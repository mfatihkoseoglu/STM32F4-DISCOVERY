#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

uint16_t count;

void SysTick_Handler()	// 1 ms de bir kesme olur ve bu sistem bu fonksiyona dallanýr.
{
	if(count > 0)
		count--;	// 1ms de bir bu iþlem yapýlýr.
}

void delay_ms(uint32_t time)
{
	count = time;

	while(count);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

int main(void)
{
	GPIO_Config();
	SysTick_Config(SystemCoreClock/1000);
		/*
		 *  SystemCoreClock/1000    -> 1ms de bir kesmeye girer.
		 *  SystemCoreClock/100000  -> 10 us de bir kesmeye girer.
		 *  SystemCoreClock/1000000 -> 1 us de bir kesmeye girer.
		 */
  while (1)
  {
	  GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  delay_ms(1000);
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
