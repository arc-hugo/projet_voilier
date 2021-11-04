#include "Driver_GPIO.h"
#include "Driver_Timer.h"

#include "Orientation.h"

void Orientation_Init(void){
	// PWM (PB6)
	GPIO_Init(GPIOB, 6, AltOut_Ppull_2MHZ);
	// Bit de sens (PC7)
	GPIO_Init(GPIOC, 7, Out_Ppull_2MHZ);
	
	// Initialisation du Timer 4 (20kHz)
	Timer_Base_Init(TIM4, 3599, 0);
	
	// Initialisation de la PWM sur le channel 1 du Timer 4
	Timer_PWM(TIM4, 1);
	
	// Etablissement du rapport cyclique à 0%
	Timer_Set_Cycle_PWM(TIM4, 1, 0);
	
	// Lancement du compteur
	Timer_Base_Start(TIM4);
}	
