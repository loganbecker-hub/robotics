#include "gpio.h"
#include "rcc.h"

// Functions that should remain PRIVATE to this GPIO Module
static void gpio_init_clock(GPIO_TypeDef * const gpiox);
static void gpio_init_mode(GPIO_TypeDef *gpiox, gpio_pin_t *config);
static void gpio_init_type(GPIO_TypeDef *gpiox, gpio_pin_t *config);
static void gpio_init_speed(GPIO_TypeDef *gpiox, gpio_pin_t *config);
static void gpio_init_pull(GPIO_TypeDef *gpiox, gpio_pin_t *config);
static void gpio_init_alt(GPIO_TypeDef *gpiox, gpio_pin_t *config);

static void gpio_init_clock(GPIO_TypeDef * const gpiox)
{
    // GPIO's clock setup
    if(gpiox == &GPIOA)
    {
        rcc_gpioa_clock_enable();        
    }
    else if(gpiox == &GPIOB)
    {
        rcc_gpiob_clock_enable();
    }
    else if(gpiox == &GPIOC)
    {
        rcc_gpioc_clock_enable();
    }
    else if(gpiox == &GPIOD)
    {
        rcc_gpiod_clock_enable();
    }
}

static void gpio_init_mode(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{
    if ((config->mode == GPIO_MODE_OUTPUT) || (config->mode == GPIO_MODE_ANALOG))
    {
        gpiox->MODER |= bit_set(((config->pin)*2));  
    }
    else
    {
        gpiox->MODER &= bit_clear((config->pin*2)); 
    }

    if ((config->mode == GPIO_MODE_ALT) || (config->mode == GPIO_MODE_ANALOG))
    {
        gpiox->MODER |= bit_set(((config->pin*2)+1));
    }
    else
    {
        gpiox->MODER &= bit_clear(((config->pin *2)+1));
    }
    
}
static void gpio_init_type(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{
    if(config->type == GPIO_TYPE_PUSH_PULL)
    {
        gpiox->OTYPER &= bit_clear(config->pin);
    }
    else
    {
        gpiox->OTYPER |= bit_set(config->pin); 
    }
}
static void gpio_init_speed(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{
    if ((config->speed == GPIO_SPEED_LOW) || (config->speed == GPIO_SPEED_HIGH))
    {
        gpiox->OSPEEDR &= bit_clear((config->pin*2)); 
    }
    else
    {
        gpiox->OSPEEDR |= bit_set((config->pin*2));
    }

    if ((config->speed == GPIO_SPEED_LOW) || (config->speed == GPIO_SPEED_MEDIUM))
    {
        gpiox->OSPEEDR &= bit_clear(((config->pin*2)+1));
    }
    else
    {
        gpiox->OSPEEDR |= bit_set(((config->pin*2)+1));
    }
}
static void gpio_init_pull(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{   
    if ( (config->pull == GPIO_PULL_NONE) || (config->pull == GPIO_PULL_DOWN))
    {
        gpiox->PUPDR &= bit_clear((config->pin*2));
    }
    else
    {
        gpiox->PUPDR |= bit_set((config->pin*2));   
    }

    if ( (config->pull == GPIO_PULL_NONE) || (config->pull == GPIO_PULL_UP))
    {
        gpiox->PUPDR &= bit_clear(((config->pin*2)+1));
    }
    else
    {
        gpiox->PUPDR |= bit_set(((config->pin*2)+1)); 
    }
}
static void gpio_init_alt(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{
    bool index = 0;
    if(config->pin >= 8)
    {
        index = 1;
    }    
    
    if ( (config->alt == GPIO_ALT_AF0) || (config->alt == GPIO_ALT_AF2) || (config->alt == GPIO_ALT_AF4) || (config->alt == GPIO_ALT_AF6))
    {
        gpiox->AFR[index] &= bit_clear(((config->pin - 8)*4)); 
    }
    else
    {
        gpiox->AFR[index] |= bit_set(((config->pin - 8)*4)); 
    }
    
    if ( (config->alt == GPIO_ALT_AF0) || (config->alt == GPIO_ALT_AF1) || (config->alt == GPIO_ALT_AF4) || (config->alt == GPIO_ALT_AF5))
    {
        gpiox->AFR[index] &= bit_clear((((config->pin - 8)*4)+1));
    }
    else
    {
        gpiox->AFR[index] |= bit_set((((config->pin - 8)*4)+1)); 
    }

    if ( (config->alt == GPIO_ALT_AF0) || (config->alt == GPIO_ALT_AF1) || (config->alt == GPIO_ALT_AF2) || (config->alt == GPIO_ALT_AF3))
    {
        gpiox->AFR[index] &= bit_clear((((config->pin - 8)*4)+2));
    }
    else
    {
        gpiox->AFR[index] |= bit_set((((config->pin - 8)*4)+2)); 
    }
    
}

void gpio_init(GPIO_TypeDef *gpiox, gpio_pin_t *config)
{   
    // Clock Setup
    gpio_init_clock(gpiox);
    // Mode configuration
    gpio_init_mode(gpiox, config);
    // Type configuration
    gpio_init_type(gpiox, config);    
    // Speed Configuration
    gpio_init_speed(gpiox, config);
    // Pull Configuration 
    gpio_init_pull(gpiox, config);
    // Alternate Configuration Double check with "GPIO_MODE_ALT"
    gpio_init_alt(gpiox, config);
}

bool gpio_read(GPIO_TypeDef *gpiox, GPIO_PIN pin)
{
    return (bool)(gpiox->IDR & bit_set(pin));
}

void gpio_set(GPIO_TypeDef *gpiox, GPIO_PIN pin)
{
    gpiox->BSRR |= bit_set(pin);
}

void gpio_clear(GPIO_TypeDef *gpiox, GPIO_PIN pin)
{
    gpiox->BRR |= bit_set(pin);
}

void gpio_toggle(GPIO_TypeDef *gpiox, GPIO_PIN pin)
{
    gpiox->ODR ^= bit_set(pin);
}
