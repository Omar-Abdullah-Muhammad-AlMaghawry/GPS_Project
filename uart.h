#ifndef uart
#define uart
#include "stdint.h"
#include "tm4c123gh6pm.h"
#define UARTTYPE 2
void UART0_init(void);
uint8_t UART_recieve(void);
void UART_sent(uint8_t data);
uint32_t * UART_recieveString(void);
#endif
