#ifndef uart
#define uart
#include "stdint.h"
#include "tm4c123gh6pm_.h"
#include "tm4c123gh6pm.h"
#define UARTTYPE 0
/*extern enum UartType;
enum GpioPort
extern enum NoOfStopBits;
extern enum NoOfBits;*/
typedef enum {
UART_0,UART_1,UART_2,UART_3,UART_4,UART_5,UART_6,UART_7
} UartType;
typedef enum {
PORTA,PORTB,PORTC,PORTD,PORTE,PORTF
}GpioPort;
typedef enum {
oneStop,twoStop
}NoOfStopBits;
typedef enum {
	fiveBits,sexBits,sevenBits,eightBits
}NoOfBits;
typedef struct {
	UartType uartType;
	GpioPort gpioPort;
	NoOfStopBits noOfStopBits;
	NoOfBits noOfBits;
	int baudRate;
}UartConfig;
extern UartConfig confUart;
extern	UartConfig * conf; 
void UART_init(const UartConfig * conf);
uint8_t UART_recieveChar(const UartConfig * conf);
void UART_sentChar(const UartConfig * conf,uint8_t data);
//uint8_t * UART_recieveString(const UartConfig * conf,int lenght);
void UART_recieveString(const UartConfig * conf,char * str,int lenght);
	void UART_sentString(const UartConfig * conf,char * str);
//uint32_t * UART_recieveString(void);

#endif