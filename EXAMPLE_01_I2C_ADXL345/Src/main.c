/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* ADXL345 in datasheetinde I2C nin adresi 0x53 olarak vermiş. Aşağıdaki yazdığımız
algoritma ile bunu kesinleştirmek istiyorum. bknz. Scan_I2C_Address function*/

#define ADXL_ADDRESS 0xA6	// 0x53 << 1 şeklinde de ifade edilebilir.

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

uint8_t i;
uint8_t data_rec[6];
int16_t x,y,z;
float xg, yg, zg;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

void Scan_I2C_Address();
void ADXL_Init();
void ADXL_Write(uint8_t reg, uint8_t value);
void ADXL_Read(uint8_t reg, uint8_t numberOfBytes);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  Scan_I2C_Address();

  ADXL_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  ADXL_Read(0x32, 6);
	  x = (data_rec[1] << 8) | data_rec[0];
	  y = (data_rec[3] << 8) | data_rec[2];
	  z = (data_rec[5] << 8) | data_rec[4];

	  // Bu işlemin ardından eksendeki ivmeyi kontrol etmek için bu verileri g şeklinde dönüştürmemiz gerekir. Yukarıdakileri
	  // başlatma bölümünde +-4g aralığını belirttiğimiz gibi kontrol etmelisiniz. Datasheete göre +-4g aralığında ölçek faktörü 7,8mg/LSB'dir.

	  // Bu yüzden g'ye dönüştürmek için .0078 ile çarpmamız gerekiyor.

	  xg = x * .0078;	// convert the x value g
	  yg = y * .0078;	// convert the y value g
	  zg = z * .0078;	// convert the z value g

	  HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Scan_I2C_Address()
{
	for(i=0; i<=255; i++)
	{
		if(HAL_I2C_IsDeviceReady(&hi2c1, i, 1, 10) == HAL_OK)
		{
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
			break;
		}
	}
}

void ADXL_Write(uint8_t reg, uint8_t value)
{
	uint8_t data[2]={0};
	data[0] = reg;
	data[1] = value;
	HAL_I2C_Master_Transmit(&hi2c1, ADXL_ADDRESS, data, 2, 100);
}

void ADXL_Read(uint8_t reg, uint8_t numberOfBytes)
{
	HAL_I2C_Mem_Read(&hi2c1, ADXL_ADDRESS, reg, 1, data_rec, numberOfBytes, 100);

	// 281.satır ve sonrasının ardından bu noktaya gelip, verileri okuruz. Veriler, DATAX0, DATAX1, DATAY0, DATAY1, DATAZ0, DATAZ1
	//şeklinde 0x32 ila 0x37 arasındaki Kayıtlarda depolanır. Her kayıt 8 bit veri depolar. bu sebeple 8 bitlik bir değişkene 6 farklı değeri kaydettik.

	// Burada MEM Read yapıyoruz. Çünkü belirli bir bellek adresinden yani 0x32'den okuyoruz ve bu adresten itibaren 6 byte veri okumak zorundayız.
	// Bundan sonra yapılması gereken işlem DATAX0 ve DATAX1 deki veriler tek bir veriye dönüştürülmeli bu işlem 125.satırda yapılır
}

void ADXL_Init()
{
	ADXL_Read(0x00, 1);		// Read adres: 0x00 and 1 bit if bits = 0xE5 sensor is true work
	// Kodlarımızı yazmadan önce, cihazın DEVID değerini kontrol ederek her şeyin yolunda olup olmadığından emin olmakta fayda var.
	// DEVID kaydı (0x00), 0xE5 sabit bir cihaz kimliği koduna sahiptir. Kod 0xE5 ile eşleşirse, çalışmaya devam edebilir, dataları okuyabiliriz.
	// 271.satır

	ADXL_Write(0x2D, 0);	// Reset all bits

	// Setup for measurement
	ADXL_Write(0x2D, 0x08);	// Measure bit-1, wake up 0, 0 at 8 hz (Ölçüm bitini set, wake up bitini reset ve frekansı 8Hz olarak ayarladık.)
	// Set to Range +- 4g
	ADXL_Write(0x31, 0x01);	// +- 4g range
	// And ok ready to read for value
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
