/* Direct Memory Access - DMA - Standart Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#define BufferLenght 1 // Number of channels

uint16_t ADC1ConvertedValue[BufferLenght]; // 12-bit reading

// We will read value from potentiometer
void GPIO_CONFIG_SPL()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //BUTTON

	//BUTTON CONFIG
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN; // Equals GPIO_Mode_AIN
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct); //INITALIZE
}

// DMA configuration
void DMA_CONFIG_SPL()
{
	DMA_InitTypeDef DMA_Structure;
	RCC_APB1PeriphClockCmd (RCC_AHB1Periph_DMA2, ENABLE);

	DMA_DeInit (DMA2_Stream0); /* Program for each channel needs the following adjustments
	 	 	 	 	 	 	  * Transfer direction,
	 	 	 	 	 	 	  * Source and target data format,
	 	 	 	 	 	 	  * Circular or normal mode,
	 	 	 	 	 	 	  * Channel priority level,
	 	 	 	 	 	 	  * Source and target increment mode*/

	DMA_Structure.DMA_Channel  			 = DMA_Channel_0;				    // Channel 0
	DMA_Structure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;		    // Writes analog value of ADC to register
	DMA_Structure.DMA_Memory0BaseAddr    = (uint32_t) &ADC1ConvertedValue;  // Base address for memory
	DMA_Structure.DMA_DIR				 = DMA_DIR_PeripheralToMemory; 	    // Adjusted to memory from the Peripheral Unit
	DMA_Structure.DMA_BufferSize		 = BufferLenght; 				    // Channel Lenght
	DMA_Structure.DMA_PeripheralInc		 = DMA_PeripheralInc_Disable;	    // DR reading is constant
	DMA_Structure.DMA_MemoryInc			 = DMA_MemoryInc_Enable;		    // Changes while reading
	DMA_Structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 12-bit data is read. Also Byte, Halfword and Word
	DMA_Structure.DMA_MemoryDataSize	 = DMA_MemoryDataSize_HalfWord;		// 12-bit data is read. Also Byte, Halfword and Word
	DMA_Structure.DMA_Mode				 = DMA_Mode_Circular;				// Cyclic
	DMA_Structure.DMA_Priority			 = DMA_Priority_VeryHigh;			// Indicates priority
	DMA_Structure.DMA_FIFOMode 			 = DMA_FIFOMode_Disable; 			// First-Input First-Output Disable
	DMA_Structure.DMA_FIFOThreshold	     = DMA_FIFOThreshold_HalfFull;      // Threshold value
	DMA_Structure.DMA_MemoryBurst		 = DMA_MemoryBurst_Single;          // Debug mode
	DMA_Structure.DMA_PeripheralBurst	 = DMA_MemoryBurst_Single;          // Debug mode

	DMA_Init(DMA2_Stream0, &DMA_Structure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

}

// ADC configuration
void ADC_CONFIG_SPL ()
{
	ADC_InitTypeDef ADC_Struct;
	ADC_CommonInitTypeDef ADC_CommonStruct;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE);

	/* Right now we are only concerned with resolution.
	 * For this reason, the remaining parameters will be default.*/
	ADC_CommonStruct.ADC_Mode             = ADC_Mode_Independent; 	       // standalone mode
	ADC_CommonStruct.ADC_Prescaler 	      = ADC_Prescaler_Div2;            // oscillator division speed
	ADC_CommonStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;    // Singular used
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles; // Wait between samples. similar to Delay

	ADC_CommonInit (&ADC_CommonStruct); 						   	       // Initialize ADC_CommonStruct

	/* Right now we are only concerned with resolution.
	 * For this reason, the remaining parameters will be default.*/
	ADC_Struct.ADC_Resolution           = ADC_Resolution_12b;              // Resolution (0-4095), that is, we select the range we value pinpoint
	ADC_Struct.ADC_ScanConvMode         = ENABLE;
	ADC_Struct.ADC_ExternalTrigConvEdge = 0;
	ADC_Struct.ADC_DataAlign 	        = ADC_DataAlign_Right;
	ADC_Struct.ADC_NbrOfConversion	    = BufferLenght;

	ADC_Init (ADC1 ,&ADC_Struct); 				 	                       // Initialize to ADC Structure

	ADC_DMACmd (ADC1, ENABLE);											   // ADC and DMA connecting

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);					   // Which ADC channel will the data flow in ADC and DMA connection?
	ADC_Cmd (ADC1,ENABLE);
}

int main(void)
{
	GPIO_CONFIG_SPL ();
	DMA_CONFIG_SPL  ();
	ADC_CONFIG_SPL  ();

	ADC_SoftwareStartConv(ADC1); // Conversion for ADC1 starts

	while (1)
	{

	}
}
