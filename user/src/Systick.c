#include "Systick.h"

void Systick_Init(uint32_t ClkSource,uint32_t TickInt,uint32_t Enable)
{	
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk|SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk);
	
    if(ClkSource)
		{SysTick->CTRL |=  SysTick_CTRL_CLKSOURCE_Msk;}
    else
    {SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;}
    if(TickInt)
    {SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk;}
    else
    {SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;}
    if(Enable)
    {SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;}
    else
    {SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;}
}

void Systick_TickInit(uint32_t Enable)
{
    if(Enable)
		{SysTick->CTRL |= (uint32_t)SysTick_CTRL_ENABLE_Msk;}
    else
    {SysTick->CTRL &= ~(uint32_t)SysTick_CTRL_ENABLE_Msk;}
}

void Systick_Load_Value(uint32_t num)
{
		SysTick->LOAD = num;
}

uint32_t Systick_GetValue(void)
{
	return (uint32_t)(SysTick->VAL);
}



