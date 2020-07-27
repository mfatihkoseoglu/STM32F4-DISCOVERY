#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "i2c-lcd.h"

GPIO_InitTypeDef GPIO_InitStruct;
I2C_InitTypeDef I2C_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);	// SCL pini
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1); // SDA pini

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pin6 SCL, Pin7 SDA
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void I2C_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStruct.I2C_Ack = ENABLE;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;

	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

void I2C_Write(uint8_t address, uint8_t data)
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));  // I2C Meþgul olduðu sürece bekle

	I2C_GenerateSTART(I2C1, ENABLE);	// I2C Haberleþmesini baþlattýk.

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ));

	I2C_SendData(I2C1, data);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	GPIO_Config();
	I2C_Config();
	lcd_init();
  while (1)
  {
	  lcd_send_cmd(0x80);
	  lcd_sende_string("Muhammed");
	  delay(63000000);
	  lcd_send_cmd(0xC3);
	  lcd_sende_string("Fatih");
	  delay(63000000);
	  lcd_send_cmd(0x01);
	  delay(2100000);
	  /*
	  lcd_send_cmd(0x80);
	  lcd_sende_string("M");
	  delay(21000000);
	  lcd_send_cmd(0x81);
	  lcd_sende_string("E");
	  delay(21000000);
	  lcd_send_cmd(0x82);
	  lcd_sende_string("R");
	  delay(21000000);

	  lcd_send_cmd(0x83);
	  lcd_sende_string("H");
	  delay(21000000);
	  lcd_send_cmd(0x84);
	  lcd_sende_string("A");
	  delay(21000000);
	  lcd_send_cmd(0x85);
	  lcd_sende_string("B");
	  delay(21000000);
	  lcd_send_cmd(0x86);
	  lcd_sende_string("A");
	  delay(42000000);
	  lcd_send_cmd(0x01);
	  delay(2100000);
	  */
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
