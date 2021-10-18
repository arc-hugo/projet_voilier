#include "Driver_GPIO.h"
#include "Driver_UART.h"

void IT_RX(void) {
	// Si le contenu est au dessus de 25
	if (((int8_t)USART1->DR) >= 25) {
		// On allume la LED (ODR = 1)
		GPIO_Set(GPIOA, 5);
		// Si le contenu est en dessous de -25
	} else if (((int8_t)USART1->DR) <= -25){
		// Sinon on l'éteint (ODR = 0)
		GPIO_Reset(GPIOA, 5);
	}
}

void IT_TX(void) {
	
}

int main(void){
	// GPIO INIT
	// Initialisation de la PA5 (LED) en Output Push/Pull
	GPIO_Init(GPIOA, 5, Out_Ppull_2MHZ);
	
	UART_Init(USART1);
	UART_Set_Interrupt(USART1, 2, (*IT_TX), (*IT_RX));
	
	while(1);
}	
