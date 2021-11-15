#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "stm32f10x.h"

#include "Voile.h"

void setup_encoder_interface(void){
	Timer_Base_Init(TIM2,1439,0);
	TIM2->SMCR |= 3; //Met en mode encoder interface, et compte tous les fronts de TI1 et TI2
	TIM2->CCER &= ~(0xAA); //TI1 and TI2 polarity
	TIM2->CCMR1 &= ~(0xf<<4);
	TIM2->CCMR1 &= ~(0xf<<12); //Compte tous les fronts 
	TIM2->CCMR1 |= 2; // T1FP1 mapped on TI1
	TIM2->CCMR1 |= (2<<8); // T2FP2 mapped on TI2
}

void init_zero(void){
	GPIO_Init(GPIOB,8,In_PullUp);
	while(!GPIO_Read(GPIOB,8)){}
	Timer_Base_Start(TIM2);
}

float conversion_alpha_teta(void){
	float result;
	float pourcentage_PWM;
	float alpha = ((float)(TIM2->CNT)/4.0);
	
	if (alpha < 45.0 || alpha > 315){
		result = 0.0;
	}
	else if (alpha <= 180){
		result = (90.0/135.0)*(alpha-45.0);
	}
	else
	{
		result = (90.0/135.0)*(360-alpha-45.0);
	}
	pourcentage_PWM = (1.0/18.0)*result+5.0;
	Timer_Set_Cycle_PWM(TIM3, 2, (char) pourcentage_PWM);
	return alpha;
}

void config_interrupt_teta(void){
	Timer_Base_Init(TIM1,4999,4319); //Periode timer1 = 2s
	Timer_ActiveIT(TIM1, 2, (void (*) (void)) conversion_alpha_teta);
	Timer_Base_Start(TIM1);
}

void init_pwm_moteur(void){
	Timer_Base_Init(TIM3,1439,999); //Periode timer3 = 20ms
	Timer_PWM(TIM3, 2); //Config PWM sur PA7
	GPIO_Init(GPIOA,7, AltOut_Ppull_2MHZ);
	Timer_Base_Start(TIM3);
}

void Voile_Init(void){
	setup_encoder_interface();
	init_zero();
	init_pwm_moteur();
	config_interrupt_teta();
}

 
