#include "stm32f10x.h"
#include "Driver_GPIO.h"

void GPIO_Init (GPIO_TypeDef * GPIO, char PIN, char CONF){
	if (GPIO == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if (GPIO == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if (GPIO == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	
  if (PIN < 8){
     GPIO->CRL &= ~(0xf << PIN*4);
     GPIO->CRL |= (CONF << PIN*4); 
  }
  else {
     GPIO->CRH &= ~(0xf << (PIN-8)*4);
     GPIO->CRH |= (CONF << (PIN-8)*4); 
  }
}

int GPIO_Read(GPIO_TypeDef * GPIO, char PIN){
  return (GPIO->IDR >> PIN) & 1;
}

void GPIO_Set(GPIO_TypeDef * GPIO, char PIN){
	GPIO->BSRR = (1 << PIN);
}

void GPIO_Reset(GPIO_TypeDef * GPIO, char PIN){
	GPIO->BRR = (1 << PIN);
}

void GPIO_Toggle(GPIO_TypeDef * GPIO, char PIN) {
	if (((GPIO->ODR >> PIN) & 1) == 0) {
		GPIO_Set(GPIO, PIN);
	} else {
		GPIO_Reset(GPIO, PIN);
	}
}
