#include "systick.h"

static volatile uint32_t Ticks;

uint32_t get_ticks(void)
{
	return Ticks;
}

void SysTick_Handler(void)
{
	Ticks++;
}

void delay(uint32_t ms)
{
	uint32_t current = Ticks + ms;
	while(Ticks < current)
	;
}