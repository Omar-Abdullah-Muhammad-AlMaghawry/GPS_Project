//#include "TM4C123GH6PM.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include "lcd_driver.h"

//int GPIO_PF_2 					= (1<<2);
//int GPIO_PORTF_DIR_R 		= 0x40025400;
//int GPIO_PORTF_UNLOCK 	= 0x4C4F434B;
//int GPIO_PORTF_CR_R			= 0x40025524;
////int i = 0;
//float accumulated_distance = 0;

//float distance_calculator() {
//	float num = 1.2;
//	// return rand()%10;
//	return num;
//}


//int main() {
//	int i =0;
//	char text[16];
//	lcd_init();
//	lcd_select_line(1);
//	lcd_write_line("Test accumulator");
//	while (i < 2) {
//		if((TIMER0->RIS & 0x00000001) == 1) {
//			accumulated_distance = distance_calculator() + accumulated_distance;
//			i = i + 1;
//			// PRINT THE VALUE ON LCD
//			if(accumulated_distance >2.3){
//			sprintf(text, "%d",(int) (accumulated_distance*10));
//			lcd_select_line(3);
//			lcd_write_line(text);
//			}
//			TIMER0->ICR				|= (1<<0);
//		}
//	}

//	return 0;
//}

//void SystemInit() {
//	/* configure GPIO port F blue LED (PF2) */
//	
//	SYSCTL->RCGCGPIO 			|= (1<<5);							// enable clock for port F
//	while ((SYSCTL->RCGCGPIO & (1<<5)) == 0){}		// wait until port F is enabled
//	GPIOF->LOCK						= GPIO_PORTF_UNLOCK;		// unlock port F
//	GPIO_PORTF_CR_R				|= (7<<1);							// commit changes to port F
//	GPIOF->AMSEL					= 0x00000000;						// disable analog functions
//	GPIOF->PCTL						&= 0x00000000;					// clear PCTL bits for port F
//	GPIOF->AFSEL 					&= ~GPIO_PF_2;					// disable AFSEL for (PF2)
//	GPIOF->DIR						= GPIO_PF_2;
//	GPIOF->DEN						= GPIO_PF_2;
//	// GPIOF->DATA						|= (7<<1);
//	
//		
//	/* configering GPTM */
//		
//	SYSCTL->RCGCTIMER			|= (1<<0);							// enable clock fro timerA0
//	TIMER0->CTL						&= !(1<<0);							// disable timerA0 from control register
//	TIMER0->CFG						= 0x00000000;						// write configuration register for timerA0
//	// configure timerA0 mode register
//	TIMER0->TAMR					|= (0x2<<0);						// sets the timer to periodic mode
//	TIMER0->TAMR					|= (1<<4);							// sets the counter to count down
//	TIMER0->TAILR					= 0x00F42400;						// set load value for timerA0 // 0x00F42400(1 sec); // 0x3D09000(4 secs); // 0x140
//	TIMER0->CTL						|= (1<<0);							// enable timerA0 from control register
//	
//	main();
//}
