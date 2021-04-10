/* Digital to Analog Converter - DAC - Standart Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* For example,
 * If we do an 8-bit reading
 * 2^8 = 256
 * Bit value for each voltage
 * 3.3 (Reference Voltage) / 255 (2^n-1) = 0,01294117647   // 3.6 - 1.8 Voltage range
 * Corresponding range to 2.2 Voltage
 * 2.2/0,01294117647 = 170,0000000077  					   // Approach 170
 * Definition range is found*/

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef  DAC_InitStruct;

int count = 0;

// Delay
void Delay(uint32_t time)
{
	while(time--);
}

void GPIO_CONFIG_SPL ()
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE); // GPIOA Enable

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DAC_CONFIG_SPL ()
{
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStruct.DAC_OutputBuffer					= DAC_OutputBuffer_Enable;  // Noise sensored activited
	DAC_InitStruct.DAC_Trigger						= DAC_Trigger_None; 		// Trigger none
	DAC_InitStruct.DAC_WaveGeneration				= DAC_WaveGeneration_None;  // We didn't gen. wave
	DAC_Init(DAC_Channel_1, &DAC_InitStruct); //Channel 1 = PA4, Channel 2= PA5

	DAC_Cmd (DAC_Channel_1, ENABLE);
}

int main(void)
{
	DAC_CONFIG_SPL  ();
	GPIO_CONFIG_SPL ();

	while (1)
	{
		for (count=0; count<255; count ++)
		{
			DAC_SetChannel1Data(DAC_Align_8b_R, count);
			Delay (16800);
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
