#ifndef timerA
#define timerA
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm_O.h"
#include "tm4c123gh6pm.h"

typedef enum {
TIMER_0,TIMER_1,TIMER_2,TIMER_3,TIMER_4,TIMER_5,TIMER_6,TIMER_7
} timerType;
void TIMER0A_initPeriodicInt_Mil(uint32_t period,timerType t);
void TIMER0A_initRtsInt(uint32_t period);
#endif