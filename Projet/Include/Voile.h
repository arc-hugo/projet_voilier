#ifndef VOILE_H__
#define VOILE_H__
#include "stm32f10x.h"

void setup_encoder_interface(void);

void init_zero(void);

void conversion_alpha_teta(void);

void config_interrupt_teta(void);

void init_pwm_moteur(void);

void Voile_Init(void);

#endif
