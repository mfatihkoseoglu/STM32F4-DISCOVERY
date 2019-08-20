#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC->AHB1ENR = 0x00000009;

	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0xFF000000;
}

void EXTI_Config()
{
	RCC->APB2ENR = 0x00004000;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	SYSCFG->EXTICR[0] = 0x00000000;
	SYSCFG->EXTICR[1] = 0x00000000;
	SYSCFG->EXTICR[2] = 0x00000000;

	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 5);
	NVIC_SetPriority(EXTI2_IRQn, 3);

	EXTI->IMR = 0x00000007;
	EXTI->RTSR = 0x00000007;
}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & (1 << 0))
	{
		int i = 0;

		do{
			GPIOD->ODR = 0x00001000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = (1 << 0);
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI->PR & (1 << 1))
	{
		int i = 0;

		do{
			GPIOD->ODR = 0x00002000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = (1 << 1);
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI->PR & (1 << 2))
	{
		int i = 0;

		do{
			GPIOD->ODR = 0x00008000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}
		while(i<5);

		EXTI->PR = (1 << 2);
	}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();
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
