#include "systick.h"

void SYSTICK_init(void){
	NVIC_ST_CTRL_R &= ~(1<<0);//denable
	NVIC_ST_RELOAD_R = 0xFFFFFFFF;
	NVIC_ST_CURRENT_R = 0;//set zer0 at current
	NVIC_ST_CTRL_R =(1<<2)|(1<<0); // enable source clk and enable the clock
}
void SYSTICK_delayClk(uint32_t time){ //dealy 0.625 microSec
	NVIC_ST_RELOAD_R = time - 1; //specifey the start value
	NVIC_ST_CURRENT_R = 0; //set zer0 at current
	while((NVIC_ST_CTRL_R&(1<<16))==1){}
}
/*void SYSTICK_delayMicro(uint32_t time){
	int i =0;
	int multiplayer = Multi(CLKSOURCE);
	for(i = 0;i<(time*16);i++)
		SYSTICK_delayClk(i);
}*/
void SYSTICK_delayMil(uint32_t time){
	int i =0;
	int multiplayer = 1600;//dev of 0.0001(mill)/1/clkSource
	for(i = 0;i<(time*multiplayer);i++)
		SYSTICK_delayClk(i);
}
void SYSTICK_delaySecond(uint32_t time){
	int i =0;
	for(i = 0;i<(time*1000);i++)
		SYSTICK_delayMil(i);
}