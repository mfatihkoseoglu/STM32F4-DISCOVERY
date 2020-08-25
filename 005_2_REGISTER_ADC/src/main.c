#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t adc_value;

void RCC_Config()
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
}

void GPIO_Config()
{
	RCC->AHB1ENR |= 0x00000001;	// GPIOA Clock Enable

	GPIOA->MODER |= 0x00000003;	// Pin 0 Analog
	GPIOA->OSPEEDR |= 0x00000003;	// Pin 0 100MHz;
}

void ADC_Config()
{
	RCC->APB2ENR |= 0x00000100;	// ADC1 Clock enable

	ADC1->CR1 |= 0x02000000;	// Resolution 8 bit
	ADC1->CR2 |= 0x00000001;	// ADC enable
	ADC1->SMPR2 |= 0x00000003;	// 56 Cycles
	ADC->CCR |= 0x00010000;		// Div 4
}

uint8_t Read_ADC()
{
	uint8_t value;

	ADC1->CR2 |= 0x40000000;

	while(!(ADC1->SR & 0x00000002));

	value = ADC1->DR;

	return value;
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = Read_ADC();
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
