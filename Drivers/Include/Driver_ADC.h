#ifndef DRIVER_ADC_H
#define DRIVER_ADC_H
#include "stm32f10x.h"


//Initialise l'ADC
void ADC_Init(ADC_TypeDef * ADC, char voie);
int Start_Conv(ADC_TypeDef * ADC);

#endif
