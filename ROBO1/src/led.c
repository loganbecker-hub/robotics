#include "led.h"

void Leds_Init(void)
{
    // LEDs
	gpio_pin_t L1 = {GPIO_MODE_OUTPUT, L1_PIN, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_ALT_AF0};
	gpio_init(&LED_PORT, &L1);
	
	gpio_pin_t L2 = {GPIO_MODE_OUTPUT, L2_PIN, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_ALT_AF0};
	gpio_init(&LED_PORT, &L2);

	gpio_pin_t L3 = {GPIO_MODE_OUTPUT, L3_PIN, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_ALT_AF0};
	gpio_init(&LED_PORT, &L3);

	gpio_pin_t L4 = {GPIO_MODE_OUTPUT, L4_PIN, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_ALT_AF0};
	gpio_init(&LED_PORT, &L4);
}

void L1_on(void)
{
    gpio_set(&LED_PORT, L1_PIN);
}
void L1_off(void)
{
    gpio_clear(&LED_PORT, L1_PIN);
}

void L2_on(void)
{
    gpio_set(&LED_PORT, L2_PIN);
}
void L2_off(void)
{
    gpio_clear(&LED_PORT, L2_PIN);
}

void L3_on(void)
{
    gpio_set(&LED_PORT, L3_PIN);
}
void L3_off(void)
{
    gpio_clear(&LED_PORT, L3_PIN);
}

void L4_on(void)
{
    gpio_set(&LED_PORT, L4_PIN);
}

void L4_off(void)
{
    gpio_clear(&LED_PORT, L4_PIN);
}
