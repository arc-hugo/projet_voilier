#include "Driver_UART.h"
#include "Driver_GPIO.h"

// Pointeur de fonction d'interruption
void (*UART_RX_Interrupt)(void) = 0;

void UART_Init(USART_TypeDef * UART) {
	// Activation de la clock du UART dans le RCC
	if (UART == USART1) {
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		// Initialisation de la PA10 (RX) en Input Pull-up
		GPIO_Init(GPIOA, 10, In_Floating);
		// Initialisation de la PA9 (TX) en Alternate Output Push/Pull
		GPIO_Init(GPIOA, 9, AltOut_Ppull_2MHZ);
	}
	// Activation du UART (UE)
	UART->CR1 |= USART_CR1_UE;
	
	// On laisse M ? 0 (8 bit)
	// On laisse STOP ? 00 (un seul bit de stop)

	// On configure le baud rate ? 9.6 kb/s
	// Mantisse = 468
	// Fraction = 12
	UART->BRR |= (468 << 4) + 12;
	
	// Activation de la r?ception (RE) et de la transmission (TE)
	UART->CR1 |= USART_CR1_RE+USART_CR1_TE;
	
}

void UART_Set_Receive(USART_TypeDef * UART, char Prio, void(*IT_RX )(void)) {
	if (UART == USART1) {
		NVIC->ISER[1] |= 1 << 5;
		NVIC->IP[37] = Prio << 4;
		// RXNEIE (bit 5)
		UART->CR1 |= USART_CR1_RXNEIE;
	}
	UART_RX_Interrupt = IT_RX;
}

void USART1_IRQHandler(void) {
	// Read data not empty (RXNE)
	if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE) {
		USART1->SR &= ~(USART_SR_RXNE);
		if (UART_RX_Interrupt != 0) {
			(* UART_RX_Interrupt)();
		}
	}
	
}
