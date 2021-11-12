#include "Driver_SysTick.h"

unsigned int save = 0;
unsigned int delay = 0;
void (*SysTick_IT)(void) = 0;

void SysTick_Handler(void) {
	if (delay != 0) {
		delay--;
	}
	if (delay == 0 && SysTick_IT != 0) {
		SysTick->CTRL &= ~(1);
		(* SysTick_IT)();
		delay = save;
		SysTick->CTRL |= 1;
	}
}

// Delay in ms
void SysTick_Init(unsigned int Tick, unsigned int Delay, void (*IT)(void)) {
	SysTick_Config(Tick * 9000);
	SysTick_IT = IT;
	delay = Delay;
	save = Delay;
}