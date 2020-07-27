//
//#include "STM32F4xx.h"
//#include "stdio.h"
//
//unsigned char WAdr,RAdr;
//char RxBuf[128];
//char TxBuf[128];
//unsigned char timer_update=0;
//uint16_t adc_val[4];
//uint8_t ch_index =0;
///*********************************************************************************
// CPU frekansi 168Mhz
// AHB frekansi 84 Mhz
// APB frekansi 42 Mhz
//*********************************************************************************/
//
//void SystemInit()
//{
//unsigned int i;
//      for (i=0;i<0x00100000;i++);     // OSC oturtma ve kurtarma rutini
//      RCC->CFGR |= 0x00009400;        // AHB ve APB hizlarini max degerlere set edelim
//      RCC->CR |= 0x00010000;          // HSE Xtal osc calismaya baslasin
//      while (!(RCC->CR & 0x00020000));// Xtal osc stabil hale gelsin
//      RCC->PLLCFGR = 0x07402A04;      // PLL katsayilarini M=4, N=168, P=2 ve Q=7 yapalim   168 Mhz
//      RCC->CR |= 0x01000000;          // PLL calismaya baslasin  (Rehber Sayfa 95)
//      while(!(RCC->CR & 0x02000000)); // Pll hazir oluncaya kadar bekle
//      FLASH->ACR = 0x00000605;        // Flash ROM icin 5 Wait state secelim ve ART yi aktif edelim (Rehber Sayfa 55)
//      RCC->CFGR |= 0x00000002;        // Sistem Clk u PLL uzerinden besleyelim
//      while ((RCC->CFGR & 0x0000000F) != 0x0000000A); // Besleninceye kadar bekle
//      RCC->AHB1ENR |= 0x0000001F;     // GPIO A,B,C,D,E clock'u aktif edelim
//      GPIOD->MODER  = 0x55550000;     // GPIOD nin 15, 14, 13, 12, 11, 10, 9, 8 pinleri cikis tanimlandi (LEDler icin)
//      GPIOD->OSPEEDR= 0xFFFFFFFF;     // GPIOD nin tum cikislari en yuksek hizda kullanacagiz
//     RCC->APB1ENR|=0x00000020;       // Timer7 CLK'u aktif edelim (84 Mhz)
//
//     TIM7->CR1=0x0080;               // Otomatik Reload
//     TIM7->PSC =839;                 // Prescaler degerimiz 839, Count frekansimiz = fCK_PSC / (Yuklenen Deger + 1) 84E6 / (840) = 100 KHz
//     TIM7->ARR =5;                   // Counter, Decimal 1 olunca basa donsun. Her 20 mikrosaniye de bir timer int olusacak.
//     TIM7->DIER=0x0001;              // Update Int enable
//     NVIC->ISER[1] = 0X00800000;     // NVIC de Timer 7 interrupta izin verelim
//     TIM7->CR1|=0x0001;              // Counter Enable
//
//     GPIOB->MODER |= 0x0000000F; //  B0 ve B1 analog
//     GPIOC->MODER |= 0x00000F00; //  C4 ve C5 analog
//
//     RCC->APB2ENR|=0x00000100;  // ADC saat kaynaðýný aktif ettik.
//     ADC1->CR1 |=0x00000120; //  ADC scan modunda çalýþacak. Interrupt aktif.
//	 NVIC_EnableIRQ(ADC_IRQn); // NVIC ADC kesmesini aktif ettik.
//
//     ADC1->SQR1 |= (3 << 20); // Kaç kanalý tarayacaðýmýzý bildiriyoruz. 20..23 bitler; 4 kanal
//     ADC1->SQR3 |= 8; // Çevrime ilk girecek kanal 8. (PB0)
//     ADC1->SQR3 |= (9 << 5); // Çevrime 2. sýrada girecek kanal 9. (PB1)
//     ADC1->SQR3 |= (14 << 10); // Çevrime 3. sýrada girecek kanal 14. (PC4)
//     ADC1->SQR3 |= (15 << 15); // Çevrime 4. sýrada girecek kanal 15. (PC5)
//	 ADC1->SMPR1 |=0xFFFFFFFF; // En düþük çevirim hýzý.
//	 ADC1->SMPR2 |=0xFFFFFFFF; // En düþük çevirim hýzý.
//
//     ADC1->CR2 |=0x00000403;   // AD converter'i açtýk. Sürekli çevirim yapacaðýz.
//	 						   // Her kanal çevrimi bittiðinde EOC set olacak.
//}
//
///********************************************************************************************************
//								ADC KESME RUTÝNÝ
//**********************************************************************************************************/
//void ADC_IRQHandler()
//{
//      	if(ADC1->SR & 0x0002){
//           	ADC1->SR &= ~0x0002;
//			adc_val[ch_index] = ADC1->DR;
//			if(++ch_index > 3)ch_index=0;
//        }
//
//}
//
//
//
///*********************************************************************************
//      USART3 modulunu kullanarak asenkron haberlesme (Hata kontrolu yapilmiyor)
//*********************************************************************************/
//void USART3_IRQHandler()
//{
//volatile int Sts;
//     Sts=USART3->SR;
//     RxBuf[WAdr]=USART3->DR;
//     WAdr=(WAdr+1)&0x7F;
//}
//
//
//void UsartInit()
//{
//     WAdr=0;RAdr=0;
//
//// USART3 MODULUNU AKTIF HALE GETIRELIM
//
//      RCC->APB1ENR|=0x00040000;  // USART3 Clk Enable (Rehber Sayfa 113)
//      RCC->APB1RSTR|=0x00040000;  // USART3 Resetlendi
//      GPIOB->AFR[1]=0x07777700;  // PB10..PB14 pinleri USART3 ile alakalandirildi (Hard Sayfa 49)
//      GPIOB->MODER|=0x2AA00000;  // GPIOB 10..14 icin alternatif fonksiyon tanimi (Rehber Sayfa 148)
//
//// USART3 MODULUNU AYARLAYALIM  // 1 Start, 8 Data, 1 Stop, No parity (Default degerler)
//
//      RCC->APB1RSTR&=~0x00040000;  // USART3 Reseti kaldiralim
////      USART3->SR&=~0X03FF;   // Status registeri silelim
//      USART3->BRR=0X1112;    // 9600 Baud
//
//      USART3->CR1|=0x0000202C;  // USART3 enable
//      NVIC->ISER[1]|=0x80;         // NVIC da USART3 interrupta izin verelim
//}
//
//void SendChar(char Tx)
//{
//      while(!(USART3->SR&0x80));  // TX Buffer dolu ise bekle (Rehber Sayfa 646)
//      USART3->DR=Tx;
//}
//
//void SendTxt(char *Adr)
//{
//      while(*Adr)
//        {
//          SendChar(*Adr);
//          Adr++;
//        }
//}
//
//char DataReady()
//{
//       return(WAdr-RAdr);
//}
//
//char ReadChar()
//{
//char Dat;
//
//      Dat=RxBuf[RAdr];
//      RAdr=(RAdr+1)&0x7F;
//      return(Dat);
//}
//
//
//void TIM7_IRQHandler()
//{
//TIM7->SR=0;
//timer_update=1;
//}
//
//// Rx ve TX pinlerini (GPIOB10 ve GPIOB11) birbirine baglarsaniz gonderdiginiz datalar geri gelecektir
//
//int main()
//{
//unsigned int ledtime;
//      UsartInit();
//      SendTxt("PicProje");
//      ADC1->CR2 |=0x40000000; // ADC çevrimini baþlattýk.
//      while(1){
//
//      	if(timer_update){
//            timer_update=0;
//            if(++ledtime > 5000){
//      			ledtime =0;
//                GPIOD->ODR ^= 0x0000008000;
//                sprintf(TxBuf,"ch0:%d ch1:%d ch2:%d ch3:%d\r",adc_val[0],adc_val[1],adc_val[2],adc_val[3]);
//                SendTxt(TxBuf);
//      		}
//        }
//      };
//}
//
//
//
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t adc_val[4];
uint8_t ch_index =0;

