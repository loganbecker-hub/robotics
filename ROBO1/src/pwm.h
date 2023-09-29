#ifndef PWM_H
#define PWM_H

#include "main.h"

// Not complete
typedef enum
{
    TIM2_CHANNEL_1 = 0,
    TIM2_CHANNEL_2,
    TIM2_CHANNEL_3,
    TIM2_CHANNEL_4,
}TIM2_CHANNEL;

typedef struct pwm_tag
{
    TIM_TypeDef *timer;
    uint16_t prescaler;
    uint16_t reload;
    uint16_t duty;
}pwm_t;

// Return boolean to indicate that wrong timer was passed!
void pwm_init(pwm_t *config, TIM2_CHANNEL channel);
// Verify how to start different motors
void pwm_start(pwm_t *config);
void pwm_change_duty_cycle(pwm_t *config, TIM2_CHANNEL channel, uint16_t duty);
// Verify how to stop different motors
void pwm_stop(pwm_t *config);

#endif // PWM_H
