/*BUTTON CONTROL REGISTER
 * TASLAK DOSYADIR !!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int counter = 0;

void PLL_CLOCK_REGISTER()
{
	RCC->CR |= 0x00010000;	//HSEON (High Speed External) ENABLE
	while(!(RCC->CR & 0x00020000));	//HSEON (High Speed External) FLAG Bekliyor
	RCC->CR |= 0x00080000;	//CSS (Clock System Security) ENABLE

	RCC->PLLCFGR |= 0x00400000;	//PLL (Phase Locked Loop) HSE Seçilir
	RCC->PLLCFGR |= 0x00000004;	//PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;	//Pll N = 168
	RCC->PLLCFGR |= 0x00000000;	//PLL P = 2

	RCC->CFGR |= 0x00000000; //AHB Prescaler = 1
	RCC->CFGR |= 0x00080000; //APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400; //APB1 Prescaler = 4
	RCC->CIR |= 0x00800000;	 //CSS (Clock System Security) FLAG Temizlenir
}

void LED_CONFIG_REGISTER ()
{
	RCC->AHB1ENR = 0x00000009;	//GPIOA ve GPIOD Aktif Edildi

	GPIOD->MODER = 0x55000000;	//OUTPUT
	GPIOD->OTYPER = 0x00000000;	//Push Pull
	GPIOD->OSPEEDR = 0xFF000000; //100MHz
	GPIOD->PUPDR = 0x00000000;	//No Pull
}

//Gecikme
void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Config();
	PLL_CLOCK_REGISTER ();

	//Butona çift basarak deðiþen durumlar
	while (1)
	{
		if(GPIOA->IDR & 0x00000001)  //GPIOA Button için IDR (INPUT DATA REGISTER) AYARLADIK
		{
			while(GPIOA->IDR & 0x00000001); //Sorgula
			delay(1680000);

			counter++;
		}

		if(counter % 2 == 0)
			GPIOD->ODR = 0x00000000; //Pinleri Resetle

		else
			GPIOD->ODR = 0x0000F000; //Pinleri Setle
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
