/* CLOCK CONFIG Ayarlamasý için REGISTER Kodlamasý
 * TASLAK DOSYADIR!!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//168 MHz Çalýþma Durumu Ýçin Gerekli Konfigürasyon
//Buradaki Seçimleri Doðrulamak Ýçin CUBEMX IDE Kullanabilirsiniz
void PLL_With_CLOCK_REGISTER()
{
	RCC->CR |= 0x00010000;	// HSEON (High Speed External) ENABLE
	while(!(RCC->CR & 0x00020000));	// HSEON (High Speed External) FLAG Bekliyor
	RCC->CR |= 0x00080000;	// CSS (Clock System Security) ENABLE
	RCC->AHB1ENR
	RCC->PLLCFGR |= 0x00400000;	// PLL (Phase Locked Loop) HSE Seçilir
	RCC->PLLCFGR |= 0x00000004;	// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;	// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;	// PLL p = 2

	RCC->CFGR |= 0x00000000; // AHB Prescaler = 1
	RCC->CFGR |= 0x00080000; // APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400; // APB1 Prescaler = 4
	RCC->CIR  |= 0x00800000;	 // CSS (Clock System Security) FLAG Temizlenir

}

int main(void)
{
	PLL_With_CLOCK_REGISTER();
	while (1)
	{

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
