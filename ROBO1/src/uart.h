#ifndef UART_H
#define UART_H

#include "main.h"

/*
	// 25.4.1 LPUART Transmission 
	[Character description]
	1. Program word length M[1:0] -> LPUART_CR1
	2. By default START bit is lOW and STOP bit is HIGH. You can change polarity if needed.
	3. The transmitter and receiver each have bit that needs to be enabled to provide clocking to the pins.
	// 25.4.2 [Transmitter]
	1. Enbale the TE bit to enable the transmitter
	2. Data in transmit shift register is outputted to the TX pin.
	3. The LPUART_TDR register sits between internal bus and transmit shift register.
	4. TE bit must be set before writing data to LPUART_TDR, otherwise data loss and corruption will occur.
	5. Stop bits [12:13] -> LPUART_CR2

	// Character Transmission Procedure
	1. Program the M bits in LPUART_CR1 to define the word length.
	2. Select the desired baud rate using the LPUART_BRR register.
	3. Program the number of stop bits in LPUART_CR2.
	4. Enable the LPUART by writing the UE bit in LPUART_CR1 register to 1.
	5. Select DMA enable (DMAT) in LPUART_CR3 if multibuffer Communication is to take
	place. Configure the DMA register as explained in multibuffer communication.
	6. Set the TE bit in LPUART_CR1 to send an idle frame as first transmission.
	7. Write the data to send in the LPUART_TDR register (this clears the TXE bit). Repeat
	this for each data to be transmitted in case of single buffer.
	8. After writing the last data into the LPUART_TDR register, wait until TC=1. This
	indicates that the transmission of the last frame is complete. This is required for
	instance when the LPUART is disabled or enters the Halt mode to avoid corrupting the
	last transmission.
	// My interrupt understanding 	+ Single byte communication
	1. LPUART_TDR Data is moved into the transmit shift register before TX pin gets it, 
	   and an interrupt will be generated if TXEIE bit is set in LPUART_CR1. 
	   Now you can send new data to the LPUART_TDR register without overwritting previous data.
	2. All 8 bits transmitted from transmit shift register will generate an interrupt if TCIE bit is set in LPUART_CR1.
	   Must be cleared in software by setting TCCF bit in LPUART_ICR or by writing to LPUART_TDR

*/

/* 25.4.3  // LPUART Receiver
	1. Rx line is HIGH, a Start bit Detection by a falling edge, and sampled in the middle as well
	   and if its 1 then Noise Error Flag is set in LPUART_ISR, and no data is sampled until the next
	   start bit is initiated. If '0' is maintained for start bit then data will then be sampled.
	// Character Reception 
	1. Program the M bits in LPUART_CR1 to define the word length.
	2. Select the desired baud rate using the baud rate register LPUART_BRR
	3. Program the number of stop bits in LPUART_CR2.
	4. Enable the LPUART by writing the UE bit in LPUART_CR1 register to 1.
	5. Select DMA enable (DMAR) in LPUART_CR3 if multibuffer communication is to take
	place. Configure the DMA register as explained in multibuffer communication.
	6. Set the RE bit LPUART_CR1. This enables the receiver which begins searching for a
	start bit. 
*/
typedef enum
{
   UART1,
   UART2,
   UART_MAX_CHANNEL
}UartChannel_t;

typedef enum
{
   UART_DISABLE,
   UART_ENABLE,
   UART_MAX_STATE
}UartState_t;

typedef enum
{
   UART_STOP1,
   UART_STOP2,
   UART_MAX_STOP
}UartStop_t;

typedef struct
{
   UartChannel_t 		 UartChannel;
   UartState_t       UartState;
   UartStop_t        StopBits;   
}UartConfig_t;

typedef enum
{
	BAUD_RATE_2400,
	BAUD_RATE_4800,
	BAUD_RATE_9600,
	BAUD_RATE_14400,
	BAUD_RATE_19200,
	BAUD_RATE_38400,
	BAUD_RATE_57600,
	BAUD_RATE_115200
}UART_BAUDRATE;

typedef enum
{
	CLOCK_8MHZ,
	CLOCK_16MHZ,
	CLOCK_24MHZ,
	CLOCK_48MHZ,
	CLOCK_72MHZ
}CLOCK_FREQ;

typedef struct 
{
	USART_TypeDef *Usartx;
	UART_BAUDRATE baud;
	CLOCK_FREQ frequency;
}UartHandle_t;

/* LPUART1 Function Prototypes */
void LPUartInit(uint32_t ClockFreq, uint32_t BaudRate, bool InterruptState);
void LPUartSendChar(char character);
void LPUartSendString(char *Message);
void LPUartSendStringIT(char *Message, char **GlobalBuffer);
uint32_t LPUartReceiveString(uint32_t Timeout);
void LPUartReceiveStringIT(void);

/* USART4 Function Prototypes */
void Uart4Init(uint32_t ClockFreq, uint32_t BaudRate, bool InterruptState);
void Uart4SendChar(char character);
void Uart4SendString(char *Message);
void Uart4SendStringIT(char *Message, char **GlobalBuffer);
char Uart4ReceiveString(void);
char Uart4ReceiveStringIT(void);

#endif // UART_H
