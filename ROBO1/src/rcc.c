#include "rcc.h"

void rcc_init(rcc *rcc)
{
    // HSI Clock 
    if (rcc->clock == RCC_CLOCK_HSI_16MHZ)
    {
        // HSI Prescaler 
        if (rcc->prescaler == RCC_PRESCALER_HSI_DISABLE)
        {
            RCC.CR &= bit_clear(3);
            while(RCC.CR & 0x10)
            ;
        }
        RCC.CR |= bit_set(0) | bit_set(1);
        // Wait for HSI ready flag to be set
        while( !(RCC.CR & 0x04) )
        ;
        // Select HSI as SYSTEM clock  
        RCC.CFGR |= bit_set(0);
	    RCC.CFGR &= bit_clear(1);
    }

}

/* Adc clock enable */
void rcc_adc1_clock_enable(void)
{
    RCC.APB2ENR |= RCC_APB2ENR_ADC1EN;
}

/* GPIOx clock enable*/
void rcc_gpioa_clock_enable(void)
{
    RCC.IOPENR |= bit_set(0);
}
void rcc_gpiob_clock_enable(void)
{
    RCC.IOPENR |= bit_set(1);
}
void rcc_gpioc_clock_enable(void)
{
    RCC.IOPENR |= bit_set(2);
}
void rcc_gpiod_clock_enable(void)
{
    RCC.IOPENR |= bit_set(3);
}

/*Timer 6 and 7 */ 
void rcc_timer6_clock_enable(void)
{
    RCC.APB1ENR |= bit_set(4);
}

void rcc_timer7_clock_enable(void)
{
    RCC.APB1ENR |= bit_set(5);
}

/* Sysclock Enable */
void rcc_syscfg_clock_enable(void)
{
    RCC.APB2ENR |= bit_set(0);
}

/* Timer 2 clock enable */
void rcc_tim2_clock_enable(void)
{
    RCC.APB1ENR |= bit_set(0);
}

