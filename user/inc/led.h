#ifndef _LED_H_
#define _LED_H_

#include <stm32f10x_conf.h>


#define LED GPIO_Pin_3
#define LED_PORT GPIOB

#define LED1 GPIO_Pin_1
#define LED1_PORT GPIOB

#define Realy GPIO_Pin_15
#define REALY_PORT GPIOA


void Led_Init(void);
//void TIM6_LED(u16 period,u16 prescaler);
//void TIM7_LED(u16 period,u16 prescaler);
#endif
