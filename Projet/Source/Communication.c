#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"

#include "Communication.h"

void IT_RX(void) {
	// Si le contenu est positif
	int8_t rapport = (int8_t)USART1->DR;
	if (rapport >= 0) {
		// On envoie un bit de sens à 1 (tribord)
		GPIO_Reset(GPIOC, 7);
		
	} else {
		// Sinon on envoie un bit de sens à 0 (babord)
		GPIO_Set(GPIOC, 7);
		rapport = -rapport;
	}
	
	Timer_Set_Cycle_PWM(TIM4, 1, rapport);
}

void IT_TX (void) {
	
}

void Communication_Init(void) {
	UART_Init(USART1);
	UART_Set_Interrupt(USART1, 2, (*IT_TX), (*IT_RX));
}
