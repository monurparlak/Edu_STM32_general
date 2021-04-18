/* *****************************************************************************************************************************************
 *******************************************************************************************************************************************
 *
 * TIMER - Standard Peripherals Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 * *****************************************************************************************************************************************
 * *****************************************************************************************************************************************

 * *****************************************************************************************************************************************
 *
 * TIMER
 * Basically, it has TIMER and COUNTER feature in the microcontroller.
 *
 * WHAT IS TIMER AND COUNTER?
 * Counting digital events (1-0)
 * Establishing and measuring Time-Delay
 * Measuring the time between events
 * Generating a signal in the desired period
 * PWM signal output
 *22
 * INCORRECT USE
 * As an example, we can use it with DELAY.
 * With DELAY it will wait idle until the loop is finished.
 * This method is useless
 * - Sytem Tick Timer X
 *
 * When we operate with frequency,
 * The elapsed time for the frequency and the cycles per second can be calculated.
 *
 * Basic operation: Frequency counter starter -> Interrupt activated - Timer enable
 *
 * *****************************************************************************************************************************************
 *
 * CAPTURE MODE (INPUT)
 * The system instantly records the timer value (fall, rise, fall-rise edge)
 * As an example, the difference between the two cases can be calculated.
 *
 * COMPARE MODE (OUTPUT)
 * The compare value is compared with the timer value.
 * When equal, the system gives out.
 * As an example, equality between two cases can be calculated.
 *
 * *****************************************************************************************************************************************
 *
 * PWM: Pulse Width Modulation
 * Since the carrier signal is realized with the desired on / off operation per second,
 * it can be said that it is a modulation through switching.
 *
 * Duty Cycle: Occupancy rate
 * Period: The time from the starting point to the end point.
 * Since the period value is fixed here, the receiving party can calculate the "Duty Cycle" rate by analyzing the sent signal.
 *
 * *****************************************************************************************************************************************
 *
 * WHAT WE SHOULD KNOW WHEN CALCULATING
 * TIMER FREQUENCY CLOCK (TIMx_CLK) = Constant value required when performing operations with Timer
 * PRESCALER 			 (TIMx_PSC) = Frequency pre-divider value.
 * AUTO RELOAD           (TIMx_ARR)	= Start counter upper limit (creates an event)
 *
 *******************************************************************************************************************************************
 *
 * FORMULA
 *
 *           (Period + 1) * (Prescaler + 1)
 * Second =  ______________________________
 *
 * 			 	    (Clock Speed)
 *
 * ------------------------------------------------------------------
 * ALL VALUES ARE OPTIONAL
 * VERY IMPORTANT: THE MAX PRESCALER VALUE CAN BE 16-BITS. (65535)
 * ------------------------------------------------------------------
 *
 * For Example: For a timer that counts in 1 second intervals
 * Period 		  = 62499
 * Prescaler 	  = 1343
 * MCU Clock Freq = 84000000
 * Interrupt Time = 1
 * Clock Divison  = 4 (most efficient)
 *
 * *****************************************************************************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_TimeBaseInitTypeDef TIMStructure;
NVIC_InitTypeDef NVICStructure;			// Interrupt Flag

void TIMER_CONFIG_SPL ()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	  // TIM2 to APB1 Bus Activited

	TIMStructure.TIM_ClockDivision		= TIM_CKD_DIV4;  	  // Divide by 4 to save on electricity consumption
	TIMStructure.TIM_CounterMode		= TIM_CounterMode_Up; // UP-DOWN Counter
	TIMStructure.TIM_Period				= 62499;
	TIMStructure.TIM_Prescaler			= 1343;
	TIMStructure.TIM_RepetitionCounter  = 0; 		     	  // Repetition status is determined (each rising)

	TIM_TimeBaseInit (TIM2, &TIMStructure);					  // Initialized

	TIM_Cmd (TIM2, ENABLE); // Peripherals Enabled

	TIM_ITConfig (TIM2, TIM_IT_Update, ENABLE); 			  // Interrupt and Timer connection

	NVICStructure.NVIC_IRQChannel					= TIM2_IRQn; // Write timer to enter the interrupt state
	NVICStructure.NVIC_IRQChannelCmd				= ENABLE;
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 0xFF;
	NVICStructure.NVIC_IRQChannelSubPriority		= 0xFF;
	NVIC_Init (&NVICStructure);
}

void TIM2_IQRHandler ()
{
	// ANY FUNCTION TO BE CARRIED OUT IN CASE OF RAISING FLAG

	TIM_ClearITPendingBit (TIM2, TIM_IT_Update); // Flag was clear
}

int main(void)
{
	TIMER_CONFIG_SPL ();

	while (1); // WE DO NOT USE THE MICROPROCESSOR
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return -1;
}
