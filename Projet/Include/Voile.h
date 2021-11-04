#ifndef VOILE_H__
#define VOILE_H__
#include "stm32f10x.h"

void setup_encoder_interface();

void init_zero();

void conversion_alpha_teta();

void config_interrupt_teta();

void init_pwm_moteur();

int Run(void);

#endif