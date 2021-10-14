#include "Driver_GPIO.h"

int main(void){
	// GPIO INIT
	// Initialisation de la PA5 (LED) en Output Push/Pull
	GPIO_Init(GPIOA, 5, Out_Ppull_2MHZ);
	
	// Initialisation de la PA9 (RX) en Input Pull-up
	GPIO_Init(GPIOA, 9, In_Floating);
	// Mettre le ODR du PIN 9 à 1
	GPIO_Set(GPIOA, 9);
	
	// Initialisation de la PA10 (TX) en Alternate Output Push/Pull
	GPIO_Init(GPIOA, 10, AltOut_Ppull_2MHZ);
	
	// USART INIT
	// Activation de la clock du UART dans le RCC
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	// Activatiion du UART 1
	USART1->CR1 |= (1 << 13);
	
	// On laisse M à 0 (8 bit)
	// On laisse STOP à 00 (un seul bit de stop)
	
	// page 804
	// On configure le baud rate à 9.6 kb/s
	// Mantisse = 468
	// Fraction = 12
	USART1->BRR |= (468 << 4) + 12;
	
	// Activation de la réception (RE)
	USART1->CR1 |= 4;
	
	while(1) {
		// On attend la fin de transmission des données
		if (((USART1->SR >> 5) & 1) == 1) {
			// On récupère le contenu de DR
			int16_t data = USART1->DR & 0xFF;
			// Si le contenu est au dessus de 25
			if (data >= 25) {
				// On allume la LED (ODR = 1)
				GPIO_Set(GPIOA, 5);
			// Si le contenu est en dessous de -25
			} else if (data <= -25){
				// Sinon on l'éteint (ODR = 0)
				GPIO_Reset(GPIOA, 5);
			}
		}
	}
}	
