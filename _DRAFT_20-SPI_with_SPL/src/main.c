/************************************************************************************************************************************************
 ************************************************************************************************************************************************
 *
 * Serial Peripheral Interface - SPI - Standart Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 *************************************************************************************************************************************************
 *************************************************************************************************************************************************/


/* **********************************************************************************************************************************************
 *
 * Serial Communication Type
 * Provides communication between peripheral - microprocessor - integrated
 * The data width can be adjusted between 8 and 16 bits
 * Communication interaction distance is ~30 cm
 *
 * **********************************************************************************************************************************************
 *
 * MISO  : Master In / Slave Out
 * MOSI  : Master Out / Slave In
 * SCK   : Serial Clock Output (Master Clock Out / Slave Clock In)
 * CS/SS : (Slave - Ciph Select) Slave selection pin in master devices
 *
 * **********************************************************************************************************************************************
 *
 * Master Mode: It is half the frequency of the main BUS line (FCLK/2)
 * CPOL: Clock is Signal Pole Setting
 * CPOL (ACTIVE): When no data is sent, the CLOCK line is high. When data is sent, the first signal is the falling edge.
 * CPOL (PASSIVE): When no data is sent, the CLOCK line is low. When data is sent, the first signal is the rising edge.
 *
 * CPHA: Clock is Phase Adjustment. Sets which edge of the clock signal the first captured bit of data will occur.
 * CPHA (ACTIVE): Occurs on the second Clock Signal edge. If CPOL is Active, it will be on the rising edge, if Passive is on the falling edge
 * CPHA (PASSIVE): Occurs on the first Clock Signal edge. If CPOL is Active, it is on the falling edge, if Passive is on the rising edge.
 *
 * ***********************************************************************************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef SPI_InitStructure;

GPIO_CONFIG_SPL ()
{
	// CS/SS SPI Pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init (GPIOx, &GPIO_InitStructure);

	// SPI with MOSI, MISO, SCLK Pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

	GPIO_PinAFConfig(GPIOx,GPIO_PinSourcex, GPIO_AF_SPIx); // MOSI
	GPIO_PinAFConfig(GPIOx,GPIO_PinSourcex, GPIO_AF_SPIx); // MISO
	GPIO_PinAFConfig(GPIOx,GPIO_PinSourcex, GPIO_AF_SPIx); // SCLK

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_x1 | GPIO_Pin_x2 | GPIO_Pin_x3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init (GPIOx, &GPIO_InitStructure);

}

void SPI_CONFIG_SPL ()
{
	RCC_APBxPeriphClockCmd (RCC_APBxPeriph_SPIx, ENABLE);

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_x;   		 // Work speed DIV
	SPI_InitStructure.SPI_CPHA				= SPIO_CPHA_xEdge; 		    		 // Edge
	SPI_InitStructure.SPI_CPOL				= SPI_CPOL_x;			    		 // The value is entered according to the datasheet data. High / low
	SPI_InitStructure.SPI_CRCPolynomial		= SPI_CRCPR_CRCPOLY;	   			 // It is a data verification unit
	SPI_InitStructure.SPI_DataSize			= SPI_DataSize_xb;		     		 // Data Lenght (8 or 16-bit)
	SPI_InitStructure.SPI_Direction			= SPI_Direction_x;   	   			 // Read - write - send only message - line usage status is written
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_x;		   			 // Indicates priority status. Low or high
	SPI_InitStructure.SPI_Mode				= SPI_Mode_x;			   			 // Master or Slave
	SPI_InitStructure.SPI_NSS				= SPI_NSS_x | SPI_NSSInternalSoftx; // It is a form of management by hardware or software

	SPI_Init (SPIx, &SPI_InitStructure);

	SPI_Cmd (SPIx, ENABLE); 		  // It's a Peripheral

	GPIO_SetBits (GPIOx, GPIO_Pin_x); // Read / Write operation can be performed. It is the coded section for CS / SS
}

int main(void)
{
	GPIO_CONFIG_SPL ();
	SPI_CONFIG_SPL  ();

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
