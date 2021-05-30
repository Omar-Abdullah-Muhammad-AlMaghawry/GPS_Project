#include "uart.h"
//#include "lcd_driver.h"
	
int main(void){
	uint8_t test=0;
	UartConfig confUart={UART_0,PORTA,1,8,9600};
	//UartConfig * conf = &confUart;
	//	lcd_init();
//	lcd_select_line(1);
	//lcd_write_line("f 00");
	UART_init(&confUart); 	
	//lcd_select_line(2);
	//lcd_write_line("f 01");
	while(1){	
		test =UART_recieve(&confUart);
		UART_sent(test,&confUart);
	}
	return 0 ;
}
void SystemInit(){}
