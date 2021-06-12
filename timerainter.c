#include "timerainter.h"
void TIMER0A_initPeriodicInt_Mil(uint32_t period){ //62.5 micro sec per cycle 
	SYSCTL_RCGCTIMER_R |=(1<<0);
	TIMER0_CTL_R&=~(1<<0); //desable the timer A
	TIMER0_TAMR_R|=(1<<2)|(1<<7)|(1<<5);
	TIMER0_TAMR_R&=~(1<<6)|~(1<<4);
	TIMER0_TAILR_R =period*16000; //the up value that when we reaach it's start again and make interrupts * 16 tom make 1 ms
	TIMER0_IMR_R |=(1<<0); //enaple the int for rts
	TIMER0_CTL_R|=(1<<0); //enable the int
	//TIMER0_MIS_R&=~(1<<)
	TIMER0_ICR_R|=(1<<0);
	NVIC_PRI7_R|=(NVIC_PRI7_R&0x00FFFFFF)|(2<<7);
	NVIC_EN0_R|=(1<<19);
	
	EnableInterrupts();
}
void TIMER0A_Handler(void){
	
	if((TIMER0_MIS_R&(1<<0))==1)
		GPIO_PORTF_DATA_R^=(1<<3);
TIMER0_ICR_R|=(1<<0);
}
void TIMER0A_initRtsInt(uint32_t period){
	TIMER0_CTL_R&=~(1<<0); //desable the timer A
	TIMER0_TAMR_R=0; 
	TIMER0_CFG_R=1;//enaple rts with 64 or 32 bit
	TIMER0_TAMATCHR_R=period;//value of compare match
	TIMER0_CTL_R|=(1<<4);
	TIMER0_IMR_R |=(1<<3); //enaple the int for rts
	TIMER0_CTL_R|=(1<<0); //enable the int
}


