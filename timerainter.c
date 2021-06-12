#include "timerainter.h"
void TIMER0AONESHOTINT_init(uint32_t period){
	TIMER0_CTL_R&=~(1<<0); //desable the timer A 
	TIMER0_CFG_R=0;//enaple rts with 64 or 32 bit
	TIMER0_TAMATCHR_R=period;//value of compare match
	TIMER0_CTL_R|=(1<<4);
	TIMER0_IMR_R |=(1<<3); //enaple the int for rts
	TIMER0_CTL_R|=(1<<0); //enable the int
}

void TIMER0ARTSINT_init(uint32_t period){
	TIMER0_CTL_R&=~(1<<0); //desable the timer A
	TIMER0_TAMR_R=0; 
	TIMER0_CFG_R=1;//enaple rts with 64 or 32 bit
	TIMER0_TAMATCHR_R=period;//value of compare match
	TIMER0_CTL_R|=(1<<4);
	TIMER0_IMR_R |=(1<<3); //enaple the int for rts
	TIMER0_CTL_R|=(1<<0); //enable the int
}
