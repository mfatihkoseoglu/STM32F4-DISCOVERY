#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config()
{
	RCC->CR |= 0x00030000;										// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));								// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;										// CSS Enable
	RCC->CR |= 0x01000000;										// PLL ON
	RCC->PLLCFGR |= 0x00400000;									// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;									// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;									// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;									// PLL p = 2
	RCC->CFGR |= 0x00000000;									// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;									// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;									// APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;										// HSERDY Flag clear
	RCC->CIR |= 0x00800000;										// CSS Flag clear
}

void GPIO_Config()
{
	RCC->AHB1ENR |= 1 << 3;

	GPIOD->MODER |= 2 << 24 | 2 << 26  |  2 << 28 | 2 << 30;	// Port D -> Pin 12 | Pin 13 | Pin 14 | Pin 15 Alternate Function selected
	GPIOD->AFR[1] |= 2 << 16 | 2 << 20 | 2 << 24 | 2 << 28;		// Port D -> Pin 12 | Pin 13 | Pin 14 | Pin 15 Tim4 -> CH selected
}

void TIM_Config()
{
	RCC->APB1ENR |= 1 << 2;										// TIM4 clock enable

	TIM4->CR1 |= 0 << 4;										// Timer counter mode is Upcounter
	TIM4->CR1 |= 0 << 5;										// Center-aligned mode edge-aligned mode selected
	TIM4->CR1 |= 0 << 8;										// Clock division 1
	TIM4->PSC = 8399;											// Prescaler value 8400
	TIM4->ARR = 9999;											// Period value 10000
	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;
	/*
	 * Capture/Compare 1 output selected
	 * Output Compare 1 pwm mode 1 selected
	 * Capture/Compare 2 output selected
	 * Output Compare 2 pwm mode 1 selected
	 */
	TIM4->CCMR2 |= 0 << 0 | 6 << 4  | 0 << 8| 6 << 12;
	/*
	 * Capture/Compare 3 output selected
	 * Output Compare 3 pwm mode 1 selected
	 * Capture/Compare 4 output selected
	 * Output Compare 4 pwm mode 1 selected
	 */
	TIM4->CCER |= 1 << 0 | 1 << 4 | 1 << 8 | 1 << 12;
	/*
	 * Capture/Compare 1 output enable
	 * Capture/Compare 2 output enable
	 * Capture/Compare 3 output enable
	 * Capture/Compare 4 output enable
	 */
	TIM4->CCR1 |= 2499;											// TIM4 Channel 1 pulse value is 2499
	TIM4->CCR2 |= 4999;											// TIM4 Channel 2 pulse value is 4999
	TIM4->CCR3 |= 7499;											// TIM4 Channel 3 pulse value is 7499
	TIM4->CCR4 |= 9998;											// TIM4 Channel 4 pulse value is 9999
	TIM4->RCR = 0;												// TIM4 Repetition Counter Value 0
	TIM4->CR1 |= 1 << 0;										// Counter Enable
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
  while (1)
  {

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
