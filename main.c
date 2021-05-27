#include "uart.h"
void SystemInit(){
;
}
int main(void){
uint8_t test=0;
	UART_init();
	 
test =	UART_recieve();
return 0 ;
}
