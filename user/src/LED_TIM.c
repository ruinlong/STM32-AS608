#include <stm32f10x_conf.h>


void LED_TIM_INIT(u16 Period,u16 Prescaler)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
		TIM_TimeBaseStructure.TIM_Period = Period;
		TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM1,ENABLE);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void TIM1_UP_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		Lock_scanf();
}

	



