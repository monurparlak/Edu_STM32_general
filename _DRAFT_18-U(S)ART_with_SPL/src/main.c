/* **********************************************************************************************************************************************
 ************************************************************************************************************************************************
 *
 * Universal Asynchronous Receiver Transmitter - U(S)ART - Standard Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 * ***********************************************************************************************************************************************
 * ***********************************************************************************************************************************************/


/* **********************************************************************************************************************************************
 * Synchronous Communication: Uses data and clock signals. Data is transmitted simultaneously with the clock signal.
 * Asynchronous Communication: There is no clock signal in the case of data transmission.
 *
 * RS232: UART-USB converters are used since they are not used in current systems.
 *
 * **********************************************************************************************************************************************
 *
 * U(S)ART Communication
 * Data are transmitted by communication packets (frames).
 * Baud Rate: It is the communication speed unit. It is between 300-115200 bps (bits per second). Baud Rate for communication should be equal.
 *
 * 										BaudRate = FCK / 8 x (2-OVR0) x USARTDIV
 * 				(FCK: APB Frequency, OVR8: Oversampling by 8, USARTDIV: Programmed BaudRate Register Value)
 *
 * Frame: There are 8 data bits, 1 start and 1 stop bit
 * Parity Bit: There may also be a validation bit called parity
 * Stop Bit: Activates in 1 or 2 bits.
 *
 * **********************************************************************************************************************************************
 *
 * Full Duplex: Two parties can communicate at the same time
 * Half Duplex: Sequential communication can be made (Radio)
 * Simplex: One-sided communication can be done
 *
 * ***********************************************************************************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

char str[20];

void Delay (uint32_t time)
{
	while (time--);
}

void GPIO_CONFIG_SPL ()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig (GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //Main Port, TX Port, What Operation (USART, I2C, TIMER, ...)

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
}

void UART_CONFIG_SPL ()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStructure.USART_BaudRate			  = 9600; 							// 300-115200 bps (bits per second)
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // RTS: It is the Data Sending of the Computer or Terminal,
																					// CTS: It is the Data Sent by RTS.
	USART_InitStructure.USART_Mode				  = USART_Mode_Tx; 					// Rx: Message (Receive)
																					// Tx: Message (Transmit)
	USART_InitStructure.USART_Parity			  = USART_Parity_No;				// Information Confirms
	USART_InitStructure.USART_StopBits			  = USART_StopBits_1;			    // It is Stop Bit :)
	USART_InitStructure.USART_WordLength		  = USART_WordLength_8b;			// Data Length to Send

	USART_Init (USART2, &USART_InitStructure); 										//Initiallize

	USART_Cmd(USART2, ENABLE);														// USART is Peripheral Unit
}

// Sending Data with USART
// Returns Address to Complete Continuously, Provides Continuity
void USART_Puts (USART_TypeDef* USARTx, volatile char *s)
{
	while (*s)
	{
		while (!(USARTx->SR & 0x00000040));

		USART_SendData(USARTx,*s);
		*s ++;
	}
}

int main(void)
{
	GPIO_CONFIG_SPL ();
	UART_CONFIG_SPL ();

	while (1)
	{
		sprintf (str, "Hello World\n");
		Delay (1680000);
		USART_Puts(USART2, str);
	}
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return -1;
}
