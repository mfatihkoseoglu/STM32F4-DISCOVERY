	#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int IRQ_Counter = 0;

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

	NVIC_SetPriority(EXTI0_IRQn, 0); // öncelik tanýmlamak için kullanýlýr, tek interrupta kullanýlmaya bilir.

	SYSCFG->EXTICR[0] = 0x00000000;
	EXTI->IMR = 0x00000001;
	EXTI->RTSR = 0x00000001;

}

void delay(uint32_t time)
{
	while(time--)
	{

	}
}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & (1<<0))
	{
		IRQ_Counter++;

		GPIOD->ODR = 0x00004000;
		delay(16800000);

		EXTI->PR = (1<<0);
	}
}

int main(void)
{
	config();

  while (1)
  {
	  GPIOD->ODR = 0x0000B000;
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
