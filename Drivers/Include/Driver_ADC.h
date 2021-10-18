#ifndef DRIVER_ADC_H__
#define DRIVER_ADC_H__
#include "stm32f10x.h"

// Temps d'�chantiollonnage
#define ADC_SMP_0_1_us 0 // 1.5 cycles
#define ADC_SMP_0_53_us 1 // 7.5 cycles
#define ADC_SMP_0_96_us 2 // 13.5 cycles
#define ADC_SMP_2_us 3 // 28.5 cycles
#define ADC_SMP_2_96_us 4 // 41.5 cycles
#define ADC_SMP_3_96_us 5 // 55.5 cycles
#define ADC_SMP_5_1_us 6 // 71.5 cycles
#define ADC_SMP_17_1_us 7 // 239.5 cycles

// Groupes de s�quence
#define ADC_Regular_Group 1
#define ADC_Injected_Group 0

// Modes de l'ADC
#define ADC_Mode_Single_Conversion 1
#define ADC_Mode_Continuous_Conversion 0

// Initialisation d'un ADC
void ADC_Init (ADC_TypeDef * ADC);

// Attribution d'un channel � un groupe
// L'ajout d'un channel le place en t�te de file (pile)
void ADC_Add (ADC_TypeDef * ADC, char Channel, char Group);

// Retire un channel de son groupe
void ADC_Remove (ADC_TypeDef * ADC, char Channel);

// Choix du mode de l'ADC
void ADC_Mode (ADC_TypeDef * ADC, char Mode);

// Mise en place de l'interruption de l'ADC
// L'interruption sera d�clench�e lors de la fin de conversion du/des groupe(s) choisi(s)
void ADC_ActiveIT(ADC_TypeDef * ADC, char Prio, void(*IT_function )(void));

// Activation de l'interuption pour le groupe choisi
void ADC_ActiveIT_Group(ADC_TypeDef * ADC, char Group);

// Configuration du temps d'�chantillonnage de l'ADC
// Renvoie la dur�e totale de conversion (en us)
float ADC_Sampling_Time (ADC_TypeDef * ADC, char Channel, char SMP);

// D�clenche le groupe de conversion sur l'ADC choisi
void ADC_Trigger (ADC_TypeDef * ADC, char Group);

// R�cup�ration du r�sultat du groupe choisi
uint16_t ADC_Result (ADC_TypeDef * ADC, char Group);

#endif
