#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config()
{
	RCC->AHB1ENR = 0x00000008;   // GPIOD clock enable 

	GPIOD->MODER = 0x55000000;   // GPIO 12,13,14 and 15 pins mode output
	GPIOD->OTYPER = 0x00000000;  // GPIO OType value PP
	GPIOD->OSPEEDR = 0xFF000000; // GPIO pins speed max
	GPIOD->PUPDR = 0x00000000;   // No Pull
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
	  GPIOD->ODR = 0x0000F000;   // GPIO 12,13,14 and 15. pins are set
	  delay(16800000);           // wait 
	  GPIOD->ODR = 0x00000000;   // GPIO 12,13,14 and 15. pins are reset
	  delay(16800000);           // wait
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
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
