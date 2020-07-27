#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t Random;

void RCC_Config()
{
	unsigned int i;

	for (i=0;i<0x00100000;i++);       // OSC oturtma ve kurtarma rutini
	RCC->CFGR |= 0x00009400;          // AHB ve APB hizlarini max degerlere set edelim
	RCC->CR |= 0x00010000;            // HSE Xtal osc calismaya baslasin
	while (!(RCC->CR & 0x00020000));  // Xtal osc stabil hale gelsin

	RCC->PLLCFGR = 0x07402A04;        // PLL katsayilarini M=4, N=168, P=2 ve Q=7 yapalim   168 Mhz
	RCC->CR |= 0x01000000;            // PLL calismaya baslasin  (Rehber Sayfa 95)
	while(!(RCC->CR & 0x02000000));   // Pll hazir oluncaya kadar bekle
	FLASH->ACR = 0x00000605;          // Flash ROM icin 5 Wait state secelim ve ART yi aktif edelim (Rehber Sayfa 55)
	RCC->CFGR |= 0x00000002;          // Sistem Clk u PLL uzerinden besleyelim
	while ((RCC->CFGR & 0x0000000F) != 0x0000000A); // Besleninceye kadar bekle
}

void GPIO_Config()
{
    RCC->AHB1ENR |= 0x00000009;       // GPIO A,D clock'u aktif edelim
    GPIOD->MODER  = 0x55550000;       // GPIOD nin 15, 14, 13, 12, 11, 10, 9, 8 pinleri cikis tanimlandi (LEDler icin)
    GPIOD->OSPEEDR= 0xFF000000;       // GPIOD nin tum cikislari en yuksek hizda kullanacagiz
}

void RNG_Config()
{
    RCC->AHB2ENR |= 0x40;              // RNG modulunun clock'unu aktif edelim
    RNG->CR=0x04;			  			// RNG modulu calismaya basladin
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	RNG_Config();
  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  while(GPIOA->IDR & 0x00000001);
		  delay(1680000);

		  while (!(RNG->SR&1));    // kullanilabilir sayi olusumunu bekle
		  Random=RNG->DR;
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
