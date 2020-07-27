#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t adc_value;
GPIO_InitTypeDef POT;

void GPIO_Config()
{
	RCC->AHB1ENR |= 0x00000009;

	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0xFF000000;
}

void ADC_Config()
{
	RCC->APB2ENR |= 0x00000100;

	GPIOA->MODER |= 0x00000003;

	ADC1->CR1 |= 0x02000000;
	ADC1->SMPR2 = 0x00000003;
	ADC->CCR |= 0x00010000;
	ADC1->CR2 |= 0x00000001;
}

uint16_t Read_ADC()
{
	ADC1->CR2 |= 0x40000000;	//  Start conversion of regular channels

	while(!(ADC1->SR & 0x00000002));

	return ADC1->DR;
}

int main(void)
{
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

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
