#include "Driver_ADC.h"
#include "Driver_GPIO.h"

void ADC_Init(ADC_TypeDef * ADC, char voie){
	if(ADC==ADC1){
		RCC->APB2ENR |= (1<<9);
	}else {
		RCC->APB2ENR |= (1<<10);
	}
	RCC->CFGR &= ~(1<<14);
	RCC->CFGR |= (1<<15);
	ADC->CR2 |= 1;
	ADC->SQR1 &= ~(0xF<<20);
	ADC->SQR3 |= voie;
	ADC->CR2 |= (1<<2);
	while(ADC->CR2 & (1<<2)){//Recalibration
	}
}


float Start_Conv(ADC_TypeDef * ADC){
	float res;
	ADC->CR2 |= 1;
	while(!(ADC->SR & 1<<1)){}
	res = ADC->DR & 0xFFF;
	return res/1241.0;
}
