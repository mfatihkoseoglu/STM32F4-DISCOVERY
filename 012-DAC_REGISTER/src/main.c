#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i;

void delay(uint32_t time)
{
	while(time--)
	{

	}
}

void config()
{
	RCC->AHB1ENR = 0x00000001;
	RCC->APB1ENR = 0x20000000;

	DAC->CR = 0x00000001;	// DAC1 enable
	DAC->SWTRIGR = 0x00000000;	// DAC1 software trigger disable
	DAC->DHR12R1 = 0x00000FFF;  // DAC channel 1 12-bit right-aligned data
	//DAC->DOR1 = 0x00000FFF; 	// DAC channel 1 data output
}

int main(void)
{
 	config();
  while (1)
  {
	  for(i = 0; i<4096; i++)
	  {
		  DAC->DHR12R1 = i; // i derðerlerini DAC1 e gönderiyoruz.
		  delay(10000);
	  }

	  i = 0;
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
