#include "uart.h"


/*
NAME: INIT UART0
Description : initialization the UART
*/  
void UART0_init(void){
SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0;
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R0)==0){};
GPIO_PORTA_AFSEL_R |= GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX;
GPIO_PORTA_DEN_R |=(1<<0)|(1<<1);
GPIO_PORTA_DIR_R |=(1<<0)|(1<<1) ;
UART0_CTL_R |=UART_CTL_UARTEN |UART_CTL_RXE|UART_CTL_TXE; 
//UART0_DR_R = ;
//UART0_FR_R = ;
}

/*
NAME: recive UART0
Description : recieving byte from the UART0
in : null
out : uint8_t // Byte
*/

uint8_t UART_recieve(void){
while((UART0_FR_R&UART_FR_RXFE) !=0){}
	return UART0_DR_R&(0xFF);
}
uint32_t * UART_recieveString(void){
 uint8_t data = UART_recieve();
	uint8_t * ptr = &data;
	uint32_t * ptrInt32 ;
	int i ;
	for( i = 0 ; i<4;i++){
	* ptrInt32 = * (ptr + i);
	}
	return ptrInt32; 
}

/*
NAME: sent UART0
Description : sent byte from the UART0
in : data // byte
out : 0
*/
void UART_sent(uint8_t data){
while((UART0_FR_R&UART_FR_TXFF)!=0){}
	UART0_DR_R=data;
}
