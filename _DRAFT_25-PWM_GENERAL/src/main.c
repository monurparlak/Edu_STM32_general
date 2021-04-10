/* **********************************************************************************************************************************************
 ************************************************************************************************************************************************
 *
 * PWM - Pulse Wave Modulation - General Purpose
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 * ***********************************************************************************************************************************************
 * ***********************************************************************************************************************************************/

/* **********************************************************************************************************************************************
 *
 * PWM Modulation: Used in signal processing and / or transmission works.
 * It is the transmission of the information to be transmitted over the signal
 * by changing certain characteristics of it within the framework of certain methods.
 *
 * **********************************************************************************************************************************************
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
 * **********************************************************************************************************************************************
 *
 * The reason for using FM in radios is that there are losses in low amplitude signal transmission
 * to greater distances and transmission with equal amplitude is provided.
 *
 * ***********************************************************************************************************************************************
 *
 * PWM: Pulse Amplitude Modulation
 * Since the carrier signal is realized with the desired on / off operation per second, it can be said that it is a modulation through switching.
 *
 * Duty Cycle: Occupancy rate
 *
 * Period: The time from the starting point to the end point.
 * Since the period value is fixed here, the receiving party can calculate the "Duty Cycle" rate by analyzing the sent signal.
 *
 * ***********************************************************************************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


int main(void)
{

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
