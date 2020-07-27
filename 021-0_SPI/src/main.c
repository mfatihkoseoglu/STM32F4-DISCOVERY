#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
SPI_InitTypeDef SPI_InitStruct;

uint8_t x,y,z;
uint8_t x_address = 0x29, y_address = 0x2B, z_address = 0x2D, m_data = 0x00;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* SPI SCK-MOSI-MISO pin Ayarlari */

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);	// SCK pin
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);	// MOSI pin
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);	// MISO pin

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft|SPI_NSSInternalSoft_Set;

	SPI_Init(SPI1, &SPI_InitStruct);

	SPI_Cmd(SPI1, ENABLE);

	GPIO_SetBits(GPIOE, GPIO_Pin_3);	// CS pini lojik 1 e çekildi
}

void SPI_Tx(uint8_t adress, uint8_t data)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

	SPI_I2S_SendData(SPI1,adress);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

	SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

	SPI_I2S_SendData(SPI1,data);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

	SPI_I2S_ReceiveData(SPI1);

	GPIO_SetBits(GPIOE,GPIO_Pin_3);
}

uint8_t SPI_Rx(uint8_t address, uint8_t data)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);	// CS pini lojik 0 a çekildi

	address = address|0x80; // Okuma iþlemi yapýlacak

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));

	SPI_I2S_SendData(SPI1, address);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));

	SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));

	SPI_I2S_SendData(SPI1, data);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

	SPI_I2S_ReceiveData(SPI1);

	GPIO_SetBits(GPIOE,GPIO_Pin_3); //CS pini lojik 1 e çekildi

	return SPI_I2S_ReceiveData(SPI1);
}

int main(void)
{
	config();
	SPI_Tx(0x20,0x67); //100 Hz , 9.2 G //

  while (1)
  {
	  x = SPI_Rx(x_address, m_data);
	  y = SPI_Rx(y_address, m_data);
	  z = SPI_Rx(z_address, m_data);

	  if(x < 139 && y < 139 && z < 169)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }

	  else if(x > 140 && x < 160)
	  {
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		  GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  }
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return -1;
}
