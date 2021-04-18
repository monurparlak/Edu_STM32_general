/* ****************************************************************************************************************************************
 ******************************************************************************************************************************************
 *
 * PWM - Pulse Wave Modulation - General Purpose
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 * ****************************************************************************************************************************************
 * ****************************************************************************************************************************************

/* ****************************************************************************************************************************************
 *
 * PWM Modulation: Used in signal processing or transmission operations.
 * It is the transmission of the information to be transmitted over the signal
 * by changing certain characteristics of it within the framework of certain methods.
 *
 * ****************************************************************************************************************************************
 *
 * AM: Amplitude Modulation
 * The amplitude (intensity) of the carrier signal is changed according to the amplitude (intensity) of the audio signal to be sent.
 * (Signal frequency does not change)
 * In this way, the receiving side can perceive the desired signal by looking at the amplitude of the received signal
 *
 * FM: Frequency Modulation
 * Conversely, here the Intensity is kept constant, there is a change in frequency
 * Thus, the receiving side analyzes the changes in the signal frequency as changes in the amplitude of the frequency
 * As a result, the information to be sent is obtained.
 *
 * ****************************************************************************************************************************************
 *
 * The reason for using FM in radios is that there are losses in low amplitude signal transmission
 * to greater distances and transmission with equal amplitude is provided.
 *
 * *****************************************************************************************************************************************
 *
 * PWM: Pulse Amplitude(Width) Modulation
 * Since the carrier signal is realized with the desired on / off operation per second,
 * it can be said that it is a modulation through switching.
 *
 * Duty Cycle: Occupancy rate
 * Period: The time from the starting point to the end point.
 * Since the period value is fixed here, the receiving party can calculate the "Duty Cycle" rate by analyzing the sent signal.
 * ****************************************************************************************************************************************
 *
 * 				  (TIMER Period +1) *(Duty Cycle)
 * Pulse Length =  _______________________________  - 1
 * 				  				100
 *
 * For example; (TIM Period = 9999)
 * 				 25% Duty Cycle = 2499
 * 				 50% Duty Cycle = 4999
 * 				100% Duty Cycle = 9999
 *
 * *****************************************************************************************************************************************/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_TimeBaseInitTypeDef TIMStructure; // General Timer
TIM_OCInitTypeDef TIMPWM; 		     // TIMER for PWM

void TIME_CONFIG_SPL ()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);      // RCC Config for TIM4

	TIMStructure.TIM_ClockDivision		= TIM_CKD_DIV1;  	  // 84 MHz
	TIMStructure.TIM_CounterMode		= TIM_CounterMode_Up; // UP-DOWN Counter
	TIMStructure.TIM_Period				= 62499;
	TIMStructure.TIM_Prescaler			= 1343;
	TIMStructure.TIM_RepetitionCounter  = 0; 		     	  // Repetition status is determined (each rising)

	TIM_TimeBaseInit (TIM2, &TIMStructure);					  // Initialized

	TIM_Cmd (TIM2, ENABLE);									  // Peripherals Enabled
}

void TIMERPWM_CONFIG_SPL ()
{
	TIMPWM.TIM_OCMode		= TIM_OCMode_PWM1; // Mode 1: %25 High, Mode 2: %75 High
	TIMPWM.TIM_OCPolarity	= TIM_OCPolarity_High;
	TIMPWM.TIM_OutputState	= TIM_OutputState_Enable;
}

void ANY_GPIO_CONFIG_SPL ()
{
	/* If Alternate Function (AF) is defined as Mode in GPIO operations,
	 * it is necessary to define which alternative output it is.*/
	GPIO_PinAFConfig (GPIOx, GPIO_PinSourcex,GPIO_AF_TIMx);
}

int main(void)
{
	TIMER_CONFIG_SPL ();
	TIMERPWM_CONFIG_SPL ();
	ANY_GPIO_CONFIG_SPL ();

	while (1)
	{
		// 50% Duty Cycle Mode
		TIMPWM.TIM_Pulse = 4999;
		TIM_OC1Init (TIM4, &TIMPWM);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
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
