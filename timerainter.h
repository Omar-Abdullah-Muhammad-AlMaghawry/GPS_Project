#ifndef timerA
#define timerA
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm_O.h"
#include "tm4c123gh6pm.h"

void TIMER0A_initPeriodicInt_Mil(uint32_t period);
void TIMER0A_initRtsInt(uint32_t period);
#endif