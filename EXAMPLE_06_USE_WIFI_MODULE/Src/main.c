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

#include <string.h>
#include <stdio.h>

#define ESP8266BUFFER_LENGHT 500

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
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

char tx_buffer[100];
char rx_buffer[100];
char transmitdata[100];
char transmitconf[100];
char g_arrui8ESP8266Buf[ESP8266BUFFER_LENGHT];

uint16_t ESPWriteIndex=0;

uint16_t potdegeri;
uint16_t adc_value;

int length;
int say=0;
int say2=0;
int say3=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

uint16_t Read_ADC(void);
static void Clear_ESPBuffer(void);
static void ESP8266_Init(void);

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
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  Clear_ESPBuffer();
  HAL_Delay(400);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  ESP8266_Init();
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

static void ESP8266_Init(void)
{
	static uint8_t ESPInitCase = 0;

	switch (ESPInitCase) {
		case 0:
			 // Standart AT Komutu gonderilir , Cevabi OK olmalidir.
			HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT\r\n"), 500);
			ESPInitCase = 1;
			HAL_Delay(500);
			break;
		case 1:
			 // STRSTR fonksiyonu metin icinde metin arayan bir fonksiyondur
			 // Eger aranilan metni bulabilirse pointer adresi ile geri donus yapar
			 // Bulamaz ise NULL dondurur. Bizde null'dan farkli mi diye sorariz.
			if(strstr(g_arrui8ESP8266Buf, "OK") != NULL)
			{
				Clear_ESPBuffer();
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "\nModule erisildi.\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 1\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, &g_arrui8ESP8266Buf[100]), 100);
				ESPInitCase = 2;
			}
			else
			{
				Clear_ESPBuffer();
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "\nModule erisilemedi. Tekrar deneniyor.\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 1\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, &g_arrui8ESP8266Buf[100]), 100);
				ESPInitCase = 0;
			}
			break;
		case 2:
			// Modulun 3 modu var gerekli bilgi datasheet'de biz 1 olmasini istiyoruz
			HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT+CWMODE?\r\n"), 100);
			HAL_Delay(1000);
			HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 2\n"), 100);
			 ESPInitCase = 3;
			break;
		case 3:
			if (strstr(g_arrui8ESP8266Buf,"+CWMODE:1") != NULL)
			 {
				Clear_ESPBuffer();
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Mod ayari dogru.\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 3\n"), 100);
				ESPInitCase = 4;
			 }
			else
			{
				// Fabrika ayarlari olarak 2 geliyor biz onu 1 yapip reset komutu ile tamamlariz.
				HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT+CWMODE=1\r\n"), 100);
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 3\n"), 100);
				HAL_Delay(1000);
				Clear_ESPBuffer();
				HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Mod ayari degistirildi.\n"), 100);
				ESPInitCase = 4;
			}
			break;
		case 4:
			 // Baglanilacak olan wifi agina ait kullanici adi ve sifre girisi yapilir.
			HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT+CWJAP=\"MFKtel\",\"mfatihkoseoglu\"\r\n"), 100);
			HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 4\n"), 100);
			HAL_Delay(1000);
			ESPInitCase = 5;
			break;
		case 5:
			 // Baglanti saglandiginde OK Cevabi alinir
			 if (strstr(g_arrui8ESP8266Buf,"OK") != NULL)
			 {
				 Clear_ESPBuffer();
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Modeme Baglanti yapildi\n"), 100);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 5\n"), 100);
				 ESPInitCase = 6;
			 }
			 else
			 {
				 HAL_Delay(1000);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Modeme Baglanti Bekleniyor.\n"), 100);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 5\n"), 100);
				 HAL_Delay(1000);
				 say2++;
				 if(say2 == 3)
				 {
					 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Modeme baglanilamadi\n"), 100);
					 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 5\n"), 100);
					 ESPInitCase=8;
					 say2=0;
				 }
			 }
			break;
		case 6:
			// IP adresi nedir diye soruyoruz ?
			HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT+CIFSR\r\n"), 100);
			// 1 saniye gecikme koyuyoruz.
			HAL_Delay(1000);
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 6\n"), 100);
			ESPInitCase = 7;
			break;
		case 7:
			 // IP alana kadar error bilgisi gonderir. Onu ayiririz. =)
			 if (strstr(g_arrui8ESP8266Buf,"ERROR") == NULL)
			 {
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Alinan IP = \n"), 100);
				 // Gelen bilginin 11.karakterinden itibaren IP adresi yaziyor.
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, &g_arrui8ESP8266Buf[11]), 100);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 7\n"), 100);
				 Clear_ESPBuffer();
				 ESPInitCase=8;
			 }
			 else
			 {
				 // ERROR der ise tekrar dene
				 HAL_Delay(1000);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Tekrar deneniyor. \n"), 100);
				 Clear_ESPBuffer();
				 ESPInitCase=6;
			 }
			break;
		case 8:
			// Baglanilacak siteye ait bilgiler girildi.
			HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, sprintf(tx_buffer, "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"), 100);
			// 1 saniye gecikme koyuyoruz.
			HAL_Delay(1000);
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 8\n"), 100);
			ESPInitCase = 9;
			break;
		case 9:
			 // Baglanti kuruldugunda Linked diye bir cevap aliriz.
			 if (strstr(g_arrui8ESP8266Buf,"CONNECT") != NULL)
			 {
				 Clear_ESPBuffer();
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Site ile baglanti kuruldu\n"), 100);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 9\n"), 100);
				 ESPInitCase = 10;
			 }
			 else
			 {
				 // Cevap gelene kadar bekler
				 HAL_Delay(1000);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Siteye Baglanti Bekleniyor.\n"), 100);
			 	 HAL_Delay(5000);
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 9\n"), 100);
			 	 say++;
			 	 if(say==3)
			 	 {
					 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Siteye Baglanti kurulamadi.\n"), 100);
			 		 ESPInitCase=8;
					 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "EspInitCase = 9\n"), 100);
			 		 say=0;
			 	 }
			 }
			break;
		case 10:
		 potdegeri = Read_ADC(); // adc okunuyor

		 sprintf(transmitdata, "GET /update?key=BYLL8GABRL1MYA4T\r\n", potdegeri);


		 length=strlen(transmitdata); // gönderilecek datanin uzunlugu
		 length=length+2;

		 HAL_UART_Transmit(&huart1, (uint8_t*)transmitconf, sprintf(transmitconf, "AT+CIPSEND=%d\r\n", length), 100);
		 // Komutu verdikten sonra bize '>' bilgisi geliyor.
		 HAL_Delay(1000);

		 if (strstr(g_arrui8ESP8266Buf,">") != NULL)
		 {
			 Clear_ESPBuffer();
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Gönderilen data uzunlugu kabul edildi\n"), 100);
			 HAL_UART_Transmit(&huart1, (uint8_t*)transmitdata, sprintf(transmitdata, "GET /update?key=BYLL8GABRL1MYA4T\r\n",potdegeri), 100);
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Data gönderildi\n"), 100);
			 HAL_Delay(2000);
			 ESPInitCase=10;
		 }
		 else
		 {
			 // Cevap gelene kadar bekler
			 HAL_Delay(3000);
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "gönderilen data uzunlugu kabul edilmedi\n"), 100);
			 ESPInitCase=8;
			 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Siteye yeniden baglanilmaya çalisiliyor\n"), 100);
			 say3++;
			 if(say3==3)
			 {
				 HAL_UART_Transmit(&huart3, (uint8_t*)tx_buffer, sprintf(tx_buffer, "Baglanti kurulamadi.\n Ayarlar kontrol edilecek\n"), 100);
				 ESPInitCase=0;
				 say3=0;
			 }
		 }
		 break;
	}
}

uint16_t Read_ADC(void)
{
	HAL_ADC_Start(&hadc1);	// ADC1 dönüşümü başlatıldı
	if(HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK)	// ADC yi yoklar ve dönüşümün bitmesini bekler.
		adc_value = HAL_ADC_GetValue(&hadc1);	// ADC1 i oku, değeri al, adc_value değişkenine ata
	HAL_ADC_Stop(&hadc1);	// ADC1 dönüşümünü durdur
	return adc_value;
}

static void Clear_ESPBuffer(void)
{
	 uint16_t i;

	 for(i = 0; i < ESP8266BUFFER_LENGHT; i++)
		 g_arrui8ESP8266Buf[i] = 0;

	 ESPWriteIndex = 0;
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
