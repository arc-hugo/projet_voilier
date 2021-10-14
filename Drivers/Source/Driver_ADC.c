#include "Driver_ADC.h"

void ADC_Init (ADC_TypeDef * ADC) {
	if (ADC == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	else if (ADC == ADC2)
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
}

void ADC_Add (ADC_TypeDef * ADC, char Channel, char Group) {
	
}
