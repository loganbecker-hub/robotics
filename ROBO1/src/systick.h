#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define HSI_VALUE (16000000U)

uint32_t get_ticks(void);

void SysTick_Handler(void);

void delay(uint32_t ms);

#endif 
