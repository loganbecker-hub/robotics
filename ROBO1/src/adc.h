#ifndef ADC_H
#define ADC_H

#include "main.h"

typedef enum
{   
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1 = 1,
    ADC_CHANNEL_2 = 2,
    ADC_CHANNEL_3 = 3,
    ADC_CHANNEL_4 = 4,
    ADC_CHANNEL_5 = 5,
    ADC_CHANNEL_6 = 6,
    ADC_CHANNEL_7 = 7,
    ADC_CHANNEL_8 = 8,
    ADC_CHANNEL_9 = 9,
    ADC_CHANNEL_10 = 10,
    ADC_CHANNEL_11 = 11,
    ADC_CHANNEL_12 = 12,
    ADC_CHANNEL_13 = 13,
    ADC_CHANNEL_14 = 14,
    ADC_CHANNEL_15 = 15,
    ADC_CHANNEL_VREF = 17,
    ADC_CHANNEL_TEMP = 18
}ADC_CHANNEL;

typedef enum
{
    ADC_RES_12_BIT = 0,
    ADC_RES_10_BIT,
    ADC_RES_8_BIT,
    ADC_RES_6_BIT = 3,
}ADC_RES;

// Not done
typedef enum
{
    ADC_MODE_CONTINUOUS,
}ADC_MODE;

// Not done
typedef enum
{
    ADC_TRIGGER_SOFTWARE,
}ADC_TRIG;

// Not done
typedef enum
{
    ADC_ALIGN_RIGHT,
}ADC_ALIGN;

typedef enum
{
    ADC_SAMPLE_1_5 = 0,
    ADC_SAMPLE_3_5,
    ADC_SAMPLE_7_5,
    ADC_SAMPLE_12_5,
    ADC_SAMPLE_19_5 = 4,
    ADC_SAMPLE_39_5,
    ADC_SAMPLE_79_5,
    ADC_SAMPLE_160_5 = 7,
}ADC_SAMPLE;

typedef enum
{
    ADC_PRE_0 = 0,
    ADC_PRE_2,
    ADC_PRE_4,
    ADC_PRE_6,
    ADC_PRE_8,
    ADC_PRE_10,
    ADC_PRE_12,
    ADC_PRE_16 = 7,
    ADC_PRE_32,
    ADC_PRE_64,
    ADC_PRE_128,
    ADC_PRE_256 = 11,
}ADC_PRESCALER;

// Not complete
typedef enum
{
    ADC_INTERRUPT_ENABLED,
    ADC_INTERRUPT_DISABLED,
}ADC_INTERRUPT;

// Not complete
typedef enum
{
    ADC_DMA_ON,
    ADC_DMA_OFF,
}ADC_DMA;

typedef struct adc_tag
{
    ADC_CHANNEL channel;
    ADC_MODE mode;
    ADC_RES res;
    ADC_TRIG trigger;
    ADC_ALIGN align;
    uint8_t calibration;
    ADC_SAMPLE sampling;
    ADC_PRESCALER prescaler;
    ADC_INTERRUPT interrupt;
}adc_t;

void adc_init(adc_t *adc);
void adc_start(adc_t *adc);
// Note: Change to Select Read to select a specific channel
uint16_t adc_read(ADC_CHANNEL channel);


/* Internal CPU temperature Sensor */
#define TEMP130_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF8007E))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF8007A))
#define VDD_CALIB ((uint16_t) (300))
#define VDD_APPLI ((uint16_t) (330))
// Write Test Code for this
int32_t ComputeCpuTemperature(uint32_t measure);

#endif // ADC_H
