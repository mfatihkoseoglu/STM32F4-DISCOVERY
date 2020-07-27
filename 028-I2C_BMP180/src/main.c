#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_bmp180.h"

int temperature,pressure,altitude;

int main(void) {

	TM_BMP180_t BMP180_Data;

	SystemInit();

	TM_DELAY_Init();

    if (TM_BMP180_Init(&BMP180_Data) == TM_BMP180_Result_Ok) {

    } else {

        while (1);
    }

	while (1) {

        TM_BMP180_StartTemperature(&BMP180_Data);

        Delay(BMP180_Data.Delay);

        TM_BMP180_ReadTemperature(&BMP180_Data);

        TM_BMP180_StartPressure(&BMP180_Data, TM_BMP180_Oversampling_UltraHighResolution);

        Delay(BMP180_Data.Delay);

        TM_BMP180_ReadPressure(&BMP180_Data);

        temperature = BMP180_Data.Temperature;
        pressure = BMP180_Data.Pressure;
        altitude = BMP180_Data.Altitude;

        Delayms(1000);
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
