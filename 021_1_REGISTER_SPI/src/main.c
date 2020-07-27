#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

short retX;
short retY;

void RCC_Config()
{
	RCC->CR |= 0x00030000;					// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));			// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;					// CSS Enable
	RCC->CR |= 0x01000000;					// PLL ON
	RCC->PLLCFGR |= 0x00400000;				// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;				// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;				// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;				// PLL p = 2
	RCC->CFGR |= 0x00000000;				// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;				// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;				// APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;					// HSERDY Flag clear
	RCC->CIR |= 0x00800000;					// CSS Flag clear
}

void GPIO_Config()
{
	// ports init: 15-MOSI, 14-MISO, 13-SCK, 12-SEL
	RCC->AHB1ENR |= 0x00000002;    // GPIOB portunun saatini aktif et
	GPIOB->MODER &= ~0x80000000; // PB 15 => sadece giriþ pini olarak ayarla
	GPIOB->MODER |= 0x45000000;   // PB 15,13,12 => çýkýþlar
	GPIOB->ODR |= 0xc000;              // SEL & SCK -> high
}

char  SPI_Transaction(uint8_t AandD)
{
	 int data = 0;
	 GPIOB->ODR &= ~0x1000;            // SPI seçilir

	 for (char k=0; k<16; k++) 		  // 16 bti için for döngüsü kur.
	 {
		 if (AandD & 0x8000)
			 GPIOB->ODR |= 0x8000; 	  // adres ve veri gönd
		 else
			 GPIOB->ODR &= ~0x8000;

		 AandD << 1;                 // adres ve veri için ilk bit
		 GPIOB->ODR &= ~0x2000;       // SCK Low yap.
		 for (int i=0; i<10;i++);     // 150ns zaman gecikmesi
		 data << 1;                   // okunan bit saða kaydýr
		 GPIOB->ODR |= 0x1000;        // SPI tamam
		 GPIOB->ODR |= 0x2000;        // SCK High yap
		 if (GPIOB->IDR & 0x4000)
			 data++;        		  // bit oku ve string’e ekle
	 };
	 GPIOB->ODR |= 0x2000;            // Slave Select pasif yap.
	 return  ((char) (data & 0xff));  // okunan veri ile geri dön.
}

void SPI_Write(uint8_t address, uint8_t data)
{
	SPI_Transaction (((address & 0x3f) << 8) + data);  // 16-biti hazýrla
}

char SPI_Read(uint8_t address)
{
	char Ret = SPI_Transaction(((address & 0x3f) << 8) + 0x8000);  // 16 bit
	return (Ret);
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	SPI_Write(0x20, 0xc7);                 // CR1: power-up, tüm eksenler
	SPI_Write(0x21, 0x40);                // CR2: Block data update & 12 bit mode
	SPI_Write(0x22, 0x00);                // CR3: filtre yok
  while (1)
  {
      retX = SPI_Read(0x28) + (SPI_Read(0x29) << 8); // x ekseni, her iki byte
      retY = SPI_Read(0x2a) + (SPI_Read(0x2b) << 8); // y ekseni, her iki byte
      for (int i=0; i<1000000; i++) {};                            // yaklaþýk 30ms zaman gecikme
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
