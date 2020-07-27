#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_

int count;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_Prescaler = 47999;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 100000;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM5, &TIM_InitStruct);

	TIM_Cmd(TIM5, ENABLE);

	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);

	TIM_SelectInputTrigger(TIM5, TIM_TS_TI1FP1);
}

int main(void)
{
	RCC_HSICmd(ENABLE);
	GPIO_Config();
	TIM_Config();
  while (1)
  {
	  count = TIM_GetCounter(TIM5);

	  while(TIM_GetFlagStatus(TIM5, TIM_FLAG_Trigger) != RESET)
	  {
		  GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

		  TIM_ClearFlag(TIM5, TIM_FLAG_Trigger);
	  }
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
