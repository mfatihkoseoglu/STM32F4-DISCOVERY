#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void delay(uint32_t time)
{
	while(time--)
	{

	}
}

void config()
{
	RCC->AHB1ENR = 0x00000009;
	RCC->APB2ENR = 0x00004000;

	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0xFF000000;

/*	GPIOA->MODER = 0x00000001;
	GPIOA->OTYPER = 0x00000000;
	GPIOA->PUPDR = 0x00000002;
	GPIOA->OSPEEDR = 0x00000003;*/

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);	// öncelik tanýmlamak için kullanýlýr, tek interrupta kullanýlmaya bilir.
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);

	SYSCFG->EXTICR[0] = 0x00000000;
	EXTI->IMR = 0x00000007;
	EXTI->RTSR = 0x00000007;
}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & 0x00000001)
	{
		int i = 0;
		do
		{
			GPIOD->ODR = 0x00004000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = 0x00000001;
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI->PR & 0x00000002)
	{
		int i = 0;
		do
		{
			GPIOD->ODR = 0x00002000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = 0x00000002;
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI->PR & 0x00000004)
	{
		int i = 0;
		do
		{
			GPIOD->ODR = 0x00001000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = 0x00000004;
	}
}

int main(void)
{
	config();
  while (1)
  {
	  GPIOD->ODR=0x0000F000;
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
