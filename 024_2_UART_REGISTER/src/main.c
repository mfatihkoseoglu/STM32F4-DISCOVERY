#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

unsigned char WAdr, RAdr;
char RxBuf[128];
int j = 0;

void Delay(uint32_t time)
{
	while(time--);
}

void RCC_Config()
{
	RCC->CR |= 0x00010000;		// HEON
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;			// CSS Enable
	RCC->CR |= 0x01000000;			// PLL On
	RCC->PLLCFGR |= 0x00400000;		// PLL HSE Selected
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// PLL N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL P = 2
	RCC->CFGR |= 0x00000000;		// AHB Prescaler 1
	RCC->CFGR |= 0x00080000;		// APB2 Prescaler 2
	RCC->CFGR |= 0x00001400;		// AHB1 Prescaler 4
	RCC->CIR |= 0x00080000;			// HSERDY Flag Clear
	RCC->CIR |= 0x00800000;			// CSS Flag Clear
}

void GPIO_Config()
{
	RCC->AHB1ENR  |= 0x00000002;		// GPIOB Clock Enable

	GPIOB->MODER  |= (2 << 20) | (2 << 22);		// AF PB10 AND PB11
	GPIOB->AFR[1] |= (7 << 8) | (7 << 12);		// PB10 & PB14 AF7 (USART3)
}

void USART_Config()
{
	RCC->APB1ENR |= 1 << 18;

	USART3->BRR = 0x1112;		// BaudRate 9600
			USART3->CR1 |= 1 << 2;		// Rx enable
	USART3->CR1 |= 1 << 3;		// Tx enable
	USART3->CR1 |= 1 << 5;		// Rx interrupt enable
	USART3->CR1 |= 0 << 10;		// Parity control disable
	USART3->CR1 |= 0 << 12;		// Word length 8bit
	USART3->CR2 |= 0 << 12;		// Stop bit 1
	USART3->BRR = 0x1112;		// BaudRate 9600
	USART3->CR1 |= 1 << 13;		// Usart enable
}

void NVIC_Config()
{
	NVIC->ISER[1] |= 0x80;
}

void SendChar(char Tx)
{
while(!(USART3->SR&0x80));  // TX Buffer dolu ise bekle (Rehber Sayfa 646)
USART3->DR=Tx;
}
void SendTxt(char *Adr)
{
while(*Adr)
{
SendChar(*Adr);
Adr++;
}
}
char DataReady()
{
	return (WAdr-RAdr);
}

char ReadChar()
{
	char Dat;
	Dat = RxBuf[RAdr];
	RAdr=(RAdr+1)&0x7F;
	return(Dat);
}

void USART3_IRQHandler()
{
	volatile int Sts;
	Sts=USART3->SR;
	RxBuf[WAdr]=USART3->DR;
	WAdr=(WAdr+1)&0x7F;
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	NVIC_Config();
	SendTxt("Hello World\n");
	for(int i=0;i<0x1000000;i++);         // Laf olsun diye bekledik
	while(DataReady()) ReadChar();
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
