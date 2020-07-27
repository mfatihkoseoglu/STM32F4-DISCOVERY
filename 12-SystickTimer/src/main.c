#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;

uint16_t m_counter = 0;

void SysTick_Handler(void)
{
	if(m_counter>0)
	{
		m_counter--;
	}
}

void delay_ms(uint16_t time)
{
	m_counter = time;

	while(m_counter)
	{

	}

}

void config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_Init(GPIOD, &LED);

	SysTick_Config(SystemCoreClock / 1000); //1 ms
}

int main(void)
{
	config();
  while (1)
  {
	  GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  delay_ms(1000);
  }
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
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
