#ifndef __DELAY_H_
#define	__DELAY_H_

#include <stm32f10x_conf.h>

static __IO uint32_t TimingDelay;

		
void Delay_Init(void);		
void Delay(__IO uint32_t nTime);

#define delay_ms(x) Delay(x*1000)
#define Delay_us(x) Delay(x)
#define Delay_ms(x) Delay(x*1000)

#endif 
