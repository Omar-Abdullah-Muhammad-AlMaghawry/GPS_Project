#include "tm4c123gh6pm.h"
#include "stdint.h"

#define GPIO_PORTD_CR_R ((*(volatile unsigned long *)0X40007524))

//Delay code by n microseconds
void delay_micro2(int n){
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
}

void uart2_init(){
	SYSCTL->RCGCGPIO |= 0x08;
	SYSCTL->RCGCUART |= 4;  // enable clock for UART2
	GPIOD->LOCK = 0x4C4F434B;
	GPIOD->DEN |= 0xC0;
	//GPIOD->CR	 |= 0xC0;
	GPIO_PORTD_CR_R = 0xFF;
	
	UART2->CTL = 0;         /* UART2 module disbable */
	UART2->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
  UART2->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
  UART2->CC = 0;          /*select system clock*/
  UART2->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
  UART2->CTL = 0x301;     /* Enable UART2 module, Rx and Tx */
	
	GPIOD->DEN = 0xC0;      /* set PD6 and PD7 as digital */
  GPIOD->AFSEL = 0xC0;    /* Use PD6,PD7 alternate function */
  GPIOD->AMSEL = 0;    /* Turn off analg function*/
  GPIOD->PCTL = 0x11000000;     /* configure PD6 and PD7 for UART */
	delay_micro2(5);
}

char read_gps(){
	char c;
	while((UART2->FR & 0x10) != 0);
	c = UART2->DR;
	return c;
}

void SystemInit(){
	uart2_init();
}
