#include <stm32f10x_conf.h>

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void Delay_Init(void)
{
	 if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    while (1);
  }
	
}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}






