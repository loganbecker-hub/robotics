#include "exti.h"
#include "gpio.h"
#include "rcc.h"

void external(void)
{
	// SYSCFG clock enable
	RCC.APB2ENR |= bit_set(0);
	// EXTI_11 -> EXTICR_4 but index start at 0, hence 2 is used
	SYSCFG.EXTICR[2] |= bit_set(12);
	SYSCFG.EXTICR[2] &= bit_clear(13);
	SYSCFG.EXTICR[2] &= bit_clear(14);
	// unmask EXTI_11
	EXTI.IMR |= bit_set(11);
	// Rising Edge Trigger
	EXTI.RTSR |= bit_set(11);
	// Range 4 - 15 : EXTI11 -> We will test PB11 -> SPI_CS
    NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

// GPIO interrupt Handler for GPIOx 0 - 1 
void EXTI0_1_IRQHandler(void)
{

}

// GPIO interrupt Handler for GPIOx 2 - 3 
void EXTI2_3_IRQHandler(void)
{

}

// GPIO interrupt Handler for GPIOx 4 - 15 
void EXTI4_15_IRQHandler(void)
{
	RCC.IOPENR |= bit_set(1); // Re-enable used peripheral clocks. Except the SYSCFG clock enable which is for GPIO interrupt
	SCB.SCR &= bit_clear(1); // Clear SleepOnExit mode bit
	
    /*
    gpio_toggle(&GPIOB, GPIO_PIN_13);
    if(count == 10 || count == 15) // Turn on SleepOnExit when 10 or 15 button presses occur
	{
	  SCB.SCR |= bit_set(1); // Set SleepOnExit mode bit
	  // Disable all peripheral clocks to save more power
	  RCC.IOPENR = 0x00;
	}
    */
	// Clears the interrupt flag or something to exit ISR
	EXTI.PR |= bit_set(11);
}

