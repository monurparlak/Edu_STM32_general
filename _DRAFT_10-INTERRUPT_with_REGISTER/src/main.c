/* INTERRUPT - REGISTER LIBRARY
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Delay (uint32_t time)
{
	while (time--);
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

	RCC->CFGR    |= 0x00000000; 	// AHB Prescaler = 1
	RCC->CFGR    |= 0x00080000; 	// APB2 Prescaler = 2
	RCC->CFGR    |= 0x00001400; 	// APB1 Prescaler = 4
	RCC->CIR     |= 0x00800000; 	// CSS (Clock System Security) FLAG Clear
}

void LED_CONFIG_REGISTER ()
{
	RCC->AHB1ENR = 0x00000008;      // GPIOD portu ENABLE

	GPIOD->MODER = 0x55000000;      // Board up the Leds OUTPUT
	GPIOD->PUPDR = 0x00000000;      // NOPULL
	GPIOD->OTYPER = 0x00000000;     // PUSH PULL
	GPIOD->OSPEEDR = 0xFF000000;    // 100 MHz
}

void BUTTON_CONFIG_REGISTER ()
{
	RCC->AHB1ENR = 0x00000001;      // GPIOA port ENABLE

	GPIOD->MODER = 0x55000000;      // Board up the BUTTON INPUT
	GPIOD->PUPDR = 0x00000000;      // NOPULL
	GPIOD->OTYPER = 0x00000000;     // PUSH PULL
	GPIOD->OSPEEDR = 0xFF000000;    // 100 MHz
}

void EXTI_CONFIG_REGISTER ()
{
	RCC->APB2ENR  	   = 0x00004000;  // EXTI Interrupt ENABLE
	SYSCFG->EXTICR [0] = 0x00000000;  // GPIOA Port Pins Activited

	NVIC_EnableIRQ (EXTI0_IRQn);	  // NVIC Priority assigned
	NVIC_SetPriority (EXTI0_IRQn, 0); // NVIC Priority selectivity
	EXTI->IMR          = 0x00000001;  // Activited for PA1
	EXTI->RTSR         = 0x00000001;  // Select Rising edge
}

void EXTI0_IRQHandler ()
{
	if (EXTI->PR & 0x00000001) 	 // Really activited? - First Bit Activited
	{
		GPIOD->ODR = 0x0000F000; // All LED's (12-13-14-15) pin activited
		Delay (16800000);

		EXTI->PR = 0x00000001;   // FLAG Clear
	}
}

int main(void)
{
	LED_CONFIG_REGISTER	  	  ();
	BUTTON_CONFIG_REGISTER    ();
	PLL_CLOCK_CONFIG_REGISTER ();
	EXTI_CONFIG_REGISTER      ();


	while (1)
	{
		GPIOD->ODR = 0x00001000; // GPIO Pin 12 Activited
		Delay (16800000); // approach 1 second
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
