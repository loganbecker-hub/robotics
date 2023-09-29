#include "dc_motor.h"
#include "pwm.h"
#include "gpio.h"
#include "rcc.h"

static volatile uint16_t motor_speed = 0;
static volatile uint16_t motor_speed_2 = 0;
static volatile uint16_t motor_speed_3 = 0;
static volatile uint16_t motor_speed_4 = 0;

// Motors 
static pwm_t motor = {0};
static pwm_t motor_2 = {0};
static pwm_t motor_3 = {0};
static pwm_t motor_4 = {0};

void dc_motor_init(void)
{
    // PB10 as PWM channel 3
	rcc_tim2_clock_enable();

	// Motor 1 (SCK)
	gpio_pin_t PWM = {0};
	PWM.mode = GPIO_MODE_ALT;
	PWM.alt = GPIO_ALT_AF2;
	PWM.pin = GPIO_PIN_10;
	PWM.speed = GPIO_SPEED_LOW;
	PWM.pull = GPIO_PULL_NONE;
	PWM.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOB, &PWM);
    
    motor.timer = &TIM2;
    motor.prescaler = 15; // (SystemCoreClock / 1000 / 1000) - 1
    motor.reload = 1000;
    motor.duty = 0;
    pwm_init(&motor, TIM2_CHANNEL_3);
    pwm_start(&motor);
	
	// Motor 2
	gpio_pin_t PWM_2 = {0};
	PWM_2.mode = GPIO_MODE_ALT;
	PWM_2.alt = GPIO_ALT_AF2;
	PWM_2.pin = GPIO_PIN_0;
	PWM_2.speed = GPIO_SPEED_LOW;
	PWM_2.pull = GPIO_PULL_NONE;
	PWM_2.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOA, &PWM_2);
		GPIOA.AFR[0] |= bit_set(1); // Bit 0 - 3   
	// Fix GPIOx_AFR[0] or pin < 8 configuration & TEST CASES as well 
	
    motor_2.timer = &TIM2;
    motor_2.prescaler = 15; // (SystemCoreClock / 1000 / 1000) - 1
    motor_2.reload = 1000;
    motor_2.duty = 0;
    pwm_init(&motor_2, TIM2_CHANNEL_1);
    pwm_start(&motor_2); 

	// Motor 3
	gpio_pin_t PWM_3 = {0};
	PWM_3.mode = GPIO_MODE_ALT;
	PWM_3.alt = GPIO_ALT_AF2;
	PWM_3.pin = GPIO_PIN_1;
	PWM_3.speed = GPIO_SPEED_LOW;
	PWM_3.pull = GPIO_PULL_NONE;
	PWM_3.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOA, &PWM_3); 
		GPIOA.AFR[0] |= bit_set(5); // bit 4 -7 
	
	motor_3.timer = &TIM2;
    motor_3.prescaler = 15; // (SystemCoreClock / 1000 / 1000) - 1
    motor_3.reload = 1000;
    motor_3.duty = 0;
    pwm_init(&motor_3, TIM2_CHANNEL_2);
	pwm_start(&motor_3); 
	
	// Motor 4 (CS)
	gpio_pin_t PWM_4 = {0};
	PWM_4.mode = GPIO_MODE_ALT;
	PWM_4.alt = GPIO_ALT_AF2;
	PWM_4.pin = GPIO_PIN_11;
	PWM_4.speed = GPIO_SPEED_LOW;
	PWM_4.pull = GPIO_PULL_NONE;
	PWM_4.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOB, &PWM_4);
    
    motor_4.timer = &TIM2;
    motor_4.prescaler = 15; // (SystemCoreClock / 1000 / 1000) - 1
    motor_4.reload = 1000;
    motor_4.duty = 0;
    pwm_init(&motor_4, TIM2_CHANNEL_4);
    pwm_start(&motor_4);
}

void dc_motor_1_full_run(uint8_t speed)
{
	motor_speed = 100;
	pwm_change_duty_cycle(&motor, TIM2_CHANNEL_3, speed);
}
void dc_motor_2_full_run(uint8_t speed)
{
	pwm_change_duty_cycle(&motor_2, TIM2_CHANNEL_1, speed);
}
void dc_motor_3_full_run(uint8_t speed)
{
	pwm_change_duty_cycle(&motor_3, TIM2_CHANNEL_2, speed);
}
void dc_motor_4_full_run(uint8_t speed)
{
	pwm_change_duty_cycle(&motor_4, TIM2_CHANNEL_4, speed);
}

void dc_motor_run(void)
{
	// Now Create a Hardware Abstraction Layer (HAL) for the DC motor speed control
	if (motor_speed > 100)
	{	
		motor_speed = 0;
		pwm_change_duty_cycle(&motor, TIM2_CHANNEL_3, motor_speed);
	}
	else
	{
		motor_speed += 25;
		pwm_change_duty_cycle(&motor, TIM2_CHANNEL_3, motor_speed);
	}

	// Now Create a Hardware Abstraction Layer (HAL) for the DC motor speed control
	if (motor_speed_2 > 100)
	{	
		motor_speed_2 = 0;
		pwm_change_duty_cycle(&motor_2, TIM2_CHANNEL_1, motor_speed_2);
	}
	else
	{
		motor_speed_2 += 25;
		pwm_change_duty_cycle(&motor_2, TIM2_CHANNEL_1, motor_speed_2);
	}

	// Now Create a Hardware Abstraction Layer (HAL) for the DC motor speed control
	if (motor_speed_3 > 100)
	{	
		motor_speed_3 = 0;
		pwm_change_duty_cycle(&motor_3, TIM2_CHANNEL_2, motor_speed_3);
	}
	else
	{
		motor_speed_3 += 25;
		pwm_change_duty_cycle(&motor_3, TIM2_CHANNEL_2, motor_speed_3);
	}

	// Now Create a Hardware Abstraction Layer (HAL) for the DC motor speed control
	if (motor_speed_4 > 100)
	{	
		motor_speed_4 = 0;
		pwm_change_duty_cycle(&motor_4, TIM2_CHANNEL_4, motor_speed_4);
	}
	else
	{
		motor_speed_4 += 25;
		pwm_change_duty_cycle(&motor_4, TIM2_CHANNEL_4, motor_speed_4);
	}
}