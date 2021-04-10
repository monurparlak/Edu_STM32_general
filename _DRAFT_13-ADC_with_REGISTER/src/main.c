/* Analog to Digital Converter - ADC - REGISTER LIBRARY
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* For example,
 * If we do an 8-bit reading
 * 2^8 = 512
 * Voltage value for each bit
 * 3.3 (Reference Voltage) / 511 (2^n-1) = 0,0064453125   // 3.6 - 1.8 range
 * Corresponding voltage to 500
 * 500*0,0064453125 = 3,22265625 Voltage
 * Voltage is found*/

uint8_t ADC_DATA;

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

void GPIO_CONFIG_REGISTER ()
{
	RCC->AHB1ENR   = 0x00000001;    // GPIOA PORT ENABLE

	GPIOD->MODER   = 0x00000003;    // Board up the Pin 0
	GPIOD->PUPDR   = 0x00000000;    // NOPULL
	GPIOD->OTYPER  = 0x00000000;    // PUSH PULL
	GPIOD->OSPEEDR = 0x00000003;    // 100 MHz to Pin 0
}

void ADC_CONFIG_REGISTER ()
{
	RCC->APB2ENR  |= 0x00000100;    // APB2 port enabled for ADC1

	ADC1->CR1     |= 0x00000000;  	// 12-bit (15 ADCCLOCK Cycles) Resolution
	ADC1->CR2     |= 0x00000001;	// ADC Activited
	ADC1->SMPR2   |= 0x00000008;	// 84 Cycles writed

	ADC->CCR      |= 0x00000000;    // PCLK2 divided by 2 = 84/2 = 42 MHz


}

uint8_t Read_ADC ()
{
	uint8_t reg;

	ADC1->CR2     |= 0x40000000; // Start Conversion  of regular channels, ON

	/* The loop has been started continuously.
	 * If not taken, he waited until his field.
	 * When received, it is reset and repeated*/
	while (!(ADC1->SR & 0x00000002));
	reg = ADC1->DR;
	return reg;
}

int main(void)
{
	PLL_CLOCK_CONFIG_REGISTER ();
	GPIO_CONFIG_REGISTER      ();
	ADC_CONFIG_REGISTER		  ();

	while (1)
	{
		ADC_DATA = Read_ADC ();

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
