#ifndef LED_H
#define LED_H

#include "gpio.h"

#define LED_PORT    GPIOB

#define L1_PIN      GPIO_PIN_12
#define L2_PIN      GPIO_PIN_13
#define L3_PIN      GPIO_PIN_14
#define L4_PIN      GPIO_PIN_15

void Leds_Init(void);

void L1_on(void);
void L1_off(void);

void L2_on(void);
void L2_off(void);

void L3_on(void);
void L3_off(void);

void L4_on(void);
void L4_off(void);


#endif // LED_H
