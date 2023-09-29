#include "timer.h"
#include "rcc.h"

void timer_6_7_init(timer *timer)
{
    // Timer Clock enable
    if (timer->timer == &TIM6)
    {
        rcc_timer6_clock_enable();
    }
    
    else if (timer->timer == &TIM7)
    {
        rcc_timer7_clock_enable();
    }    
    
    // BUFFER
    if (timer->buffer == TIM_BUFFER_ARR_ENABLE)
    {
        timer->timer->CR1 |= bit_set(7); 
    }
    else if(timer->buffer == TIM_BUFFER_ARR_DISABLE)
    {
        timer->timer->CR1 &= bit_clear(7);
    }

    // MODE
    if (timer->mode == TIM_MODE_CONTINUOUS)
    {
        timer->timer->CR1 &= bit_clear(3);
    }
    
    else if (timer->mode == TIM_MODE_ONE_PULSE)
    {
        timer->timer->CR1 |= bit_set(3);
    }

    // UPDATE
    if (timer->update == TIM_UPDATE_NONE)
    {
        timer->timer->CR1 |= bit_set(2);
    }
    else if (timer->update == TIM_UPDATE_INTERRUPT_ENABLE)
    {
        timer->timer->DIER |= bit_set(0);
    }
    else if(timer->update == TIM_UPDATE_INTERRUPT_DISABLE)
    {
        timer->timer->DIER &= bit_clear(0);
    }
    else if(timer->update == TIM_UPDATE_DMA_ENABLE)
    {
        timer->timer->DIER |= bit_set(8);
    }
    else if(timer->update == TIM_UPDATE_DMA_DISABLE)
    {
        timer->timer->DIER &= bit_clear(8);
    }
 
}

void timer_6_7_update_enable(TIM_TypeDef * timer)
{
    timer->CR1 &= bit_clear(1);
}

void timer_6_7_update_disable(TIM_TypeDef * timer)
{
    timer->CR1 |= bit_set(1);
}

void timer_6_7_counter_enable(TIM_TypeDef * timer)
{
    timer->CR1 |= bit_set(0);
}

void timer_6_7_counter_disable(TIM_TypeDef * timer)
{
    timer->CR1 &= bit_clear(0);
}

void timer_6_7_set_counter(TIM_TypeDef * timer, uint16_t value)
{
    timer->CNT = value;
}

void timer_6_7_set_prescaler(TIM_TypeDef * timer, uint16_t value)
{
    timer->PSC = value;
}

void timer_6_7_set_reload(TIM_TypeDef * timer, uint16_t value)
{
    timer->ARR = value;
}