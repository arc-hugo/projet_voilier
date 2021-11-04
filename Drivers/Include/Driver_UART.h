#ifndef DRIVER_UART_H__
#define DRIVER_UART_H__

#include "stm32f10x.h"

void UART_Init(USART_TypeDef * UART);
void UART_Set_Interrupt(USART_TypeDef * UART, char Prio, void(*IT_TX )(void), void(*IT_RX )(void));

#endif
