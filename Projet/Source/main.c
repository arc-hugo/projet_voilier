#include "Voile.h"
#include "Orientation.h"
#include "Communication.h"
#include "Accelero.h"
#include "Driver_ADC.h"
#include "Driver_GPIO.h"

int main(void){
	//Voile_Init();
	Orientation_Init();
	Communication_Init();
	

	while(1);
}	
