#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "stm32f10x.h"

void setup_encoder_interface(){
	Timer_Base_Init(TIM2,1439,0);
	TIM2->SMCR |= 3; //Met en mode encoder interface, et compte tous les fronts de TI1 et TI2
	TIM2->CCER &= ~(0xAA); //TI1 and TI2 polarity
	TIM2->CCMR1 &= ~(0xf<<4);
	TIM2->CCMR1 &= ~(0xf<<12); //Compte tous les fronts 
	TIM2->CCMR1 |= 2; // T1FP1 mapped on TI1
	TIM2->CCMR1 |= (2<<8); // T2FP2 mapped on TI2
	Timer_Base_Start(TIM2);
}

int main(void){
	setup_encoder_interface();
	while(1);
}	
