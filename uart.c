#include "uart.h"

/*
NAME: INIT UART for gbs
Description : initialization the UART
in : none
out : none
*/  	
void UART_init(const UartConfig * conf){
	float UARTSysClk = 16000000;
	float ClkDiv =16;
	float BRD = UARTSysClk / (ClkDiv * conf->baudRate);
	int IBRD = BRD;
	int FBRD=(((((float)BRD - (float)IBRD)* 64)+ 0.5));
	int c = 0;
	SYSCTL_RCGCUART_R |= (1<<(conf->uartType)); // enable uart
	SYSCTL_RCGCGPIO_R |=(1<<conf->gpioPort); // enable port
	//while((SYSCTL_PRGPIO_R&(1<<conf->gpioPort))==0);
	for( c=0;c<5;c++);
	c=0;
	switch (conf->uartType){		
		case UART_0:
			
			GPIO_PORTA_AFSEL_R |= (1<<0)|(1<<1);//enable alternative fn;
			GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)|0x00000011; //choose alternative fn as UNRx &UnTx
			GPIO_PORTA_DEN_R |=(1<<0)|(1<<1); // degit enable for 0 & 1
			GPIO_PORTA_AMSEL_R &=~(1<<1)&~(1<<0);
			UART0_CTL_R &=~UART_CTL_UARTEN; // denable
			UART0_IBRD_R =IBRD; //integer baud rate 
			UART0_FBRD_R =FBRD; //float baud rate 
		if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART0_LCRH_R|=0x10; // 5 bit & fifo enable & one stop bit
					break;
					case sexBits:
						UART0_LCRH_R|=0x30; // 6 bit & fifo enable & one stop bit
					break;
					case sevenBits:
						UART0_LCRH_R|=0x50; // 7 bit & fifo enable & one stop bit
					break;
					case eightBits:
						UART0_LCRH_R|=0x70; // 8 bit & fifo enable & one stop bit
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART0_LCRH_R|=0x18; // 5 bit & fifo enable & 2 stop bits
					break;
					case sexBits:
						UART0_LCRH_R|=0x38; // 6 bit & fifo enable & 2 stop bit
					break;
					case sevenBits:
						UART0_LCRH_R|=0x58; // 7 bit & fifo enable & 2 stop bit
					break;
					case eightBits:
						UART0_LCRH_R|=0x78; // 8 bit & fifo enable & 2 stop bit
					break;			
				}
				UART0_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
			UART0_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
		break;
		case UART_1:
			if(conf->gpioPort == 1){
				GPIO_PORTB_AFSEL_R |= (1<<0)|(1<<1);
				GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)|0x00000011;
				GPIO_PORTB_DEN_R |=(1<<0)|(1<<1); 
				GPIO_PORTB_AMSEL_R &=~(1<<0)&~(1<<1);
			}
			else if(conf->gpioPort == 2){
				GPIO_PORTC_AFSEL_R |= (1<<0)|(1<<1);
				GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as UnRx &UnTx
				GPIO_PORTC_DEN_R |=(1<<1)|(1<<0); // degit enable for 1 & 0
				GPIO_PORTC_AMSEL_R &=~(1<<0)&~(1<<1);
			}			
			UART1_CTL_R &=~UART_CTL_UARTEN; // denable			
			UART1_IBRD_R =IBRD; //integer baud rate 
			UART1_FBRD_R =FBRD; //float baud rate 
			
			if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART1_LCRH_R|=0x10; // 5 bit & fifo enable & one stop bit
					break;
					case sexBits:
						UART1_LCRH_R|=0x30; // 6 bit & fifo enable & one stop bit
					break;
					case sevenBits:
						UART1_LCRH_R|=0x50; // 7 bit & fifo enable & one stop bit
					break;
					case eightBits:
						UART1_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART1_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART1_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART1_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART1_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}
				UART1_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART1_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		case UART_2:
				GPIO_PORTD_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)|0x11000000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTD_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
				GPIO_PORTD_AMSEL_R &=~(1<<6)&~(1<<7);		
				UART2_CTL_R &=~UART_CTL_UARTEN; // denable			
				UART2_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART2_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333

		if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART2_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART2_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART2_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART2_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART2_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART2_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART2_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART2_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}	
				UART2_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART2_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		case UART_3:
				GPIO_PORTC_AFSEL_R |= (1<<6)|(1<<7);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)|0x11000000; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTC_DEN_R |=(1<<6)|(1<<7); // degit enable for 6 & 7
				GPIO_PORTC_AMSEL_R &=~(1<<6)&~(1<<7);
				UART3_CTL_R &=~UART_CTL_UARTEN; // denable		
				UART3_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART3_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
		if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART3_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART3_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART3_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART3_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART3_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART3_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART3_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART3_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}
				UART3_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART3_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
				break;
		case UART_4:
			GPIO_PORTC_AFSEL_R |= (1<<5)|(1<<4);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)|0x00110000; //choose alternative fn as U2Rx &U2Tx // edited or |
			GPIO_PORTC_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
			GPIO_PORTC_AMSEL_R &=~(1<<4)&~(1<<5);
			UART4_CTL_R &=~UART_CTL_UARTEN; // denable	
			UART4_IBRD_R =IBRD; //integer baud rate 16,000,000 /(16*9600) ** for gps 9600(default)
			UART4_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
		if(conf->noOfStopBits == oneStop)
				switch(conf->noOfBits){
					case fiveBits:
						UART4_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART4_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART4_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART4_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART4_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART4_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART4_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART4_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}		
			UART4_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
			UART4_CTL_R |=UART_CTL_UARTEN ; // enable uart 				
			break;
		case UART_5:
			GPIO_PORTE_AFSEL_R |= (1<<4)|(1<<5);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTE_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
			GPIO_PORTE_AMSEL_R &=~(1<<4)&~(1<<5);	
			UART5_CTL_R &=~UART_CTL_UARTEN; // denable
			UART5_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
			UART5_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
			if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
						case fiveBits:
						UART5_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART5_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART5_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART5_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART5_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART5_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART5_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART5_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}
				UART5_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART5_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;			
		case UART_6:
			GPIO_PORTD_AFSEL_R |= (1<<4)|(1<<5);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
			GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF00FFFF)+0x00110000; //choose alternative fn as U2Rx &U2Tx
			GPIO_PORTD_DEN_R |=(1<<4)|(1<<5); // degit enable for 6 & 7
			GPIO_PORTD_AMSEL_R &=~(1<<4)&~(1<<5);		
			UART6_CTL_R &=~UART_CTL_UARTEN; // denable						
			UART6_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
			UART6_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
		if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART6_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART6_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART6_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART6_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART6_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART6_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART6_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART6_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}
				UART6_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART6_CTL_R |=UART_CTL_UARTEN ; // enable uart 		
			break;
		case UART_7:
				GPIO_PORTE_AFSEL_R |= (1<<0)|(1<<1);//GPIO_PCTL_PD6_U2RX|GPIO_PCTL_PD7_U2TX;
				GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)|0x00000011; //choose alternative fn as U2Rx &U2Tx
				GPIO_PORTE_DEN_R |=(1<<1)|(1<<0); // degit enable for 6 & 7
				GPIO_PORTE_AMSEL_R &=~(1<<4)&~(1<<5);
				UART7_IBRD_R =IBRD; //integer baud rate 80,000,000 /(16*9600) ** for gps 9600(default)
				UART7_FBRD_R =FBRD; //float baud rate 0.833333*64 = 53.3333
				UART7_CTL_R &=~UART_CTL_UARTEN; // denable	
			if(conf->noOfStopBits == 0)
				switch(conf->noOfBits){
					case fiveBits:
						UART7_LCRH_R|=0x10; // 8 bit & fifo enable
					break;
					case sexBits:
						UART7_LCRH_R|=0x30; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART7_LCRH_R|=0x50; // 8 bit & fifo enable
					break;
					case eightBits:
						UART7_LCRH_R|=0x70; // 8 bit & fifo enable
					break;
				}
			else			
				switch(conf->noOfBits){			
					case fiveBits:
						UART7_LCRH_R|=0x18; // 8 bit & fifo enable
					break;
					case sexBits:
						UART7_LCRH_R|=0x38; // 8 bit & fifo enable
					break;
					case sevenBits:
						UART7_LCRH_R|=0x58; // 8 bit & fifo enable
					break;
					case eightBits:
						UART7_LCRH_R|=0x78; // 8 bit & fifo enable
					break;			
				}
				UART7_CTL_R |= UART_CTL_RXE | UART_CTL_TXE; // enable tx & rx
				UART7_CTL_R |=UART_CTL_UARTEN ; // enable uart 	
			break;
		default: 
			break;
	} 
	for( c=0;c<10;c++);
}

