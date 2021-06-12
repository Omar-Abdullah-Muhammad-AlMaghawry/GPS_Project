#ifndef portfinterrupt
#define portfinterrupt
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm_O.h"
#include "tm4c123gh6pm.h"
void PORTFINTER_init(void);
void DisableInterrupts(void); // Disable interrupts
//void EnableInterrupts(void);  // Enable interrupts
#endif