#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t m_FlashData;

void RCC_Config()
{
	RCC->CR |= 0x00030000;										// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));								// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;										// CSS Enable
	RCC->CR |= 0x01000000;										// PLL ON
	RCC->PLLCFGR |= 0x00400000;									// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;									// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;									// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;									// PLL p = 2
	RCC->CFGR |= 0x00000000;									// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;									// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;									// APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;										// HSERDY Flag clear
	RCC->CIR |= 0x00800000;										// CSS Flag clear
}

void FLASH_UnLock(void)
{
	/*
	 * FLASH_CR kaydýnýn kilidini açmak ve programlama/silme iþlemlerini saðlamak için FLASH->KEYR
	 * kaydedicisine KEY1 ve KEY2 deðerleri sýrasýyla yazýlmalýdýr.
	 */
	while ((FLASH->SR & 0x00010000) != 0 );	// Flash belleðin meþgul olmamasýný bekle

	if(FLASH->CR & 0x80000000)				// Flaþ'ýn kilidinin açýk olup olmadýðýný kontrol et
	{
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xCDEF89AB;
	}
}

void FLASH_Locker(void)
{
	/*
	 * FLASH_CR kaydýnýn kilitlemek ve programlama/silme iþlemlerini durdurmak için FLASH->CR
	 * kaydedicisinin LOCK bitine 1 yazýlmalýdýr.
	 */
	FLASH->CR |= 0x80000000;
}

void FLASH_Erase(void)
{
	/*
	 * Silmek demek Flaþ'ý 0x0000 yapmak demek deðil 0xFFFF yapmak demektir.
	 * Silme iþlemi için:
	 * 	1- Status registerindaki busy(BSY) bitini kontrol ederek Flash belleði iþlemlerinin devam etmediðini doðrula.
	 * 	2- CR kaydedicisindeki SER bitini ayarla ve silmek istediðin sectoru ana bellek bloðundaki SNB den belirle
	 * 	3- CR kaydedicisindeki STRT bitini ayarla
	 * 	4- Status registerindaki busy(BSY) bitinin temizlenmesini bekle
	 */
	// Bayraklarý temizle
	FLASH->SR |= 0x00000001;				// End of Operation flag clear
	FLASH->SR |= 0x00000040;				// Programming Parallelism error flag clear
	FLASH->SR |= 0x00000010;				// Write protected error flag clear

	while((FLASH->SR & 0x00010000) != 0);	// Meþguliyet bitene kadar bekle
	FLASH->CR |= 0x00000002;				// sektör silme bitini ayarla (SER)
	FLASH->CR |= 11 << 3;					// Sektör 11 silinecek sektör olarak seçildi
	FLASH->CR |= 1 << 16;					// STRT biti 1 olarak ayarlandý
	while(FLASH->SR & 0x00010000);			// Ýþlemler bitene kadar bekle

	if((FLASH->SR & 0x00000001) != 0)		// Ýþlem sonu biti ayarlandý ise
	{
	    FLASH->SR |= 0x00000001;			// Ýþlem baþarýlý oldu, iþlem sonu baðraðý temizle
	}
	FLASH->CR &= ~0x00000002; 				// CR register'ý PER biti baþlangýçtaki duruma ayarla
}

void FLASH_Write(uint32_t address, uint32_t data)
{
	/*
	 * Yazma iþlemi için:
	 * 	1- Status register'ýndaki busy(BSY) bitini kontrol ederek Flash belleði iþlmelerinin devam etmediðini doðrula
	 * 	2- CR kaydedicisindeki Programming Enable(PG) bitini ayarla
	 * 	3- Veri yazma iþlemini istenilen adrese yap (ana hafýza bloðu veya OTP içerisinde)
	 * 		- x8 paralelliði durumunda bayt eriþimi
	 * 		- x16 paralellik durumunda yarým kelimelik eriþim
	 * 		- x32 paralellik durumunda kelime eriþimi
	 * 		- x64 paralellik durumunda çift kelime eriþimi
	 * 	4- Status register'ýndaki busy(BSY) bitinin temizlenmesini bekle
	 */
	while(FLASH->SR & 0x00010000);		// Meþguliyet bitene kadar bekle
	FLASH->CR |= 0x00000001;			// PG biti ayarlandý, Programmin modda
	FLASH->CR |= 2 << 8;				// Program size 32
	*(__IO uint32_t*)address = data;	// Ýstenilen adrese istenilen veri yazýlýyor.
	while(FLASH->SR & 0x00010000);		// Ýþlemler bitene kadar bekle

	if((FLASH->SR & 0x00000001) != 0)	// Ýþlem sonu biti ayarlandý ise
	{
	     FLASH->SR |= 0x00000001;		// Ýþlem baþarýlý oldu, iþlem sonu baðraðý temizle
	}

	FLASH->CR &= ~0x00000001;			// CR register'ý PG biti baþlangýçtaki duruma ayarla
}

uint32_t FLASH_Read(uint32_t address)
{
	uint32_t myFlashData;

	myFlashData = (*(uint32_t*)address);

	return myFlashData;
}

int main(void)
{
	RCC_Config();

	FLASH_UnLock();
	FLASH_Erase();
	FLASH_Write(0x080E0000, 0xDB);
	FLASH_Locker();
	FLASH_UnLock();
	m_FlashData = FLASH_Read(0x080E0000);
	FLASH_Locker();
  while (1)
  {

  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
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
