#include "stm32f4xx.h"

volatile uint32_t Delay_ms;
void SysTick_Handler(void)
{
	Delay_ms++;
}

static void Delay(__IO uint32_t bekle)
{
  uint32_t t= Delay_ms;
  while ((Delay_ms - t) < bekle);
}

void Bekleme(void)
{
	if (SysTick_Config(SystemCoreClock / 1000)) //1ms bekleme
	{
		while (1);
	}
}

int main()
{
	Bekleme();
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);


	TIM_TimeBaseStructure.TIM_Period=19999; //arr degeri
	TIM_TimeBaseStructure.TIM_Prescaler=84;//PrescalerValue; 84
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //0 'dan 20 bine kadar sayar Count 0 -> CNT
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	TIM_Cmd(TIM4,ENABLE);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //Output compare or Output control mode Set pulse when CNT==CCRx
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;

	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; // Active High, i.e 0 -> 1 starts duty cycle

	while(1)
	{
		for(int i=0;i<2201;i++)
		{
			TIM_OCInitStructure.TIM_Pulse=i;//CCR1_Val; Initial duty cycle
			TIM_OC1Init(TIM4,&TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
			TIM_OCInitStructure.TIM_Pulse=i;//CCR2_Val; Initial duty cycle
			TIM_OC2Init(TIM4,&TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
			Delay(1);
		}
		for(int i=2200;i>0;i--)
		{
			TIM_OCInitStructure.TIM_Pulse=i;//CCR1_Val; Initial duty cycle
			TIM_OC1Init(TIM4,&TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
			TIM_OCInitStructure.TIM_Pulse=i;//CCR2_Val; Initial duty cycle
			TIM_OC2Init(TIM4,&TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
			Delay(1);
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
