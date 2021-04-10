/* Digital to Analog Converter - DAC - REGISTER LIBRARY
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* For example,
 * If we do an 8-bit reading
 * 2^8 = 256
 * bit value for each voltage
 * 3.3 (Reference Voltage) / 255 (2^n-1) = 0,01294117647   // 3.3 - 1.8 Voltage range
 * Corresponding range to 2.2 Voltage
 * 2.2/0,01294117647 = 170,0000000077  					   // Approach 170
 * Definition range is found*/

int count = 0;

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

	RCC->PLLCFGR |= 0x00400000;		// PLL (Phase Locked Loop) HSE
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL P = 2

	RCC->CFGR    |= 0x00000000; 	// AHB  = 1
	RCC->CFGR    |= 0x00080000; 	// APB2 = 2
	RCC->CFGR    |= 0x00001400; 	// APB1 = 4
	RCC->CIR     |= 0x00800000; 	// CSS (Clock System Security) FLAG Clear
}

void DAC_CONFIG_REGISTER ()
{
	RCC->AHB1ENR |= 0x00000001;		// AHB1 port enabled
	RCC->APB1ENR |= 0x20000000;     // APB1 port enabled for DAC1

	DAC->CR		 |= 0x00000001;		// DAC1 (DAC Channel 1) Enable
	DAC->SWTRIGR |= 0x00000000;		// DAC1 Trigger Disable
	DAC->DHR8R1  |= 0x00000000;		// DAC1 8-bit, Right align, Channel 1
}

int main(void)
{
	PLL_CLOCK_CONFIG_REGISTER ();
	DAC_CONFIG_REGISTER		  ();

	while (1)
	{
		for (count=0; count<255; count++)
		{
			DAC->DHR8R1 = count;
			Delay(168000);
		}

		count = 0;
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
