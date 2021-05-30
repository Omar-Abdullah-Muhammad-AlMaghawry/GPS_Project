#ifndef uart
#define uart
#include "stdint.h"
#include "tm4c123gh6pm.h"
#define UARTTYPE 0
/*extern enum UartType;
enum GpioPort
extern enum NoOfStopBits;
extern enum NoOfBits;*/
typedef enum {
UART0,UART1,UART2,UART3,UART4,UART5,UART6,UART7
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
void UART_init(UartConfig * conf);
uint8_t UART_recieve(UartConfig * conf);
void UART_sent(uint8_t data,UartConfig * conf);
uint32_t * UART_recieveString(void);

#endif
