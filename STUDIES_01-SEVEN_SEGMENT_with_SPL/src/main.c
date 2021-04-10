/*7 SEGMENT DISPLAY WITH BUTTON SPL
 * ÇALIÞMA DOSYASIDIR !!!
 * By MUSTAFA ONUR PARLAK*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//Sayýcý
int counter = 0;

GPIO_InitTypeDef GPIO_InitStructure;

void BUTTON_SPL()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void SEVEN_SEGMENT_SPL()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	SEVEN_SEGMENT_SPL ();
	BUTTON_SPL ();

  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
	  {
		  while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0));
		  delay(1680000);

		  counter++;
	  }

	  //BUTONA Basýldýkça Case Ýfadesine Göre Deðiþen Sayma Sistemi
	  switch(counter)
	  {
	  	  case 0:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	  		  break;
	  	  }
	  	  case 1:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	  		  break;
	  	  }
	  	  case 2:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_6);
	  		  break;
	  	  }
	  	  case 3:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_5);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_6);
	  		  break;
	  	  }
	  	  case 4:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 |GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
	  		  break;
	  	  }
	  	  case 5:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_5 | GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4);
	  		  break;
	  	  }
	  	  case 6:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	  		  break;
	  	  }
	  	  case 7:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	  		  break;
	  	  }
	  	  case 8:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_All);
	  		  break;
	  	  }
	  	  case 9:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	  		  break;
	  	  }
	  	  default:
		  {
	  		  counter = 0;
	  		  break;
		  }
	  }
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
