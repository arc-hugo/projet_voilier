#include "Voile.h"
#include "Orientation.h"
#include "Communication.h"
#include "Accelero.h"
#include "Driver_ADC.h"
#include "Driver_GPIO.h"

int res;
int main(void){
	res = 0;
	/*Voile_Init();
	Orientation_Init();
	Communication_Init();*/
	GPIO_Init(GPIOB, 0, In_Analog);
	ADC_Init(ADC1, 8);
	while(1){
		res = Start_Conv(ADC1);
	};
}	
