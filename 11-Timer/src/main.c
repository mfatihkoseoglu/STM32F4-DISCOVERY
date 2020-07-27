#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i = 0;

GPIO_InitTypeDef LED;

TIM_TimeBaseInitTypeDef TIMStructure;

NVIC_InitTypeDef NVICStructure;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &LED);

	TIMStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIMStructure.TIM_Period = 9999;
	TIMStructure.TIM_Prescaler = 8399;
	TIMStructure.TIM_RepetitionCounter = 0;
	TIMStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIMStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, ENABLE);

	NVICStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVICStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVICStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVICStructure);
}

int main(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	config();
  while (1)
  {

  }
}

void TIM4_IRQHandler()
{
	i++;
	if(i == 1)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	}

	else if(i == 2)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	}

	else if(i == 3)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	}

	else if(i == 4)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

		i = 0;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
