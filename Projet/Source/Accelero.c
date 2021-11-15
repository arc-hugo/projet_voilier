#include "Accelero.h"

void Config_Master_SPI(){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	SPI1->CR1 |= 3; //config CPOL CPHA
	SPI1->CR1 &= ~(7 << 3); //config BR
	SPI1->CR1 &= ~(1 << 11); //Configure en mode transmission 8 bits (DFF)
	SPI1->CR1 &= ~(1 << 9); //Config SSM
	SPI1->CR1 |= (1 << 6); //Config SPE
	SPI1->CR2 |= (3 << 6); //Config Rx Tx enable
}

int result;
void Run(){
	int poubelle;
	Config_Master_SPI();
	SPI1->DR = 0;
	while ((SPI1->SR & 1)){} //Wait TX = 1 (indique que le registre du maitre est vide)
	poubelle = SPI1->DR;
	SPI1->DR = 1;
	while ((SPI1->SR & 1)){}
	result = SPI1->DR;
}
