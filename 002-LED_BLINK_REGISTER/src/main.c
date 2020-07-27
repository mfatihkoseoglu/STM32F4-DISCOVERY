#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void config()
{
	RCC->AHB1ENR = 0b00000000000000000000000000001000;
	GPIOD-> MODER   = 0b01010101000000000000000000000000;
	GPIOD-> OTYPER  = 0b00000000000000000000000000000000;
	GPIOD-> OSPEEDR = 0b11111111000000000000000000000000;

}

void Delay(uint32_t time)
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
		GPIOD->ODR = 0b00000000000000001111000000000000;
		Delay(1680000);
		GPIOD->ODR = 0b00000000000000000000000000000000;
		Delay(1680000);
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