/*
NAME: UART_recieveChar
Description : recieving byte from the UART
in : null
out : uint8_t // Byte
*/
//(UART0_FR_R&UART_FR_RXFE) ==UART_FR_RXFE?0:1;
	uint8_t UART_recieveChar(const UartConfig * conf){
		switch (conf->uartType){		
			case UART_0:
					while((UART0_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART0_DR_R&(0xFF);
				break;
			case UART_1:
					while((UART1_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART1_DR_R&(0xFF);
				break;
			case UART_2:
					while((UART2_FR_R&UART_FR_RXFE) ==UART_FR_RXFE?0:1){}
					return (uint8_t) UART2_DR_R&(0xFF);
				break;
			case UART_3:
					while((UART3_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART3_DR_R&(0xFF);
				break;
			case UART_4:
					while((UART4_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART4_DR_R&(0xFF);
				break;
			case UART_5:
					while((UART5_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART5_DR_R&(0xFF);
				break;		
			case UART_6:
					while((UART6_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART6_DR_R&(0xFF);
				break;
			case UART_7:
					while((UART7_FR_R&UART_FR_RXFE) !=0){}
					return (uint8_t) UART7_DR_R&(0xFF);
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
	void UART_sentChar(const UartConfig * conf,uint8_t data){
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
						UART2_DR_R=data;	
					break;
				case UART_3:
							while((UART3_FR_R&UART_FR_TXFF)!=0){}
							UART3_DR_R=data;
					break;
				case UART_4:
							while((UART4_FR_R&UART_FR_TXFF)!=0){}
							UART4_DR_R=data;	
						break;
				case UART_5:
							while((UART5_FR_R&UART_FR_TXFF)!=0){}
							UART5_DR_R=data;
						break;		
				case UART_6:
							while((UART6_FR_R&UART_FR_TXFF)!=0){}
							UART6_DR_R=data;	
					break;
				case UART_7:
							while((UART7_FR_R&UART_FR_TXFF)!=0){}
							UART7_DR_R=data;	
					break;
		}
}
	void UART_recieveString(const UartConfig * conf,char * str,int lenght){
		uint8_t charac;
		uint8_t i=0;
		do{
			charac =	UART_recieveChar(conf);
			str[i]=charac;
			i++;
			lenght--;
			}while(lenght!=0);
		str[i] = '\0';
			i=0;
	}
	void UART_sentString(const UartConfig * conf,char * str){
		uint8_t i=0;
		while(str[i]!= '\0'){
			UART_sentChar(conf,str[i]);
			i++;
		}
		i=0;
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
