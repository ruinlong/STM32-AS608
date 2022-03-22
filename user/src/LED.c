#include <stm32f10x_conf.h>

void Led_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure1;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin = LED;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(LED_PORT,&GPIO_InitStructure);
	
		GPIO_InitStructure1.GPIO_Pin = LED1;
		GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(LED1_PORT,&GPIO_InitStructure1);
		
		GPIO_InitStructure1.GPIO_Pin = Realy;
		GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(REALY_PORT,&GPIO_InitStructure1);
	
		GPIO_ResetBits(REALY_PORT,Realy);
		GPIO_ResetBits(LED_PORT,LED);
		GPIO_ResetBits(LED1_PORT,LED1);
}

void TIM6_LED(u16 period,u16 prescaler)
{
	TIM_TimeBaseInitTypeDef TIM6_TimeBaseInitstructure;
	NVIC_InitTypeDef NVIC_Initstructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM6EN,ENABLE);
	
	TIM6_TimeBaseInitstructure.TIM_Period = period;
	TIM6_TimeBaseInitstructure.TIM_Prescaler = prescaler;
	TIM6_TimeBaseInitstructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM6_TimeBaseInitstructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM6_TimeBaseInitstructure.TIM_RepetitionCounter = DISABLE;
	
	TIM_TimeBaseInit(TIM6,&TIM6_TimeBaseInitstructure);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_Initstructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Initstructure);
}

//void TIM7_LED(u16 period,u16 prescaler)
//{
//	TIM_TimeBaseInitTypeDef TIM7_TimeBaseInitstructure;
//	NVIC_InitTypeDef NVIC_Initstructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7EN,ENABLE);
//	
//	TIM7_TimeBaseInitstructure.TIM_Period = period;
//	TIM7_TimeBaseInitstructure.TIM_Prescaler = prescaler;
//	TIM7_TimeBaseInitstructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM7_TimeBaseInitstructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM7_TimeBaseInitstructure.TIM_RepetitionCounter = DISABLE;
//	
//	TIM_TimeBaseInit(TIM7,&TIM7_TimeBaseInitstructure);
//	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
//	TIM_Cmd(TIM7,ENABLE);
//	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_Initstructure.NVIC_IRQChannel = TIM7_IRQn;
//	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_Initstructure);
//}


//void TIM6_IRQHandler(void)
//{
//		GPIO_WriteBit(LED_PORT,LED,(BitAction)(!GPIO_ReadOutputDataBit(LED_PORT,LED)));
//		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
//	
//}


//void TIM7_IRQHandler(void)
//{
//		GPIO_WriteBit(LED1_PORT,LED1,(BitAction)(!GPIO_ReadOutputDataBit(LED1_PORT,LED1)));
//		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
//	
//}









