/* *****************************************************************************************************************************************
 *******************************************************************************************************************************************
 *
 * System Tick Timer - STANDARD PERIPHERAL LIBRARY
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 * *****************************************************************************************************************************************
 * *****************************************************************************************************************************************/

/* *****************************************************************************************************************************************
 *
 * SYSTEM TICK TIMER?
 *
 * Roughly, it has a timing feature. does not serve a specific purpose
 * It is specific to ARM Architecture.
 * At the core and easily accessible
 * Linked to HSE
 *
 * *****************************************************************************************************************************************
 *
 * System Timer
 * 1sn = System Frequency / 1
 * 1ms = System Frequency / 1000
 * 1us = System Frequency / 1000000
 *
 * *****************************************************************************************************************************************/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t u32DelayCount;

void SYSTEM_TICK_CONFIG_SPL ()
{
	SysTick_Config (SystemCoreClock/1000); // Enters interrupt function every 1ms
}

void delay_ms (uint32_t u32time)
{
	u32DelayCount = u32time;

	while (u32DelayCount);
}

// We reduce the time and reset it
void SysTick_Handler (void)
{
	if (u32DelayCount > 0)
	{
		u32DelayCount --;
	}
}

void Delay (uint32_t time)
{
	while (time --);
}


int main(void)
{
	SYSTEM_TICK_CONFIG_SPL();

	while (u32DelayCount)
	{
		// You can write the function you will count here.
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
