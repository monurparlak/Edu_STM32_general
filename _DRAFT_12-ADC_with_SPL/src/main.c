/* Analog to Digital Converter - ADC - Standart Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

/* For example,
 * If we do an 8-bit reading
 * 2^8 = 512
 * Voltage value for each bit
 * 3.3 (Reference Voltage) / 511 (2^n-1) = 0,0064453125   // 3.6 - 1.8 range
 * Corresponding voltage to 500
 * 500*0,0064453125 = 3,22265625
 * Voltage is found*/

/* Too much speed reduces resolution*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef POTStruct;				// Potentiometer Structure
ADC_InitTypeDef ADCStruct;				// ADC Structure
ADC_CommonInitTypeDef ADC_CommonStruct;	// ADC Common

uint8_t ADC_DATA; // We select the range of values that we will read from the potentiometer

//DELAY CONFIG
void Delay (uint32_t time)
{
	while (time --);
}

// We write led and potentiometer external devices here.
void GPIO_CONFIG_SPL ()
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE); // POT DATABUS Enable

	/*POT Config*/
	POTStruct.GPIO_Mode  = GPIO_Mode_AN; 				   // Analog mode from the Pot
	POTStruct.GPIO_OType = GPIO_OType_PP; 				   // Push Pull
	POTStruct.GPIO_Pin   = GPIO_Pin_0; 					   // POT PA0 config
	POTStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; 			   // PULL UP or PULLDOWN not necessary therefore No Pull
	POTStruct.GPIO_Speed = GPIO_Speed_100MHz; 			   // IO Freq not necessary therefore 100 MHz
	GPIO_Init (GPIOA, &POTStruct);						   //Initialize
}

/* Let's define void loops into more useful logic blocks for peripherals like adc*/
void ADC_CONFIG_SPL ()
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE);	// ADC DATABUS Activited

	/* Right now we are only concerned with resolution.
	 * For this reason, the remaining parameters will be default.*/
	ADC_CommonStruct.ADC_Mode      = ADC_Mode_Independent; 	// standalone mode
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4; 	// oscillator division speed
	ADC_CommonInit (&ADC_CommonStruct); 					// Initialize ADC_CommonStruct

	/* Right now we are only concerned with resolution.
	 * For this reason, the remaining parameters will be default.*/
	ADCStruct.ADC_Resolution = ADC_Resolution_8b; 			// Resolution (0-255), that is, we select the range we value pinpoint
	ADC_Init (ADC1 ,&ADCStruct); 							// Initialize to ADC Structure
	ADC_Cmd (ADC1, ENABLE);  	 							// ADC1 Module peripheral unit Enable
}

// ADC type Writing and Reading
uint16_t Read_ADC ()
{
	ADC_RegularChannelConfig (ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);

	ADC_SoftwareStartConv (ADC1); 							// ADC transform begin

	/*WE MUST WAIT UNTIL ADC IS CALCULATED*/
	while (ADC_GetFlagStatus (ADC1, ADC_FLAG_EOC) == RESET); // WAIT UNTIL EOC (End of conversion ) RESET. LATER OUT OF THE WHILE CYCLE

	return ADC_GetConversionValue (ADC1);					// Come back to ADC_DATA and ADC1

}

int main(void)
{
	GPIO_CONFIG_SPL ();
	ADC_CONFIG_SPL ();

	while (1)
	{
		ADC_DATA = Read_ADC ();
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
