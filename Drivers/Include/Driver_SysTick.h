#ifndef DRIVER_SYSTICK_H__
#define DRIVER_SYSTICK_H__

#include "stm32f10x.h"

// Delay in ms
void SysTick_Init(unsigned int Tick, unsigned int Delay, void (*IT)(void));

#endif
