#include "Driver_ADC.h"

void ADC_Init (ADC_TypeDef * ADC) {
	if (ADC == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	else if (ADC == ADC2)
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
}

void ADC_Add_Regular(ADC_TypeDef * ADC, char Channel) {
	// Vérification du nombre de conversions
	char nb = ((ADC->SQR1 >> 20) & 0xF);
	if (nb < 15) {
		// Si l'on n'est à moins de 16 conversions
		// on verifie que notre première conversion ne soit pas vide
		if ((ADC->SQR3 & 0x1F) == 0) {
			ADC->SQR1 += (1 << 20);
			nb += 1;
		}
	}
	
	// Selon le nombre de conversions, on décale les registres
	if (nb > 6) {
		if (nb > 12) {
			int sqr1 = ((ADC->SQR1 << 5) & 0x000FFFFF);
			ADC->SQR1 &= 0xFFF00000;
		}
	}
}

void ADC_Add_Injected(ADC_TypeDef * ADC, char Channel) {
	
}

void ADC_Add (ADC_TypeDef * ADC, char Channel, char Group) {
	if (Group) {
		ADC_Add_Regular(ADC, Channel);
	} else {
		ADC_Add_Injected(ADC, Channel);
	}
}
