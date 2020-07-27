#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t random;

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void RNG_Config()
{
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);

	RNG_Cmd(ENABLE);
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Config();
	RNG_Config();
  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		  delay(1680000);

		  random = RNG_GetRandomNumber();
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
