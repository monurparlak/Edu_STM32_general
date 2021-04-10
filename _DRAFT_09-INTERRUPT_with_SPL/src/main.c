/* INTERRUPT - STANDART PERIPHERAL
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct; // GPIO yap� tan�mlamam�z
EXTI_InitTypeDef EXTI_InitStruct; // EXTI yap� tan�mlamam�z
NVIC_InitTypeDef NVIC_InitStruct; // NVIC yap� tan�mlamam�z

// Gecikme
void Delay(uint32_t time)
{
	while(time--);
}

// LED konfig�rasyonu
void LED_CONFIG_SPL()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //LED

	// LED CONFIG
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct); // INITIALIZE
}

// Button konfig�rasyonu
void BUTTON_CONFIG_SPL()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //BUTTON

	// BUTTON CONFIG
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct); // INITIALIZE


}

// EXTERNAL INTERRUPT konf�g�rasyonu
void EXTI_CONFIG_SPL ()
{
	SYSCFG_EXTILineConfig (EXTI_PortSourceGPIOA, EXTI_PinSource0);

	EXTI_InitStruct.EXTI_Line	 = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode	 = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init (&EXTI_InitStruct); // INITIALIZE
}

// NESTED VECTOR INTERRUPT CONTROL konf�grasyonu
void NVIC_CONFIG_SPL ()
{
	NVIC_InitStruct.NVIC_IRQChannel					  = EXTI0_IRQn;	 //EXTI 0 hatt� NVIC i�in aktif olarak kullan�lmaktad�r
	NVIC_InitStruct.NVIC_IRQChannelCmd				  = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0xFF;		 // �ncelik
	NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0x00;   	 // �nceli�in �nceli�i
}

// IRQHandler FLAG konfig�rasyonu
void EXTI0_IRQHandler ()
{
	if (EXTI_GetITStatus (EXTI_Line0) != RESET)
	{
		GPIO_ResetBits (GPIOD, GPIO_Pin_All);
		Delay (168000);

		GPIO_SetBits (GPIOD, GPIO_Pin_All);
		Delay (1680000);

		EXTI_ClearITPendingBit (EXTI_Line0);
	}
}

int main(void)
{
	BUTTON_CONFIG_SPL ();
	LED_CONFIG_SPL 	  ();
	EXTI_CONFIG_SPL   ();
	NVIC_CONFIG_SPL   ();

	while (1)
	{
		GPIO_SetBits (GPIOD, GPIO_Pin_All);
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
