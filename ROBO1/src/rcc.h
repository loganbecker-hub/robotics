#ifndef RCC_H
#define RCC_H

#include "main.h"

typedef enum
{
    RCC_CLOCK_HSI_16MHZ,
}CLOCK;

typedef enum
{
    RCC_PRESCALER_HSI_DISABLE,
    RCC_PRESCALER_HSI_ENABLE,
}PRESCALER;

typedef struct rcc_tag
{
    CLOCK clock;
    PRESCALER prescaler;
}rcc;

void rcc_init(rcc *rcc);

void rcc_adc1_clock_enable(void);
void rcc_gpioa_clock_enable(void);
void rcc_gpiob_clock_enable(void);
void rcc_gpioc_clock_enable(void);
void rcc_gpiod_clock_enable(void);

// Add Test
void rcc_syscfg_clock_enable(void);
void rcc_tim2_clock_enable(void);
void rcc_timer6_clock_enable(void);
void rcc_timer7_clock_enable(void);


#endif // RCC_H
