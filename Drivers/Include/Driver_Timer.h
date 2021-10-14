#ifndef DRIVER_TIMER_H__
#define DRIVER_TIMER_H__
#include "stm32f10x.h"

#define TIM_CLOK_FREQUENCY 72000000

// Initialisation du Timer avec une valeur d'autoreload (ARR) et de prescaler (PSC)
void Timer_Base_Init (TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC);
// Lancement du Timer
void Timer_Base_Start (TIM_TypeDef * Timer);
// Arrêt du Timer
void Timer_Base_Stop (TIM_TypeDef * Timer);
// Activation de l'interruption du Timer
// Place la priorité (Prio) et défini un handler (IT_function)
void Timer_ActiveIT(TIM_TypeDef * Timer, char Prio, void(*IT_function )(void));
// Active le channel spécifié du Timer spécifié
// La GPIO et la PWM (ARR, PSC) doivent être activées au préalable
void Timer_PWM(TIM_TypeDef * Timer, char Channel);
// Etablie le rapport cyclique de la PWM au Timer et channel spécifiés
// Pourcentage en 
void Timer_Set_Cycle_PWM(TIM_TypeDef * Timer, char Channel, char Percent);
#endif
