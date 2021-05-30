#include "uart.h"
/*
NAME: INIT UART for gbs
Description : initialization the UART
*/  
	
void UART_init(const UartConfig * conf){
	int UARTSysClk = 16000000;
	int ClkDiv =16;
	uint8_t BRD = UARTSysClk / (ClkDiv * conf->baudRate);
	int IBRD = BRD;
	int FBRD = ( (BRD-IBRD)* 64 + 0.5);
	int c ;
	SYSCTL_RCGCGPIO_R |=(1<<conf->gpioPort); // enable portd
	//while((SYSCTL_PRGPIO_R&(1<<conf->gpioPort))==0);
	for( c=0;c<5;c++);
	SYSCTL_RCGCUART_R |= (1<<(conf->uartType)); // enable uart2
	switch (conf->uartType){	
		
		case UART_0:
			UART0_CTL_R &=~UART_CTL_UARTEN; // denable
			GPIO_PORTA_AFSEL_R |= (1<<0)|(1<<1);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTA_DEN_R |=(1<<0)|(1<<1); // degit enable for 6 & 7
			UART0_LCRH_R|=0x70; // 8 bit & fifo enable	
			UART0_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
			UART0_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
			UART0_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
			UART0_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
		break;
		case UART_1:
				UART1_CTL_R &=~UART_CTL_UARTEN; // denable			
			if(conf->gpioPort == 1){
				GPIO_PORTB_AFSEL_R |= (1<<0)|(1<<1);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTB_DEN_R |=(1<<0)|(1<<1); // degit enable for 6 & 7
			}
			else if(conf->gpioPort == 2){
				GPIO_PORTC_AFSEL_R |= (1<<0)|(1<<1);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTC_DEN_R |=(1<<1)|(1<<0); // degit enable for 6 & 7
			}
			UART1_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART1_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART1_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART1_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART1_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		case UART_2:
				UART2_CTL_R &=~UART_CTL_UARTEN; // denable			
				GPIO_PORTD_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTD_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
				UART2_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART2_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART2_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART2_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART2_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		case UART_3:
				UART3_CTL_R &=~UART_CTL_UARTEN; // denable		
				GPIO_PORTC_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTC_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
				UART3_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART3_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART3_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART3_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART3_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		case UART_4:
			UART4_CTL_R &=~UART_CTL_UARTEN; // denable	
			GPIO_PORTC_AFSEL_R |= (1<<5)|(1<<4);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTC_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
			UART4_LCRH_R|=0x70; // 8 bit & fifo enable	
			UART4_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
			UART4_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
			UART4_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
			UART4_CTL_R |=UART_CTL_UARTEN ; // enable uart 				
			break;
		case UART_5:
				UART5_CTL_R &=~UART_CTL_UARTEN; // denable
				GPIO_PORTE_AFSEL_R |= (1<<4)|(1<<5);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTE_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
				UART5_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART5_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART5_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART5_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART5_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;			
		case UART_6:
				UART6_CTL_R &=~UART_CTL_UARTEN; // denable		
				GPIO_PORTD_AFSEL_R |= (1<<4)|(1<<5);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTD_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
				UART6_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART6_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART6_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART6_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART6_CTL_R |=UART_CTL_UARTEN ; // enable uart 		
			break;
		case UART_7:
				UART7_CTL_R &=~UART_CTL_UARTEN; // denable		
				GPIO_PORTE_AFSEL_R |= (1<<0)|(1<<1);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000011; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTE_DEN_R |=(1<<1)|(1<<0); // degit enable for 6 & 7
				UART7_LCRH_R|=0x70; // 8 bit & fifo enable	
				UART7_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART7_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART7_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART7_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		default: 
			break;
	} 
/*#if 0 
	switch (conf->gpioPort){
	case PORTA:
			GPIO_PORTA_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTA_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;
	case PORTB:
			GPIO_PORTB_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTB_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;
	case PORTC:
			GPIO_PORTC_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTC_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;
	case PORTD:
			GPIO_PORTD_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTD_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;
	case PORTE:
			GPIO_PORTE_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTE_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTE_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;
	case PORTF:
			GPIO_PORTF_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTF_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTF_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
		break;

}	 
#endif 
	//GPIO_PORTD_DIR_R |=(1<<6)|(1<<7);
	*/
//p * aux
//unified program
}

/*
NAME: recive UART0
Description : recieving byte from the UART0
in : null
out : uint8_t // Byte
*/

uint8_t UART_recieve(const UartConfig * conf){
		switch (conf->uartType){	
		
		case UART_0:
		while((UART0_FR_R&UART_FR_RXFE) !=0){}
		return UART0_DR_R&(0xFF);
	break;
		case UART_1:
while((UART1_FR_R&UART_FR_RXFE) !=0){}
	return UART1_DR_R&(0xFF);
	break;

case UART_2:
while((UART2_FR_R&UART_FR_RXFE) !=0){}
	return UART2_DR_R&(0xFF);
	break;
case UART_3:
while((UART3_FR_R&UART_FR_RXFE) !=0){}
	return UART3_DR_R&(0xFF);
	break;
	case UART_4:
while((UART4_FR_R&UART_FR_RXFE) !=0){}
	return UART4_DR_R&(0xFF);
	break;
	case UART_5:
while((UART5_FR_R&UART_FR_RXFE) !=0){}
	return UART5_DR_R&(0xFF);
	break;		
		case UART_6:
while((UART6_FR_R&UART_FR_RXFE) !=0){}
	return UART6_DR_R&(0xFF);
	break;case UART_7:
while((UART7_FR_R&UART_FR_RXFE) !=0){}
	return UART7_DR_R&(0xFF);
	break;
		}
}
/*uint32_t * UART_recieveString(void){
 uint8_t data = UART_recieve();
	uint8_t * ptr = &data;
	uint32_t * ptrInt32 ;
	int i ;
	for( i = 0 ; i<4;i++){
	* ptrInt32 = * (ptr + i);
	}
	return ptrInt32; 
}
*/
/*
NAME: sent UART0
Description : sent byte from the UART0
in : data // byte
out : 0
*/
void UART_sent(uint8_t data,const UartConfig * conf){
	switch (conf->uartType){	
		
		case UART_0:
while((UART0_FR_R&UART_FR_TXFF)!=0){}
	UART0_DR_R=data;
	break;
		case UART_1:
while((UART1_FR_R&UART_FR_TXFF)!=0){}
	UART1_DR_R=data;
	break;

case UART_2:
while((UART2_FR_R&UART_FR_TXFF)!=0){}
	UART2_DR_R=data;	break;
case UART_3:
while((UART3_FR_R&UART_FR_TXFF)!=0){}
	UART3_DR_R=data;	break;
	case UART_4:
while((UART4_FR_R&UART_FR_TXFF)!=0){}
	UART4_DR_R=data;	break;
	case UART_5:while((UART5_FR_R&UART_FR_TXFF)!=0){}
	UART5_DR_R=data;
	break;		
		case UART_6:
while((UART6_FR_R&UART_FR_TXFF)!=0){}
	UART6_DR_R=data;	break;
		case UART_7:
while((UART7_FR_R&UART_FR_TXFF)!=0){}
	UART7_DR_R=data;	
	break;
		}

}
