#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
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
	  if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
	  {
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0));
		delay(3360000);

		count ++;
	  }

	  switch(count)
	  {
	  	  case 0:
	  	  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	  		  break;
	  	  }
		  case 1:
		  {
			  GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			  break;
		  }
		  case 2:
		  {
	  		  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	  		  GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			  break;
		  }
		  case 3:
		  {
			  break;
		  }
		  case 4:
		  {
			  break;
		  }
		  case 5:
		  {
			  break;
		  }
		  case 6:
		  {
			  break;
		  }
		  case 7:
		  {
			  break;
		  }
		  case 8:
		  {
			  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			  break;
		  }
		  case 9:
		  {
			  break;
		  }
		  default:
		  {
			  count = 0;
		  }
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
