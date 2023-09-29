#include "uart.h"

void LPUartInit(uint32_t ClockFreq, uint32_t BaudRate, bool InterruptState)
{
	// Enable LPUART clock
	RCC.APB1ENR |= RCC_APB1ENR_LPUART1EN;
	// Enable GPIOC clock
	RCC.IOPENR |= RCC_IOPENR_GPIOCEN;
	
	// PC0 alternate function
	GPIOC.MODER &= ~(1U<<0);
	GPIOC.MODER |= (1U<<1);
	// PC1 alternate function
	GPIOC.MODER &= ~(1U<<2);
	GPIOC.MODER |= (1U<<3);
	
	// AFR[0] : Pins 0 - 7
	// AFR[1] : Pins 8 - 15
	// AF6 is for LPUART Rx and Tx found in Datasheet PG51
	// 0x600 -- This would right 6 into PC2	
	// PC0 mapped to Rx
	GPIOC.AFR[0] |= 0x06; // Move 6 into PC0
	// PC1 mapped to Tx
	GPIOC.AFR[0] |= 0x60; // Move 6 into PC1
	
	// LPUARTDIV = 256**fck / Baudrate(9600)
	uint32_t div = (256*ClockFreq) / BaudRate; 
	LPUART1.BRR = div;
	
	if(InterruptState)
	{
		/* Note: Enabled LPUART Interrupt */
		LPUART1.CR1 |= (1U<<5 | 1U<<6 | 1U<<7 | 1U<<8);
	}

	// Enable LPUART
	LPUART1.CR1 |= 1U<<0;
	// TE enbaled (transmission enabled)
	LPUART1.CR1 |= 1U<<3;
	// RE enabled (reception enabled)
	LPUART1.CR1 |= 1U<<2;
}

void LPUartSendChar(char character)
{
	LPUART1.TDR = character;
	while(!(LPUART1.ISR & 0x80)) // Wait for data to be shited into the Transmit shift register(TXE)
	;
	while(!(LPUART1.ISR & 0x40)) // Wait for Transmission Completion (TC) which sends all 8 bits to TX pin.
	;
}

void LPUartSendString(char *Message)
{
	while(*Message)
	{
		LPUartSendChar(*Message);
		Message++;
	}
}

void LPUartSendStringIT(char *Message, char **GlobalBuffer)
{
	 // Send the first data point
	LPUART1.TDR = *Message;
	// Use the next memory location
	*GlobalBuffer = ++Message;
	// Re-enable this bit so interrupt can occur, but remove here if issues occur
	LPUART1.CR1 |= USART_CR1_TXEIE;
}

uint32_t LPUartReceiveString(uint32_t Timeout)
{
	//uint32_t current_tick = GetTicks() + Timeout;
	//while(!(LPUART1.ISR & 0x20) & (GetTicks() < current_tick)); // Wait for RXNE flag to be set meaning a character is received
	
	while(!(LPUART1.ISR & 0x20))
	;
	// Over run occurs when receiving a character while RDR was still contains the character i think check again
	return LPUART1.RDR;
}

void LPUartReceiveStringIT(void)
{
	// Enabled IRQ Handler
	__NVIC_EnableIRQ(LPUART1_IRQn);
}


/*****************************
	USART4 Function Definitions 
******************************/

void Uart4Init(uint32_t ClockFreq, uint32_t BaudRate, bool InterruptState)
{
	// Enable USART4 clock
	RCC.APB1ENR |= RCC_APB1ENR_USART4EN;
	// Enable GPIOA clock
	RCC.IOPENR |= RCC_IOPENR_GPIOAEN;
	
	// PA0 alternate function
	GPIOA.MODER &= ~(1U<<0);
	GPIOA.MODER |= (1U<<1);
	// PA1 alternate function
	GPIOA.MODER &= ~(1U<<2);
	GPIOA.MODER |= (1U<<3);
	
	// AFR[0] : Pins 0 - 7
	// AFR[1] : Pins 8 - 15
	// AF6 is for USART Rx and Tx found in Datasheet PG51
	// 0x600 -- This would right 6 into PA2	
	// PA0 mapped to Tx
	GPIOA.AFR[0] |= 0x06; // Move 6 into PA0
	// PA1 mapped to Rx
	GPIOA.AFR[0] |= 0x60; // Move 6 into PA1
	
	// UART4DIV = 256*fck / Baudrate(9600)
	uint32_t div = (256*ClockFreq) / BaudRate; 
	USART4.BRR = div;
	
	if(InterruptState)
	{
		/* Note: Enabled USART4 Interrupt */
		USART4.CR1 |= (1U<<5 | 1U<<6 | 1U<<7 | 1U<<8);
	}

	// Enable USART4
	USART4.CR1 |= 1U<<0;
	// TE enbaled 
	USART4.CR1 |= 1U<<3;
	// RE enbaled 
	USART4.CR1 |= 1U<<2;
}

void Uart4SendChar(char character)
{
	USART4.TDR = character;
	while(!(USART4.ISR & 0x80)) // Wait for data to be shited
	;
	while(!(USART4.ISR & 0x40)) // Wait for Transmission Completion
	;
}
void Uart4SendString(char *Message)
{
	while(*Message)
	{
		Uart4SendChar(*Message);
		Message++;
	}
}

void Uart4SendStringIT(char *Message, char **GlobalBuffer)
{
	 // Send the first data point
	USART4.TDR = *Message;
	// Use the next memory location
	*GlobalBuffer = ++Message;
	// Re-enable this bit so interrupt can occur, but remove here if issues occur
	USART4.CR1 |= USART_CR1_TXEIE;
}

char Uart4ReceiveString(void)
{
	return 'a';
}
char Uart4ReceiveStringIT(void)
{
	return 'a';
}
