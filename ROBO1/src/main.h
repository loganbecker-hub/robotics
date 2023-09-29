#ifndef MAIN_H
#define MAIN_H

#include "stm32l071xx.h"
#include <stdint.h>
#include <stdbool.h>

// Handles the set and clear operations of inidividual bits
#define bit_set(pin)    (1U<<pin)
#define bit_clear(pin)  (~(1U<<pin))
// 2MHZ internal oscillator 
#define MSI_SPEED (2097*1000)

void delay(uint32_t ms);
void L_GPIO_INIT(void);


#endif