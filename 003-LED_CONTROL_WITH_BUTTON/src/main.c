#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

int i = 0;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void delay(uint32_t time)
{
	while(time--)
	{

	}
}

int main(void)
{
	config();

  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		  i++;
		  delay(1680000);
	  }

	  if(i == 1)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  }

	  else if(i == 2)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  }

	  else if(i == 3)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  }

	  else if(i == 4)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  }

	  else
	  {
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		  i = 0;
	  }
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
