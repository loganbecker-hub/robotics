#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "adc.h"
#include "exti.h"
#include "syscfg.h"
#include "pwm.h"
#include "uart.h"
#include "i2c.h"
#include "led.h"
#include "servo.h"
#include "systick.h"

int main(void)
{
	// Clock setup
	rcc sysclock = {RCC_CLOCK_HSI_16MHZ, RCC_PRESCALER_HSI_DISABLE};
	rcc_init(&sysclock);

	// Systick setup
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	// Led setup
	Leds_Init();

	// Servo 1 setup
	// Every 1000 ticks is 1ms 
	pwm_t * servo1 = servo1_init();
	pwm_t * servo2 = servo2_init();

	while (1)
	{
		L1_on();
		delay(100);
		L1_off();
		delay(100);

		// Servo SG90 -> rotation (BASE)		
		servo1->timer->CCR3 = theta1(0.0);
		delay(1500);
		servo1->timer->CCR3 = theta1(180.0); 
		delay(1500);

		// ARM 
		servo2->timer->CCR4 = theta1(0.0);
		delay(1500);
		servo2->timer->CCR4 = theta1(90.0);
		delay(1500);
		servo2->timer->CCR4 = theta1(180.0);
		delay(1500);
	}	
}