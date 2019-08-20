#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
	  {
		  while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));
		  delay(1680000);

		  count++;
	  }

	  if(count == 1)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  }

	  else if(count == 2)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  }

	  else if(count == 3)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  }

	  else if(count == 4)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  }

	  else{
		  count = 0;
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		  delay(1680000);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		  delay(1680000);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		  delay(1680000);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
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
