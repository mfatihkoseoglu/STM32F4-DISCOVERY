#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t data;

void FLASH_Write(uint32_t address, uint32_t data)
{
	FLASH_Unlock();

	FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);

	FLASH_ProgramWord(address, data);

	FLASH_Lock();
}

uint32_t FLASH_Read(uint32_t address)
{
	uint32_t myFlashData;

	myFlashData = *(uint32_t*)address;

	return myFlashData;
}

int main(void)
{
	//FLASH_Write(0x080E0000, 0xAA);
	FLASH_Write(0x080EE000, 0xAA);
  while (1)
  {
	  data = FLASH_Read(0x080E0000);
  }
}

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
