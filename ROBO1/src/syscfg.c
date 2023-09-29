#include "syscfg.h"
#include "rcc.h"

void syscfg_gpio_0_15(SYS_GPIO gpiox, GPIO_PIN pinx)
{
    uint8_t temp = 0x00;
    rcc_syscfg_clock_enable();
    
    if ( (pinx >=0) && (pinx <= 3) )
    {
        SYSCFG.EXTICR[1] &= ~((0xFF)<<(temp*4)); 
        if(pinx > 0U)
        {
            SYSCFG.EXTICR[1] |= gpiox<<(pinx*4);
        }
    }
    
    else if ( (pinx >= 4) && (pinx <= 7) )
    {
        temp = pinx%4;
        SYSCFG.EXTICR[2] &= ~((0xFF)<<(temp*4)); 
        if(temp > 0)
        {
            SYSCFG.EXTICR[2] |= gpiox<<(temp*4);
        }        
    }

    else if ( (pinx >= 8) && (pinx <= 11) )
    {
        temp = pinx%8;
        SYSCFG.EXTICR[3] &= ~((0xFF)<<(temp*4)); 
        if (temp > 0)
        {
            SYSCFG.EXTICR[3] |= gpiox<<(temp*4);
        }      
    }

    else if ( (pinx >= 12) && (pinx <= 15) )
    {
        temp = pinx%12;
        SYSCFG.EXTICR[4] &= ~((0xFF)<<(temp*4));
        if (temp > 0)
        {
            SYSCFG.EXTICR[4] |= gpiox<<(temp*4);
        }  
            
    }
    
}