#include "Batterie.h"

#include "Driver_GPIO.h"
#include "Driver_ADC.h"

void Batterie_Init(void){
	GPIO_Init(GPIOB, 0, In_Analog);
	ADC_Init(ADC1, 8);
}
