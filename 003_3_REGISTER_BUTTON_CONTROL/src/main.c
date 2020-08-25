#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC->CR |= 0x00030000;	// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;	// CSS Enable
	RCC->PLLCFGR |= 0x00400000;	// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;	// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;	// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;	// PLL p = 2
	RCC->CFGR |= 0x00000000;	// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;	// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;	// APB1 Prescaler = 4
	RCC->CIR |= 0x00800000;		// CSS Flag clear

	RCC->AHB1ENR = 0x00000009;	// GPIOA ve GPIOD aktif

	GPIOD->MODER = 0x55000000;	// 12,13,14,15. pins digital output
	GPIOD->OTYPER = 0x00000000;	// 12,13,14,15. pins Push pull
	GPIOD->OSPEEDR = 0xFF000000; // 12,13,14,15. pins 100MHz
	GPIOD->PUPDR = 0x00000000;	// 12,13,14,15. pins no pull
}

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)  // GPIOA port is set
	  {
		  while(GPIOA->IDR & 0x00000001); // wait during GPIOA port is set 
		  delay(1680000);                 // wait 

		  count++;
	  }

	  if(count % 2 == 0)                
		  GPIOD->ODR = 0x00000000;        // GPIOD port all pins are reset
	  else
		  GPIOD->ODR = 0x0000F000;        // GPIOD port 12,13,14 and 15 pins are set
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
