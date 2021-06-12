#include "portfinterrupt.h"
void PORTFINTER_init(void){
	SYSCTL_RCGCGPIO_R|=(1<<5);
	while(SYSCTL_PRGPIO_R&(1<<5)==0);
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R=0xFF;
	GPIO_PORTF_LOCK_R = 0;
	GPIO_PORTF_DIR_R =0x0E;
	GPIO_PORTF_DEN_R=0xFF;
	GPIO_PORTF_PUR_R=(1<<0)|(1<<4);
	//GPIO_PORTF_AFSEL_R = 0x00;
	GPIO_PORTF_IS_R	&=~(1<<0)|~(1<<4); //porf bit0 edge sensitive
	GPIO_PORTF_IBE_R&=~(1<<0)|~(1<<4); //portf bit0 not both edge
	GPIO_PORTF_IEV_R&=~(1<<0)|~(1<<4); //PORTF BIT0 FALLING edge
	GPIO_PORTF_ICR_R|=(1<<0)|(1<<4);//CLEAR THE FLAG FOR BIT0 OF PORTF 
	GPIO_PORTF_IM_R |=(1<<0)|(1<<4); // ENABLE INT FPR BIT0 OF PORTF
	NVIC_PRI7_R=(NVIC_PRI7_R&0xFF00FFFF)|(3<<5);//per1 bcause first bit reserved
	NVIC_EN0_R|=(1<<30); //ENABLE MODULE INT FOR PORTF
	EnableInterrupts();
}
void GPIOF_Handler(void){
	if(GPIO_PORTF_MIS_R&(1<<0)){
	GPIO_PORTF_DATA_R^=(1<<1);
	GPIO_PORTF_ICR_R |=(1<<0);
}
	else if(GPIO_PORTF_MIS_R&(1<<4)){
	GPIO_PORTF_DATA_R^=(1<<3);
	GPIO_PORTF_ICR_R |=(1<<4);
}
}
void EnableInterrupts(void){
__asm ("CPSIE I")//set I = 0 to enable
}
