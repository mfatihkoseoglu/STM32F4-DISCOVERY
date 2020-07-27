#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h> // C dilinin standart kütüphanesi.
#include <stdlib.h>

char str[50];
int i;

// USART ile ekrana string yazdirmak için gerekli fonksiyon.
void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s)
	{
		while( !(USARTx->SR & 0x00000040) );

		USART_SendData(USARTx, *s);
		*s++;
	}
}

int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // USART2'ye clock sinyali verdik.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   // GPIOA portuna clock sinyali verdik.

	// Rx bacaginin konfügirasyonlarini yaptik. A portunun 2. bacagi.
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // Bu Rx bacagini alternatif fonksiyon olarak kullanacagimizi belirttik.


	// USART'in konfügirasyonlarini yaptik.
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	USART_Cmd(USART2, ENABLE); //USART2 aktif hale getirirldi.

	while(1)
	{
		sprintf(str,"n0.val="); // Ekrana yazdirmak istedigimiz cümleyi str char'ina attik.
		USART_puts(USART2,str); // USART_puts fonksiyonu ile de bu str char'ini ekrana yazdirdik.
		i=1200000;  // Bekleme yapmaniz gerekir aksi taktirde bilgisayariniz haberlesme hizina yetisemez ve mavi ekran hatasi verebilir.
		while(i)
		{
			i--;
		}
		sprintf(str,"100"); // Ekrana yazdirmak istedigimiz cümleyi str char'ina attik.
		USART_puts(USART2,str); // USART_puts fonksiyonu ile de bu str char'ini ekrana yazdirdik.
		i=1200000;  // Bekleme yapmaniz gerekir aksi taktirde bilgisayariniz haberlesme hizina yetisemez ve mavi ekran hatasi verebilir.
		while(i)
		{
			i--;
		}
		sprintf(str,"t4.txt="); // Ekrana yazdirmak istedigimiz cümleyi str char'ina attik.
		USART_puts(USART2,str); // USART_puts fonksiyonu ile de bu str char'ini ekrana yazdirdik.
		i=1200000;  // Bekleme yapmaniz gerekir aksi taktirde bilgisayariniz haberlesme hizina yetisemez ve mavi ekran hatasi verebilir.
		while(i)
		{
			i--;
		}
		sprintf(str,"adana"); // Ekrana yazdirmak istedigimiz cümleyi str char'ina attik.
		USART_puts(USART2,str); // USART_puts fonksiyonu ile de bu str char'ini ekrana yazdirdik.
		i=1200000;  // Bekleme yapmaniz gerekir aksi taktirde bilgisayariniz haberlesme hizina yetisemez ve mavi ekran hatasi verebilir.
		while(i)
		{
			i--;
		}
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
