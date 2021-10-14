#ifndef DRIVER_GPIO_H__
#define DRIVER_GPIO_H__
#include "stm32f10x.h"

// Configurations en INPUT
#define In_Floating 0x4
#define In_PullDown 0x8
#define In_PullUp 0x8
#define In_Analog 0x0

// Configurations en OUTPUT 2MHZ
#define Out_Ppull_2MHZ 0x2
#define Out_OD_2MHZ 0x6
#define AltOut_Ppull_2MHZ 0xA
#define AltOut_OD_2MHZ 0xE

// Configurations en OUTPUT 10MHZ
#define Out_Ppull_10MHZ 0x1
#define Out_OD_10MHZ 0x5
#define AltOut_Ppull_10MHZ 0x9
#define AltOut_OD_10MHZ 0xD

// Configurations en OUTPUT 50MHZ
#define Out_Ppull_50MHZ 0x3
#define Out_OD_50MHZ 0x7
#define AltOut_Ppull_50MHZ 0xB
#define AltOut_OD_50MHZ 0xF

// Initialisation d'une PIN d'un GPIO à la CONF souhaitée
void GPIO_Init (GPIO_TypeDef * GPIO, char PIN, char CONF);
// Lecture d'un bit de l'IDR du GPIO correspondant à la PIN choisie
int GPIO_Read(GPIO_TypeDef * GPIO, char PIN);
// Mise à 1 du bit de l'ODR du GPIO correspondant à la PIN choisie
void GPIO_Set(GPIO_TypeDef * GPIO, char PIN);
// Mise à 0 du bit de l'ODR du GPIO correspondant à la PIN choisie
void GPIO_Reset(GPIO_TypeDef * GPIO, char PIN);
// Inversement du bit de l'ODR du GPIO correspondant à la PIN choisie
void GPIO_Toggle(GPIO_TypeDef * GPIO, char PIN);

#endif
