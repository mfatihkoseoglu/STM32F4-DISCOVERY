#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define BufferLength  2

uint16_t ADC1ConvertedValue[BufferLength] = {0, 0};

uint16_t adc_value1;
uint16_t adc_value2;

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
DMA_InitTypeDef DMA_InitStruct;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void ADC_DMA_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_DeInit(DMA2_Stream0); // Önceki tanýmlamalarý resetler ve default deðerleri yükler.

	DMA_InitStruct.DMA_Channel = DMA_Channel_0; // ADC1
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh; // öncelik atamasý yapýlýr
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR; // deðerin nereden okunduðunu veren ifadedir ADC_DR adres deðeri
	// vermek zorundayýz.// 0x4001204C olarakta yazýlabilirdi. ADC1 registerinin adresidir.
	// Peripheral base adresi olduðu gibi memory base adreside var. Bu da deðiþkenimizin adresidir.
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) &ADC1ConvertedValue;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory; // nereden nereye yazdýðýmýzý belirtmemiz gereken ifadedir.
	DMA_InitStruct.DMA_BufferSize = BufferLength; // kanal sayýsý
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // yazcaðýmýz veri yeri sabit mi deðiþken mi olduðunu belirttiðimiz nokta
	// Disable yaptýk yani adres sabit deðiþkenlik yok (okuyacaðýmýz register hep ayný olduðu için)
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; // Hafýzaya yazma iþlemi hep yanyana yazýlacak bu sebeple
	// farklý noktalarda yazýlacaðý için memory adresi sürekli deðiþecek diyoruz.
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // okunacak veri 12bit ama 16b demektir bu
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // Yazýlacak verinin data size 12bit yazcaz o yüzden halfword 16bit
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular; // DMA nýn nasýl çalýþacaðýný gireceðiz. Devamlý diyoruz.
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable ; // First Input First Output
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull; // eþik deðerini verir. Yarý dolu dedik
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single; // burst patlatmak memeory ve peripheral için ayný olmalý
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //

	DMA_Init(DMA2_Stream0, &DMA_InitStruct);

	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; // Eðer çok kanallý DMA okuyacaksak aktif etme
	// miz gerekir. Tek kanal okuduðumuz için disable edebiliriz.
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles; // iki örnek arasý bekleme

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // herhangi bir yerden harici tetik almayacak
	ADC_InitStruct.ADC_ExternalTrigConv = 0; // Çevrim tetiði almayacak
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; // Saða dayalý mý sola dayalýmý
	ADC_InitStruct.ADC_NbrOfConversion = BufferLength;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; // iþlemin sürekli olarak devam etmesini saðlýyoruz

	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_DMACmd(ADC1, ENABLE);



	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_56Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
}

int main(void)
{
 	config();
	ADC_DMA_config();

	ADC_SoftwareStartConv(ADC1);	// ADC1 için ADC iþlemini yazýlýmsal olarak baþlattýk
  while (1)
  {
	  adc_value1 = ADC1ConvertedValue[0];
	  adc_value2 = ADC1ConvertedValue[1];
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
