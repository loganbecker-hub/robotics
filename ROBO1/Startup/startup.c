/* 1. Create a vector table for MCU. MCU specific
	 2.	Write a startup code which initializes .data and .bss section in SRAM
	 3. Call main()
*/
#include <stdint.h>

#define SRAM_START 		0x20000000U
#define SRAM_SIZE	 		(20 * 1024) // 20KB
#define SRAM_END			((SRAM_START) + (SRAM_SIZE))

#define STACK_START		SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);
void __libc_init_array();

// Gets executed with every reset of the MCU button pressed
void Reset_Handler(void);

// Handles all Handlers unless Override is implemented
void Error_Handler(void);

// Alias 		 - When these handlers are called they all goto "Error_Handler()"
// Weak      - Allows you to override these Handlers with their real names in main.c  
void NMI_Handler(void)			 __attribute__((weak, alias("Error_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Error_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Error_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Error_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Error_Handler")));

void WWDG_IRQHandler(void) __attribute__((weak, alias("Error_Handler"))); // IRQ Handler
void PVD_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void RCC_CRS_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void DMA1_Channel2_3_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void DMA1_Channel4_7_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void ADC_COMP_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void LPTIM1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void USART4_5_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM21_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void I2C3_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void TIM22_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));
void LPUART1_IRQHandler(void) __attribute__((weak, alias("Error_Handler")));

/* The Vector Table will automatically be stored in ".data"
	 section, therefore we must tell the compiler to store it
	 in another user section that we will create ".vector".
	 
	 Note: Please refer to the Cortex-M0+ manual to see the 
	 			 actual vector interrupt service routine,
	 			 else it will constantly jump to Error_Handler()
	 			 if the vector table is wrongly configured 
*/ 
uint32_t vector_table[] __attribute__((section(".vector"))) = 
{
	STACK_START,
	(uint32_t)Reset_Handler,  // System Exception Handlers Start Here
	(uint32_t)NMI_Handler,
	(uint32_t)HardFault_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(uint32_t)SVC_Handler,
	0,
	0,
	(uint32_t)PendSV_Handler,
	(uint32_t)SysTick_Handler,
	(uint32_t)WWDG_IRQHandler, // IRQ Handlers Start Here
	(uint32_t)PVD_IRQHandler,
	(uint32_t)RTC_IRQHandler,
	(uint32_t)FLASH_IRQHandler,
	(uint32_t)RCC_CRS_IRQHandler,
	(uint32_t)EXTI0_1_IRQHandler,
	(uint32_t)EXTI2_3_IRQHandler,
	(uint32_t)EXTI4_15_IRQHandler,
	0,
	(uint32_t)DMA1_Channel1_IRQHandler,
	(uint32_t)DMA1_Channel2_3_IRQHandler,
	(uint32_t)DMA1_Channel4_7_IRQHandler,
	(uint32_t)ADC_COMP_IRQHandler,
	(uint32_t)LPTIM1_IRQHandler,
	(uint32_t)USART4_5_IRQHandler,
	(uint32_t)TIM2_IRQHandler,
	(uint32_t)TIM3_IRQHandler,
	(uint32_t)TIM6_IRQHandler,
	(uint32_t)TIM7_IRQHandler,
	0,
	(uint32_t)TIM21_IRQHandler,
	(uint32_t)I2C3_IRQHandler,
	(uint32_t)TIM22_IRQHandler,
	(uint32_t)I2C1_IRQHandler,
	(uint32_t)I2C2_IRQHandler,
	(uint32_t)SPI1_IRQHandler,
	(uint32_t)SPI2_IRQHandler,
	(uint32_t)USART1_IRQHandler,
	(uint32_t)USART2_IRQHandler,
	(uint32_t)LPUART1_IRQHandler,
};

/* Standard 32-bit address register definition macro */
#define hw32(address) (*((volatile uint32_t *)(address)))

// Define here for testing when the Error_Handler() is invoked
#define GPIOB_test  hw32(0x50000418)
#define gpio_set(pin)    GPIOB_test |= 1U<<pin;

void Error_Handler(void)
{
	gpio_set(15);
}

void Reset_Handler(void)
{
	// copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	// Init the .bss section to zero in SRAM
	uint8_t *pDst = (uint8_t *)&_sdata;
	uint8_t *pSrc = (uint8_t *)&_la_data;
	for(uint32_t i = 0; i < size; i++)
	{
		*pDst++ = *pSrc++;
	}

	//Init the .bss section to zero in RAM
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	pDst = (uint8_t*)&_sbss;
	for(uint32_t i =0 ; i < size ; i++)
	{
		*pDst++ = 0;
	}

	// Call init function of std library here
	__libc_init_array();

	// call main()
	main();
}
