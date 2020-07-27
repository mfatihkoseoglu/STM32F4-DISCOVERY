#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void config()
{
	//RCC->AHB1ENR = 0b000000000000000000000000001001;
	RCC->AHB1ENR = 0x00000009;

	//GPIOD->MODER = 0b01010101000000000000000000000000;
	GPIOD->MODER = 0x55000000;
	//GPIOD->OSPEEDR = 0b11111111000000000000000000000000;
	GPIOD->OSPEEDR = 0xFF000000;
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	int a = 0;
	config();
  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  a++;
		  delay(3360000);
	  }

	  if(a == 1)
	  {
		  GPIOD->ODR = 0x00001000;
	  }

	  else if(a == 2)
	  {
		  GPIOD->ODR = 0x00003000;
	  }

	  else if(a == 3)
	  {
		  GPIOD->ODR = 0x00007000;
	  }

	  else if(a == 4)
	  {
		  GPIOD->ODR = 0x0000F000;
	  }

	  else
	  {
		  GPIOD->ODR = 0x00000000;
		  a = 0;
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
