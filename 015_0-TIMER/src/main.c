#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 42 MHz max Timer için 84Mhz max

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;; // STMCUBEMX den de bakýlabilir. Elektrik tüketimi ile alakalýdýr.
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_RepetitionCounter = 0; // 1 taþma sonucunda bayraðý kaldýr diyoruz. yazýlan deðer +1 olur.
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Yukarý doðru say diyoruz.

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	// Eðer TIM ile beraber bir interrupt kullanacaksak timer ile interruptý birbirine baðlamalýyýz.
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn; // NVIC in yöneteceði interruptý belirtir
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	// hattý aktif ettik
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; // basþa interrupt yok önceliðe gerek yok.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;

	NVIC_Init(&NVIC_InitStruct);
}

void TIM4_IRQHandler()
{
	// bayrak kalktýktan sonra yapýlacak iþlem
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	// bayraðý tekrar indirmeliyiz bayraðýn tekrar kalkmasý için
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

int main(void)
{
	config();
  while (1)
  {

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
