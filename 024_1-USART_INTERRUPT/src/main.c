#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>

/*
 * Bu örnekte hem bilgisayardan cihaza hemde cihazdan veri akýþý saðlayacaðýz
 * Bunu da kesme yardýmý ile yapacaðýz.
 * Uygulama ilk baþladýðýnda ekrana Ayarlar Tamamlandý! yazacak.
 * Seri port ekranýna kelimeyi girip enter tuþuna bastýðýmýz anda bu kelimeyi bizim ekranýmýza geri döndürecek.
 */

#define Max_Strlen 24 // Kelimemizin en fazla 24 karakter olacagini belirttik.
volatile char alinanString[Max_Strlen+1]; // Kelimemizi alinanString degiskenine atadik.
uint32_t sayici=0;
char cikti[50];

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

void config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	// Tx ve Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);	// Tx
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);	// Rx

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

void USART_puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s)
	{
		while(!(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}

/*
 * USART1'in kesme fonksiyonu. Seri porttan veri girildigi anda
 * kesme aktif olur ve bu fonksiyonun içerisi çalismaya baslar.
*/
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)) // Eger veri girisi yapildiysa. (bayrak kalktý ise)
	{
		char kelime= USART1 -> DR; // USART1'in registerindaki bilgiyi kelime degiskenine at.

		if( (kelime != '\n') && (sayici < Max_Strlen) ) // kelime degiskenini karakter sayisi boyunca tara.
		{
			alinanString[sayici]=kelime; // Ekrana girilmis olan kelimeyi alinanString degiskenine ata.
			sayici++; // sayiciyi 1 arttir.
		}
		else // kelime degiskenindeki karakter bittiyse.
		{
			alinanString[sayici]='\0'; // alinanString degerini sifirla.
			sayici=0;
			USART_puts(USART1,alinanString); // alinanString degiskenini ekrana yazdir.
		}
	}
}

int main(void)
{
	config();
	USART_puts(USART1, "Ayarlar Tamamlandi!\r\n"); // Baslangiçta ekrana ayarlar tamamlandi yazmasini belirttik.
  while (1)
  {

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
