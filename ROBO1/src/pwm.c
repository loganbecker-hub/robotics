#include "pwm.h"

void pwm_init(pwm_t *config, TIM2_CHANNEL channel)
{
    float duty_temp = 0.0f;

    // Precaler   
    config->timer->PSC = config->prescaler;
    // Auto Reload
    config->timer->ARR = config->reload;
    // Set to upcounter
    config->timer->CR1 &= bit_clear(4);
    
    if (channel == TIM2_CHANNEL_1)
    {
        // Output compare mode channel 3 
        config->timer->CCMR1 |= bit_set(5) | bit_set(6);
        // Channel Enable
        config->timer->CCER |= bit_set(0);
    }

    else if (channel == TIM2_CHANNEL_2)
    {
        // Output compare mode channel 3 
        config->timer->CCMR1 |= bit_set(13) | bit_set(14);
        // Channel Enable
        config->timer->CCER |= bit_set(4);
    }


    // NOTE : [HANDLE THIS AND UNDERSTAND IT]
    else if (channel == TIM2_CHANNEL_3)
    {
        // Output compare mode channel 3 
        config->timer->CCMR2 |= bit_set(5) | bit_set(6);
        // Channel Enable
        config->timer->CCER |= bit_set(8);
    }

    else if (channel == TIM2_CHANNEL_4)
    {
        // Output compare mode channel 3 
        config->timer->CCMR2 |= bit_set(13) | bit_set(14);
        // Channel Enable
        config->timer->CCER |= bit_set(12);
    }

    // Duty cycle Calculation
    duty_temp = (config->duty / 100.0f) * config->reload;

    // Channel 1
    if (channel == TIM2_CHANNEL_1)
    {
       config->timer->CCR1 = (uint16_t)duty_temp;
    }
    // Channel 2
    else if (channel == TIM2_CHANNEL_2)
    {
       config->timer->CCR2 = (uint16_t)duty_temp;
    }
    // Channel 3
    else if (channel == TIM2_CHANNEL_3)
    {
       config->timer->CCR3 = (uint16_t)duty_temp;
    }
    // Channel 4
    else if (channel == TIM2_CHANNEL_4)
    {
       config->timer->CCR4 = (uint16_t)duty_temp;
    }

    // Update Generation
    config->timer->EGR |= bit_set(0);
}

void pwm_start(pwm_t *config)
{
    // Counter Enable
    config->timer->CR1 |= bit_set(0);
}

void pwm_change_duty_cycle(pwm_t *config, TIM2_CHANNEL channel, uint16_t duty)
{
    float duty_temp = 0.0f;
    // Duty cycle Calculation
    duty_temp = (duty / 100.0f) * config->reload;
    
    if (channel == TIM2_CHANNEL_3)
    {
        config->timer->CCR3 = (uint16_t)duty_temp;
    }

    else if (channel == TIM2_CHANNEL_1)
    {
        config->timer->CCR1 = (uint16_t)duty_temp;
    }

    else if (channel == TIM2_CHANNEL_2)
    {
        config->timer->CCR2 = (uint16_t)duty_temp;
    }

    else if (channel == TIM2_CHANNEL_4)
    {
        config->timer->CCR4 = (uint16_t)duty_temp;
    }

}

void pwm_stop(pwm_t *config)
{
    // Counter Enable
    config->timer->CR1 &= bit_clear(0);
}