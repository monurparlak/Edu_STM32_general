/* GPIO OUTPUT APP - STANDART PERIPHERAL LIBRARY
 * TASLAK DOSYADIR !!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Configuration()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	//Kart �st�ndeki Ledleri Yakan Yap�lar�m�z
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //Led Pinleri
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //Giri� (INPUT - YAZMA) veya ��k�� (OUTPUT - OKUMA)
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //Push Pull, Pull Up, Pull Down, No Pull Durumlar�
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; //��lem H�z� (NOT: INPUT -> OUTPUT Ge�i� H�z�)

	//Initialize ��lemi i�in Gerekli Kod
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

//Gecikme i�in Gerekli Fonksiyon
void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Configuration();

	//Temel Yan S�n Durumunu Yaz�yoruz
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_All);
	    delay(16800000);

	    GPIO_ResetBits(GPIOD, GPIO_Pin_All);
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
