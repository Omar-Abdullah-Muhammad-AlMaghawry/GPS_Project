#include "uart.h"
#include "lcd_driver.h"
	
int main(void){
	uint8_t test=0;
	char testS[5]={0};
	UartConfig confUartTermUSB={UART_0,PORTA,oneStop,eightBits,9600};
	UartConfig confUartTermBluetooth={UART_5,PORTE,oneStop,eightBits,9600};
	UartConfig confUartGps={UART_4,PORTC,oneStop,eightBits,9600};
	lcd_init();
	lcd_select_line(1);
	lcd_write_line("f 00");
	UART_init(&confUartTermUSB); 	
	UART_init(&confUartTermBluetooth);
	UART_init(&confUartGps); 	
	lcd_select_line(2);
	lcd_write_line("f 01");
	while(1){	
		test = UART_recieveChar(&confUartGps);
		//UART_recieveString(&confUartTermBluetooth, testS,5);
	//	UART_sentChar(&confUartTermUSB,test);
		UART_sentChar(&confUartTermBluetooth,test);
		//UART_sentString(&confUartTermBluetooth,testS);
	//	UART_sent('h',&confUart);
		lcd_select_line(3);
	//	lcd_write_line(testS);
		lcd_write_char(test);
		
	}
	return 0 ;
}
void SystemInit(){main();}
