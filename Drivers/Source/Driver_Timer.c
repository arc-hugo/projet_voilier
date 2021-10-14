#include "Driver_Timer.h"
#include "Driver_GPIO.h"

// Pointeurs de fonctions d'interruption
void (*Timer1_Interupt)(void) = 0;
void (*Timer2_Interupt)(void) = 0;
void (*Timer3_Interupt)(void) = 0;
void (*Timer4_Interupt)(void) = 0;

void Timer_Base_Init (TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC) {
	if (Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (Timer == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else
		return;
	
	Timer->PSC = PSC;
	Timer->ARR = ARR;
}

void Timer_Base_Start (TIM_TypeDef * Timer) {
	Timer->CR1 |= 1;
}

void Timer_Base_Stop (TIM_TypeDef * Timer) {
	Timer->CR1 &= ~(1);
}


void Timer_ActiveIT(TIM_TypeDef * Timer, char Prio, void(*IT_function )(void)) {
	// Autorisation de l'interruption et mise en place de la priorité dans le NVIC
	// Attribution de l'adresse de l'interrupteur qau ointeur de fonction correspondant
	if (Timer == TIM1) {
		NVIC->ISER[0]|= 1 << 25;
		NVIC->IP[25] = (Prio << 4);
		Timer1_Interupt = IT_function;
	} else if (Timer == TIM2) {
		NVIC->ISER[0] = 1 << 28;
		NVIC->IP[28] = (Prio << 4);
		Timer2_Interupt = IT_function;
	} else if (Timer == TIM3) {
		NVIC->ISER[0] = 1 << 29;
		NVIC->IP[29] = (Prio << 4);
		Timer3_Interupt = IT_function;
		} else if (Timer == TIM4) {
		NVIC->ISER[0] = 1 << 30;
		NVIC->IP[30] = (Prio << 4);
		Timer4_Interupt = IT_function;
	} else {
		return;
	}
	
	// Autorisation des demandes d'interruption 
	Timer->DIER |= 0x1;
}

void Timer_PWM(TIM_TypeDef * Timer, char Channel) {
	// Activation de la PWM du channel spécifié
	switch (Channel) {
		case 1:
			Timer->CCMR1 |= (6 << 4);
			Timer->CCER |= (1 << 0);
			break;
		case 2:
			Timer->CCMR1 |= (6 << 12);
			Timer->CCER |= (1 << 4);
			break;
		case 3:
			Timer->CCMR2 |= (6 << 4);
			Timer->CCER |= (1 << 8);
			break;
		case 4:
			Timer->CCMR2 |= (6 << 12);
			Timer->CCER |= (1 << 12);
			break;
		default:
			return;
	}
	
	// Configuration supplémentaire pour TIM1
	if (Timer == TIM1) {
		Timer->BDTR |= (1 << 15);
	}
}

void Timer_Set_Cycle_PWM(TIM_TypeDef * Timer, char Channel, char Percent) {
	// Calcul du pourcentage de l'ARR
	uint16_t CCR = (Percent*Timer->ARR)/100;
	switch (Channel) {
		case 1:
			Timer->CCR1 = CCR;
			break;
		case 2:
			Timer->CCR2 = CCR;
			break;
		case 3:
			Timer->CCR3 = CCR;
			break;
		case 4:
			Timer->CCR4 = CCR;
			break;
		default:
			break;
	}
}

// Fonction d'interruption de TIM1
void TIM1_UP_IRQHandler (void) {
	TIM1->SR &= ~(0x1);
	if (Timer1_Interupt != 0)
		(*Timer1_Interupt)();
}

// Fonction d'interruption de TIM2
void TIM2_IRQHandler (void) {
	TIM2->SR &= ~(0x1);
	if (Timer2_Interupt != 0)
		(*Timer2_Interupt)();
}

// Fonction d'interruption de TIM3
void TIM3_IRQHandler (void) {
	TIM3->SR &= ~(0x1);
	if (Timer3_Interupt != 0)
		(*Timer3_Interupt)();
}

// Fonction d'interruption de TIM4
void TIM4_IRQHandler (void) {
	TIM4->SR &= ~(0x1);
	if (Timer4_Interupt != 0)
		(*Timer4_Interupt)();
}
