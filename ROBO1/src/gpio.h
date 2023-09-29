#ifndef GPIO_H
#define GPIO_H

#include "main.h"

typedef enum GPIO_MODE
{
    GPIO_MODE_INPUT = 1,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALT,
    GPIO_MODE_ANALOG,
}GPIO_MODE;

typedef enum 
{   
    GPIO_PIN_0 = 0,
    GPIO_PIN_1 = 1,
    GPIO_PIN_2 = 2,
    GPIO_PIN_3 = 3,
    GPIO_PIN_4 = 4,
    GPIO_PIN_5 = 5,
    GPIO_PIN_6 = 6,
    GPIO_PIN_7 = 7,
    GPIO_PIN_8 = 8,
    GPIO_PIN_9 = 9,
    GPIO_PIN_10 = 10,
    GPIO_PIN_11 = 11,
    GPIO_PIN_12 = 12,
    GPIO_PIN_13 = 13,
    GPIO_PIN_14 = 14,
    GPIO_PIN_15 = 15,
}GPIO_PIN;

typedef enum
{
    GPIO_TYPE_PUSH_PULL = 1,
    GPIO_TYPE_OPEN_DRAIN,
}GPIO_TYPE;

typedef enum
{
    GPIO_SPEED_LOW = 1,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH,
}GPIO_SPEED;

typedef enum
{
    GPIO_PULL_NONE = 1,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
    GPIO_PULL_RESERVED,
}GPIO_PULL;

typedef enum
{
    GPIO_ALT_AF0 = 1,
    GPIO_ALT_AF1,
    GPIO_ALT_AF2,
    GPIO_ALT_AF3,
    GPIO_ALT_AF4,
    GPIO_ALT_AF5,
    GPIO_ALT_AF6,
    GPIO_ALT_AF7,
}GPIO_ALT;

typedef struct gpio_pin_t
{   
    GPIO_MODE mode;
    GPIO_PIN pin;
    GPIO_TYPE type;
    GPIO_SPEED speed;
    GPIO_PULL pull;
    GPIO_ALT alt;
}gpio_pin_t;

/**
 * @brief GPIO initialization
 * 
 * @param gpiox Defines which GPIO to use
 * @param pin   A structure that contains the Pin configuration information
 */
void gpio_init(GPIO_TypeDef *gpiox, gpio_pin_t *pin);

/**
 * @brief Returns if GPIO Pin is 1 or 0
 * 
 * @param gpiox Defines which GPIO to use
 * @param pin   Defines which GPIO Pin to read
 * @return bool 
 */
bool gpio_read(GPIO_TypeDef *gpiox, GPIO_PIN pin);

/**
 * @brief Sets a GPIO Pin to 1
 * 
 * @param gpiox Defines which GPIO to use
 * @param pin   Defines which GPIO Pin to Set
 */
void gpio_set(GPIO_TypeDef *gpiox, GPIO_PIN pin);

/**
 * @brief Clear a GPIO Pin to 0
 * 
 * @param gpiox Defines which GPIO will be used
 * @param pin   Defines which GPIO Pin to Clear
 */
void gpio_clear(GPIO_TypeDef *gpiox, GPIO_PIN pin);

/**
 * @brief Toggles a GPIO Pin
 *  
 * @param gpiox Defines which GPIO will be used
 * @param pin   Defines which GPIO Pin to toggle
 */
void gpio_toggle(GPIO_TypeDef *gpiox, GPIO_PIN pin);

#endif // GPIO_H
