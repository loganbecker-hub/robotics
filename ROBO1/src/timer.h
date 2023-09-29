#ifndef TIMER_H
#define TIMER_H

#include "main.h"

typedef enum 
{
    TIM_BUFFER_ARR_ENABLE,
    TIM_BUFFER_ARR_DISABLE,
}TIM_ARR;

typedef enum
{
    TIM_MODE_CONTINUOUS,
    TIM_MODE_ONE_PULSE,
}TIM_MODE;

typedef enum
{
    TIM_UPDATE_NONE,
    TIM_UPDATE_INTERRUPT_ENABLE,
    TIM_UPDATE_INTERRUPT_DISABLE,
    TIM_UPDATE_DMA_ENABLE,
    TIM_UPDATE_DMA_DISABLE,
}TIM_UPDATE;

typedef struct timer_tag
{
    TIM_TypeDef *timer;
    TIM_ARR buffer;
    TIM_MODE mode;
    TIM_UPDATE update;
}timer;

void timer_6_7_init(timer *timer);

void timer_6_7_update_enable(TIM_TypeDef * timer);
void timer_6_7_update_disable(TIM_TypeDef * timer);

void timer_6_7_counter_enable(TIM_TypeDef * timer);
void timer_6_7_counter_disable(TIM_TypeDef * timer);

void timer_6_7_set_counter(TIM_TypeDef * timer, uint16_t value);
void timer_6_7_set_prescaler(TIM_TypeDef * timer, uint16_t value);
void timer_6_7_set_reload(TIM_TypeDef * timer, uint16_t value);

#endif // TIMER_H

	/* EXAMPLE 
    volatile uint32_t count = 0U;
    volatile uint32_t count1 = 0U;
	
    timer a = {&TIM6, TIM_BUFFER_ARR_ENABLE, TIM_MODE_CONTINUOUS, TIM_UPDATE_INTERRUPT_ENABLE};
	timer_6_7_init(&a);
	timer_6_7_set_counter(&TIM6, 0);
	timer_6_7_set_prescaler(&TIM6, 2097);
	timer_6_7_set_reload(&TIM6, 1000-1);
	timer_6_7_update_enable(&TIM6);
	NVIC_EnableIRQ(TIM6_IRQn);
	timer_6_7_counter_enable(&TIM6);

	timer b = {&TIM7, TIM_BUFFER_ARR_ENABLE, TIM_MODE_CONTINUOUS, TIM_UPDATE_INTERRUPT_ENABLE};
	timer_6_7_init(&b);
	timer_6_7_set_counter(&TIM7, 0);
	timer_6_7_set_prescaler(&TIM7, 2097);
	timer_6_7_set_reload(&TIM7, 1000-1);
	timer_6_7_update_enable(&TIM7);
	NVIC_EnableIRQ(TIM7_IRQn);
	timer_6_7_counter_enable(&TIM7);
	
	char buffer[7] = {0};
	char buffer1[7] = {0};
	Lcd_string_xy(1, 0, "Timer6:");
	Lcd_string_xy(2, 0, "Timer7:");

	while (1)
	{
		sprintf(buffer, "%ld", count);
		Lcd_string_xy(1, 8, buffer);
		sprintf(buffer1, "%ld", count1);
		Lcd_string_xy(2, 8, buffer1);
	}

void TIM6_IRQHandler(void)
{
	count++;
	TIM6.SR &= bit_clear(0); // Clear the flag to exit interrupt
}

void TIM7_IRQHandler(void)
{
	count1++;
	TIM7.SR &= bit_clear(0); // Clear the flag to exit interrupt
}
	*/