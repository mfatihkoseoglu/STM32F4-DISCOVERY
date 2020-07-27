#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t adc;
uint32_t adc1[8];

void RCC_Config()
{
	RCC->CR |= 0x00030000;	// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;	// CSS Enable
	RCC->CR |= 0x01000000;	// PLL ON
	RCC->PLLCFGR |= 0x00400000;	// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;	// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;	// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;	// PLL p = 2
	RCC->CFGR |= 0x00000000;	// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;	// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;	// APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;		// HSERDY Flag clear
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

	ADC->CCR 	|= 1 << 16;		// ADC Clock Divided By 4
	//ADC1->SMPR2 |= 6 << 0;	// 144 Cycles for Channel 0
	ADC1->CR1 	|= 0 << 24;		// ADC Resolution 12 bit
	ADC1->CR1	|= 1 << 8;		// Scan conversion mode enable
	ADC1->CR2   |= 1 << 0;		// ADC enable
	ADC1->CR2   |= 1 << 1;		// Continuous conversion mode enable
	ADC1->CR2   |= 1 << 8;		// DMA Enable
	ADC1->CR2   |= 1 << 9;		// DDS
	ADC1->CR2   |= 1 << 10;		// EOCS
	//ADC1->CR2   |= 1 << 30;	//
	ADC1->SQR1 	|= 0 << 20;		// L = 1 conversion number
	ADC1->SQR3  |= 0 << 0;		// put channel number CH0

}

void DMA_Config()
{
	RCC->AHB1ENR |= 0x00400000;			// RCC->AHB1ENR |= (1<<22); // DMA2 clk Enable

	while((DMA2_Stream4->CR & 0x00000001) == 1);	// wait for stream4 to be 0(stop)

	DMA2_Stream4->PAR|= (uint32_t) &ADC1->DR;
	DMA2_Stream4->M0AR |= (uint32_t) &adc1;
	DMA2_Stream4->NDTR = 1;
	DMA2_Stream4->CR |= 0 << 6;	 	// Peripheral to Memory
	DMA2_Stream4->CR |= 1 << 8;		// Circular mode
	DMA2_Stream4->CR |= 1 << 10;		// memory incremented
	DMA2_Stream4->CR |= 2 << 11;		// peripheral data size 32 bit (word)
	DMA2_Stream4->CR |= 2 << 13;		// memory data size 32 bit (word)
	DMA2_Stream4->CR |= 2 << 16;		// priority level high
	DMA2_Stream4->CR |= 0 << 25;		// channel 0 selected
	DMA2_Stream4->FCR |= 0 << 2;		// direct mode enable
	DMA2_Stream4->CR |= 1 << 0;			// start stream 4
	//ADC1->CR2 |= ADC_CR2_SWSTART;
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	DMA_Config();
	ADC1->CR2 |= ADC_CR2_SWSTART;  //start conversion
  while (1)
  {
	  //if(DMA2->HISR == 0x00000030)
	//  {
		//  DMA2->HIFCR = 1 << 5 | 1 << 4;  // Clear DMA Transfer Complete Flag
	  //}
	  adc = adc1[0];
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
