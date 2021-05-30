#include "uart.h"
#include "lcd_driver.h"
	
int main(void){
	uint8_t test=0;
	UartConfig confUart={UART_2,PORTD,oneStop,eightBits,9600};
	lcd_init();
	lcd_select_line(1);
	lcd_write_line("f 00");
	UART_init(&confUart); 	
	lcd_select_line(2);
	lcd_write_line("f 01");
	while(1){	
		test = UART_recieve(&confUart);
		UART_sent(test,&confUart);
		lcd_select_line(3);
		lcd_write_char(test);
		
	}
	return 0 ;
}
void SystemInit(){main();}
