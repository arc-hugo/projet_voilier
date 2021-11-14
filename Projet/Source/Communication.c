#include "stdio.h"

#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"
#include "Driver_SysTick.h"

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

void IT_TX(void) {
	char buffer[29];
	char length = 28;
	int i;
	sprintf(buffer,"Batterie = %3d, Orient = %3d%c",100,10,0xD);
	
	for (i = 0; i < length; i++) {
		USART1->DR = buffer[i];
		while ((USART1->SR & USART_SR_TXE) != USART_SR_TXE); 
	}
}

void Communication_Init(void) {
	UART_Init(USART1);
	UART_Set_Receive(USART1, 1, (*IT_RX));
	// Transmission toutes les 3 sec
	SysTick_Init(0,30,(*IT_TX));
}
