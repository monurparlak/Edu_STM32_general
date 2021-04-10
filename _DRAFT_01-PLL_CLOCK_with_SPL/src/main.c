/*PLL Ve CLOCK Ayarlama GPIO
 * TASLAK DOSYASIDIR!!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//Global GPIO (General Propuse Input/Output) Deðiþkenimizi Tanýmlýyoruz
GPIO_InitTypeDef GPIO_InitStructure;

void PLL_With_CLOCK_GPIO()
{
	//RCC (Reset and Clock Control) Kýsmýný DATABUS ile ENABLE Yapýyoruz
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

}

int main(void)
{
	while (1)
	{
		PLL_With_CLOCK_GPIO();
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
