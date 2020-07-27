#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Common deðerleri default olarak gelir.
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;  // Clock sinyalini 4 e böldük.

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;

	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_Cmd(ADC1, ENABLE); // ADC hattýný aktif ettik. Eðer bu satýr unutulursa önceki tanýmlamalarýn hiçbir önemi yok.
}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles); // ADC nin 1'i , kanal 0, rank 1, ve
	// örnek alma döngüsü 56Cycle örnek alma süremiz azaldýkça akým çekme deðeri artar ve sinyalin kalitesi yükselir
	ADC_SoftwareStartConv(ADC1); // Yazýlýmsal olarak ADC Dönüþümünü baþlat demektir.

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // ADC Hesaplanma iþlemi bitene kadar beklemesini söylüyoruz.

	return ADC_GetConversionValue(ADC1);	// ADC1 de okunan deðeri okuyup gönderdik.
}

int main(void)
{
	config();
  while (1)
  {
	  adc_value = Read_ADC();

	  if(adc_value <= 820)
	  {
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }
	  else if(adc_value > 820 && adc_value <= 1640)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }
	  else if(adc_value > 1640 && adc_value <= 2460)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
	  }
	  else if(adc_value > 2460 && adc_value <= 3280)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	  }
	  else if(adc_value > 3280 && adc_value <= 4095)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }
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
