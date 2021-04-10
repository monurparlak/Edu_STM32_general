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
 * 				(FCK: APB Frequency, OVR8: Oversampling by 8, USARTDIV: Programmed BRR Register value)
 *
 * Frame: There are 8 data bits, 1 start and stop bit
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
#include "stdio.h"

char Rx_Buffer [50];
int i=0;

// Delay
void Delay(uint32_t time)
{
	while(time--);
}

void PLL_CLOCK_CONFIG_REGISTER()
{
	RCC->CR 	 |= 0x00010000;		// HSEON (High Speed External) ENABLE
	while(!(RCC->CR & 0x00020000));	// HSEON (High Speed External) waiting for FLAG
	RCC->CR 	 |= 0x00080000;		// CSS   (Clock System Security) ENABLE
	RCC->CR		 |= 0x01000000; 	// PLL ON

	RCC->PLLCFGR |= 0x00400000;		// PLL (Phase Locked Loop) HSE
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL P = 2

	RCC->CFGR    |= 0x00000000; 	// AHB  = 1
	RCC->CFGR    |= 0x00080000; 	// APB2 = 2
	RCC->CFGR    |= 0x00001400; 	// APB1 = 4
	RCC->CIR     |= 0x00800000; 	// CSS (Clock System Security) FLAG Clear
}

void GPIO_CONFIG_REGISTER ()
{
	RCC->AHB1ENR   |= 0x00000002;    			// GPIOB PORT ENABLE

	GPIOB->MODER   |= (2 << 20) | (2 << 22);    // Board up the Pin 10-11 AF. 20 Bits shift left, write 2 (10)
	GPIOB->PUPDR   |= 0x00000000;  				// NOPULL
	GPIOB->OTYPER  |= 0x00000000;    			// PUSH PULL
	GPIOB->AFR[1]  |= 0x00007700;     			// Pin 10 and Pin 11 = AF7
}

void USART_CONFIG_REGISTER ()
{
	RCC->APB1ENR   |= 0x00020000; //USART Pin 18

	USART3->BRR    |= 0x00001112; // BaudRate 9600

	USART3->CR1    |= 0 << 10;	  // Parity DISABLE
	USART3->CR1    |= 0 << 12; 	  // Word Length 8-Bit
	USART3->CR1	   |= 1 << 2;	  // Rx ENABLE
	USART3->CR1    |= 1 << 3;	  // Tx ENABLE
	USART3->CR1    |= 1 << 5; 	  // RxNE Interrupt ENABLE
	USART3->CR2    |= 0 << 12;    // STOP Bit 1
	USART3->CR1    |= 1 << 13;    // USART ENABLE
}

void NVIC_CONFIG_REGISTER ()
{
	NVIC->ISER [1] |= 1 << 7;
}

void USART3_IRQHandler ()
{
	volatile int Str;
	Str = USART3->SR;
	Rx_Buffer[i] = USART3->DR;    // Getting Data from the Data Register
	i ++;
}

void Send_Char (char message)
{
	while (!(USART3->SR & 0x00000080)); // TxF Buffer Status Register Full Detection
	USART3->DR |= message;
}

// Sending Data with USART
// Returns Address to Complete Continuously, Provides Continuity
void Send_Message (char *Str)
{
	while (*Str)
	{
		Send_Char (*Str);
		Str ++;
	}
}

int main(void)
{
	PLL_CLOCK_CONFIG_REGISTER();
	GPIO_CONFIG_REGISTER ();
	USART_CONFIG_REGISTER ();
	NVIC_CONFIG_REGISTER ();

	while (1)
	{
		Send_Message ("Hello World\n");
		for (int k = 0; k <1000; k++);
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
