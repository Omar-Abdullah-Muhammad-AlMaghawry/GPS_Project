#include "uart.h"
#include"lcd.h"
void SystemInit(){
;
}
int main(void){
uint8_t test=0;
UartConfig testUart ={UART0,PORTA,1,8,9600};
UART_init(&testUart); 	
while(1){	
test =UART_recieve(&testUart);

	UART_sent(test,&testUart);
}
	return 0 ;
}
