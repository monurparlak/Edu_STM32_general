/************************************************************************************************************************************************
 ************************************************************************************************************************************************
 *
 * Inter Integrated Circuit - I2C - Standart Peripheral Library
 * TASLAK DOSYADIR
 * By MUSTAFA ONUR PARLAK
 *
 *************************************************************************************************************************************************
 *************************************************************************************************************************************************/


/* **********************************************************************************************************************************************
 *
 * It enables low speed (MCU xMHz) peripherals to communicate with less cable with I2C Protocol.
 * Pull-Up resistance required for system operation (3.3-5 V, 4.7-5K Ohm)
 *
 * SDA: Serial Data Line
 * SCL: Serial Clock Line
 *
 * ACK: Acknowledgment. The acceptance that the slave device sends to the master device.
 * Repeated Start: It is done to restart the bit sent for the SLAVE device to the I2C line used with any MASTER device.
 * SDA and SCL pins must be LOW to do this.
 * Idle: It represents the idle state of the I2C line
 *
 * **********************************************************************************************************************************************
 *
 * In such protocols,
 * 		First Start is sent >> Then the address is sent >> In the final, RW (Read/Write) information goes
 * Starts when the SDA line is LOW, followed by a loop ending when it is HIGH
 * Similarly ... When SDA becomes HIGH, SCL becomes HIGH; communication ends
 *
 * **********************************************************************************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;
I2C_InitTypeDef I2C_InitStructure;

void GPIO_CONFIG_SPL ()
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOx, ENABLE);

	GPIO_PinAFConfig (GPIOx, GPIO_PinSourucex, GPIO_AF_I2Cx); // SCL Pin
	GPIO_PinAFConfig (GPIOx, GPIO_PinSourucex, GPIO_AF_I2Cx); // SDA Pin

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pinx;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init (GPIOx, &GPIO_InitStructure);
}

void I2C_CONFIG_SPL ()
{
	RCC_APBxPeriphClockCmd (RCC_APHBxPeriph_I2Cx, ENABLE);

	I2C_InitStructure.I2C_Ack				  = ENABLE; 					  // Acknowledge
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_xbit; // 7 or 10 bits
	I2C_InitStructure.I2C_ClockSpeed		  = 400000;						  // Max I/O working frequency
	I2C_InitStructure.I2C_DutyCycle			  = I2C_DutyCycle_x; 			  // Duty Cycle
	I2C_InitStructure.I2C_Mode				  = I2C_Mode_I2C;                 // Working mode
	I2C_InitStructure.I2C_OwnAddress1		  = 0x00; 						  //First device address

	I2C_Init (I2Cx, &I2C_InitStructure);
	I2C_Cmd (I2Cx, ENABLE); // This is a Peripheral
}

int main(void)
{
	GPIO_CONFIG_SPL ();
	I2C_CONFIG_SPL  ();

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
