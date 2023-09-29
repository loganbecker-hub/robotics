#include "adc.h"
#include "rcc.h"

// Moving bit manipulations 
// on top may help it from 
// reconfiguring other bits
// in registers. (e.g., Data Resolution affected "CONTINOUS MODE - bit(13)")
// Moving it before "MODE selection helped"
void adc_init(adc_t *adc)
{
    // ADC clock enabled
    rcc_adc1_clock_enable();

    adc->calibration = 0U;
    
    // ADC Clock prescaler
    if (adc->prescaler > 11)
    {
        ADC1_COMMON.CCR = 0x00 << 18;
    }
    else
    {
        ADC1_COMMON.CCR = adc->prescaler << 18;
    }

    // Channel selection
    if (adc->channel == ADC_CHANNEL_TEMP)
    {
        ADC1_COMMON.CCR |= bit_set(23);
    }
    /*
    else if (adc->channel == ADC_CHANNEL_VREF)
    {
        ADC1_COMMON.CCR |= bit_set(25);
    }
    */
    ADC1.CHSELR |= bit_set(adc->channel);
    
    
    
    // Data Resolution
    if (adc->res > ADC_RES_6_BIT)
    {
        ADC1.CFGR1 &= bit_clear(3);
        ADC1.CFGR1 &= bit_clear(4);
    }
    else
    {
        ADC1.CFGR1 = adc->res << 3;
    }

    // Mode Selection
    if (adc->mode == ADC_MODE_CONTINUOUS)
    {
        ADC1.CFGR1 |= ADC_CFGR1_CONT;
    }
    
    // Trigger Selection
    if (adc->trigger == ADC_TRIGGER_SOFTWARE)
    {
        ADC1.CFGR1 &= bit_clear(10);
        ADC1.CFGR1 &= bit_clear(11);
    }
    
    // Alignment (Left / Right)
    if (adc->align == ADC_ALIGN_RIGHT)
    {
        ADC1.CFGR1 &= bit_clear(5);
    }

    // Sampling time
    if (adc->sampling > 7)
    {
        ADC1.SMPR = 0x00;
    }
    else
    {
        ADC1.SMPR = adc->sampling << 0;
    }

    // Interrupt 
    if (adc->interrupt == ADC_INTERRUPT_ENABLED)
    {
        // End of Conversion Enabled
	    ADC1.IER = ADC_IER_EOCIE;

	    NVIC_EnableIRQ(ADC1_COMP_IRQn);
	    NVIC_SetPriority(ADC1_COMP_IRQn, 0);
    }

}

void adc_start(adc_t *adc)
{
    // ADC calibration turned on 
    ADC1.CR |= ADC_CR_ADCAL;
    // Wait for Calibration to complete
    while(!(ADC1.ISR & ADC_ISR_EOCAL))
    ;
    // Store the calibration value, when ADC peripheral disabled,etc.
    // To increase setup time again, and so on.
    adc->calibration = ADC1.DR;

    // Enable the ADC
    ADC1.CR |= ADC_CR_ADEN;
    // Wait for ADC to become Ready for conversion
    while(!(ADC1.ISR & ADC_ISR_ADRDY))
    ;

    // Start conversion for the ADC
    ADC1.CR |= ADC_CR_ADSTART;
}

uint16_t adc_read(ADC_CHANNEL channel)
{
    uint16_t value = 0U;
    //ADC1.CHSELR |= bit_set(channel);
    // Wait for End of Conversion

    while(!(ADC1.ISR & ADC_ISR_EOC))
    ;
    value = ADC1.DR;
    return value;
}

// From Reference Manual
int32_t ComputeCpuTemperature(uint32_t measure)
{
	int32_t temperature;
	temperature = ((measure * VDD_APPLI / VDD_CALIB) - (int32_t) *TEMP30_CAL_ADDR );
	temperature = temperature * (int32_t)(130 - 30);
	temperature = temperature / (int32_t)(*TEMP130_CAL_ADDR - *TEMP30_CAL_ADDR);
	temperature = temperature + 30;
	return(temperature);
}