void GPIO_Config()
{
	RCC->AHB1ENR |= 0x00000001;

	GPIOA->MODER |= 0x00000003;
	GPIOA->OSPEEDR |= 0x00000003;
}

void ADC_Config()
{
	RCC->APB2ENR |= 0x00000100;

    ADC1->CR1 |=0x00000120; //  ADC scan modunda çalýþacak. Interrupt aktif.
	NVIC_EnableIRQ(ADC_IRQn); // NVIC ADC kesmesini aktif ettik.

    ADC1->SQR1 |= (3 << 20); // Kaç kanalý tarayacaðýmýzý bildiriyoruz. 20..23 bitler; 4 kanal
    ADC1->SQR3 |= 8; // Çevrime ilk girecek kanal 8. (PB0)
    ADC1->SQR3 |= (9 << 5); // Çevrime 2. sýrada girecek kanal 9. (PB1)
    ADC1->SQR3 |= (14 << 10); // Çevrime 3. sýrada girecek kanal 14. (PC4)
    ADC1->SQR3 |= (15 << 15); // Çevrime 4. sýrada girecek kanal 15. (PC5)
	ADC1->SMPR1 |=0xFFFFFFFF; // En düþük çevirim hýzý.
	ADC1->SMPR2 |=0xFFFFFFFF; // En düþük çevirim hýzý.
    ADC1->CR2 |=0x00000403;   // AD converter'i açtýk. Sürekli çevirim yapacaðýz.
	 						   // Her kanal çevrimi bittiðinde EOC set olacak.
}

void ADC_IRQHandler()
{
      	if(ADC1->SR & 0x0002){
           	ADC1->SR &= ~0x0002;
			adc_val[ch_index] = ADC1->DR;
			if(++ch_index > 3)ch_index=0;
        }

}

int main(void)
{
	GPIO_Config();
	ADC_Config();
  while (1)
  {

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
