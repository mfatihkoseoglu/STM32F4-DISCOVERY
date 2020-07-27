#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
 	config();

  while (1)
  {
	  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  Delay(42000000);
	  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  Delay(42000000);
	  GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  Delay(42000000);
	  GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  Delay(42000000);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	  Delay(16800000);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	  Delay(16800000);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	  Delay(16800000);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	  Delay(16800000);
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
