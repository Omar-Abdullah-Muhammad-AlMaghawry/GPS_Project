#include "systick.h"
/*
* Name : SYSTICK_init
* Description : init the system timer
* in : doesn't take input
* out: doesn't send outpt
*/
void SYSTICK_init(void){
	NVIC_ST_CTRL_R &= ~(1<<0);//denable
	NVIC_ST_RELOAD_R = 0xFFFFFFFF;
	NVIC_ST_CURRENT_R = 0;//set zer0 at current
	NVIC_ST_CTRL_R =(1<<2)|(1<<0); // enable source clk and enable the clock
}

/*
* Name : SYSTICK_delayClk
* Description : wait no of clock cycles
* in : take No. of clk cycles
* out: doesn't send outpt
*/
void SYSTICK_delayClk(uint32_t time){ //dealy 0.625 microSec
	NVIC_ST_RELOAD_R = time - 1; //specifey the start value
	NVIC_ST_CURRENT_R = 0; //set zer0 at current
	while((NVIC_ST_CTRL_R&(1<<16))==0){}
}
/*void SYSTICK_delayMicro(uint32_t time){
	int i =0;
	int multiplayer = Multi(CLKSOURCE);
	for(i = 0;i<(time*16);i++)
		SYSTICK_delayClk(i);
}*/
/*
* Name : SYSTICK_delayMil
* Description : wait number of milli secon
* in : take No. of milli
* out: doesn't send outpt
*/
void SYSTICK_delayMil(uint32_t time){
	int i =0;
	unsigned int multiplayer = 1600;//dev of 0.0001(mill)/1/clkSource
	for(i = 0;i<(time);i++)
		SYSTICK_delayClk(multiplayer);
}
/*
* Name : SYSTICK_delayMil
* Description : wait number of  secon
* in : take No. of sec
* out: doesn't send outpt
*/
void SYSTICK_delaySec(uint32_t time){
	unsigned int i =0;
	for(i = 0;i<(time);i++)
		SYSTICK_delayMil(1000);
}