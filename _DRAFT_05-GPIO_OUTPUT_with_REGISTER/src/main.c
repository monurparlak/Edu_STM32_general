/* GPIO OUTPUT APP - REGISTER LIBRARY
 * TASLAK DOSYADIR !!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void PLL_With_CLOCK_REGISTER()
{
	RCC->CR |= 0x00010000;		    // HSEON (High Speed External) ENABLE
	while(!(RCC->CR & 0x00020000));	// HSEON (High Speed External) FLAG Bekliyor
	RCC->CR |= 0x00080000;			// CSS (Clock System Security) ENABLE

	RCC->PLLCFGR |= 0x00400000;		// PLL (Phase Locked Loop) HSE Seçilir
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL p = 2

	RCC->CFGR |= 0x00000000; 		// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000; 		// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400; 		// APB1 Prescaler = 4
	RCC->CIR  |= 0x00800000; 		// CSS (Clock System Security) FLAG Temizlenir

}

void GPIO_LED_BLINK_REGISTER()
{
	RCC->AHB1ENR = 0x00000008;      // GPIOD portu ENABLE

	GPIOD->MODER = 0x55000000;      // Kart Üstündeki Ledler OUTPUT ayarlandý
	GPIOD->PUPDR = 0x00000000;      // NOPULL
	GPIOD->OTYPER = 0x00000000;     // PUSH PULL
	GPIOD->OSPEEDR = 0xFF000000;    // 100 MHz
}

//Gecikme
void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	PLL_With_CLOCK_REGISTER();
	GPIO_LED_BLINK_REGISTER();

	while (1)
	{
		GPIOD->ODR = 0x0000F000; // ODR (OUTPUT DATA REGISTER) Pinler için Set Edildi
		delay(16800000);

		GPIOD->ODR = 0x00000000; //ODR (OUTPUT DATA REGISTER) Pinler için Reset Edildi
		delay(16800000);
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
