#ifndef systick
#define systick
#include "stdint.h"
#include "tm4c123gh6pm_O.h"
#define CLKSOURCE 16000000
#define Multi(clk) ((0.0001) / (1/clk))
void SYSTICK_init(void);
void SYSTICK_delayClk(uint32_t time);
void SYSTICK_delayMil(uint32_t time);
void SYSTICK_delaySec(uint32_t time);
#endif