#include "servo.h"
#include "gpio.h"
#include "rcc.h"

pwm_t * servo1_init(void)
{
    // PB10 as PWM channel 3
	rcc_tim2_clock_enable();

	// Motor 1 (SCK)
	gpio_pin_t PWM = {0};
	PWM.mode = GPIO_MODE_ALT;
	PWM.alt = GPIO_ALT_AF2;
	PWM.pin = GPIO_PIN_10;
	PWM.speed = GPIO_SPEED_VERY_HIGH;
	PWM.pull = GPIO_PULL_NONE;
	PWM.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOB, &PWM);
    
	// we want 50hz frequency 
	static pwm_t motor = {0};
    motor.timer = &TIM2;
    motor.prescaler = 16-1; // (SystemCoreClock / 1000) / 1000) - 1
    motor.reload = 20000; // Produces 20ms. Which is 50hz
    motor.duty = 0;
    pwm_init(&motor, TIM2_CHANNEL_3);
    pwm_start(&motor);

	return &motor;
}

pwm_t * servo2_init(void)
{
    // PB11 as PWM channel 2
	rcc_tim2_clock_enable();

	// Motor 2 (CS)
	gpio_pin_t PWM = {0};
	PWM.mode = GPIO_MODE_ALT;
	PWM.alt = GPIO_ALT_AF2;
	PWM.pin = GPIO_PIN_11;
	PWM.speed = GPIO_SPEED_VERY_HIGH;
	PWM.pull = GPIO_PULL_NONE;
	PWM.type = GPIO_TYPE_PUSH_PULL;
	gpio_init(&GPIOB, &PWM);
    
	// we want 50hz frequency 
	static pwm_t motor = {0};
    motor.timer = &TIM2;
    motor.prescaler = 16-1; // (SystemCoreClock / 1000) / 1000) - 1
    motor.reload = 20000; // Produces 20ms. Which is 50hz
    motor.duty = 0;
    pwm_init(&motor, TIM2_CHANNEL_4);
    pwm_start(&motor);

	return &motor;
}


int theta1(float x)
{
    // Experimental values 
    // y2 = 2500 
    // y1 = 500

    // x2 = 180
    // x1 = 0

    // linear equation  : y(x) = y2 - y1   
    //                           ------- * x  + c 
    //                           x2 - x1   
    //
    //                  : y(x) = 2500 - 500 
    //                           ---------- * x + 500 
    //                           180  -  0 
    
    int y1 = 500;
    int y2 = 2500;

    int x1 = 0;
    int x2 = 180;
    
    // Format of equation changed to ensure the best accuracy 
    int y_x = (((y2 - y1) * x) / (x2-x1)) + y1;
    return y_x;
}