#ifndef SYSCFG_H
#define SYSCFG_H

#include "main.h"
#include "gpio.h"

typedef enum
{
    SYS_GPIOA = 0,
    SYS_GPIOB,
    SYS_GPIOC,
    SYS_GPIOD,
    SYS_GPIOE,
}SYS_GPIO;

// Note: Still need to Optimize
void syscfg_gpio_0_15(SYS_GPIO gpiox, GPIO_PIN pinx);

#endif // SYSCFG_H
