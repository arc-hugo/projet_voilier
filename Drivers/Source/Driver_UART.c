#include "Driver_UART.h"
#include "Driver_GPIO.h"

// Pointeur de fonction d'interruption
void (*UART_RX_Interrupt)(void) = 0;
void (*UART_TX_Interrupt)(void) = 0;
void (*UART_TC_Interrupt)(void) = 0;

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
	UART->CR1 |= (1 << 13);
	
	// On laisse M à 0 (8 bit)
	// On laisse STOP à 00 (un seul bit de stop)

	// On configure le baud rate à 9.6 kb/s
	// Mantisse = 468
	// Fraction = 12
	UART->BRR |= (468 << 4) + 12;
	
	// Activation de la réception (RE) et de la transmission (TE)
	UART->CR1 |= ((1 << 2)+(1 << 3));
	
}

void UART_Set_Interrupt(USART_TypeDef * UART, char Prio, void(*IT_TX )(void), void(*IT_TC )(void), void(*IT_RX )(void)) {
	if (UART == USART1) {
		NVIC->ISER[1] |= 1 << 5;
		NVIC->IP[37] = Prio << 4;
		// TXEIE (bit 7), TCIE (bit 6) et RXNEIE (bit 5)
		UART->CR1 |= ((1 << 7)+(1 << 6)+(1 << 5));
	}
	UART_TX_Interrupt = IT_TX;
	UART_TC_Interrupt = IT_TC;
	UART_RX_Interrupt = IT_RX;
}

void USART1_IRQHandler(void) {
	// Read data not empty (RXNE)
	if (((USART1->SR >> 5) & 1) == 1) {
		USART1->SR &= ~(1<<5);
		if (UART_RX_Interrupt != 0) {
			(* UART_RX_Interrupt)();
		}
	}
	
	// Transmission complete (TC)
	if (((USART1->SR >> 6) & 1) == 1) {
		USART1->SR &= ~(1<<6);
		if (UART_TX_Interrupt != 0) {
			(* UART_TX_Interrupt)();
		}
	}
	
	// Transmit data register empty (TXE)
	if (((USART1->SR >> 6) & 1) == 1) {
		USART1->SR &= ~(1<<6);
		if (UART_TX_Interrupt != 0) {
			(* UART_TX_Interrupt)();
		}
	}
	
	
}
