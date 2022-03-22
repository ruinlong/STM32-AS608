#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 


#define KEY1 PBin(8)
#define KEY2 PBin(12) 
#define KEY3 PBin(13)
#define KEY4 PBin(14)
#define KEY5 PBin(15)

#define KEY1_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY1_PORT			 GPIOB
#define KEY1_PORT_PIN  GPIO_Pin_8

#define KEY2_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY2_PORT			 GPIOB
#define KEY2_PORT_PIN  GPIO_Pin_12

#define KEY3_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY3_PORT			 GPIOB
#define KEY3_PORT_PIN  GPIO_Pin_13

#define KEY4_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY4_PORT			 GPIOB
#define KEY4_PORT_PIN  GPIO_Pin_14

#define KEY5_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY5_PORT			 GPIOB
#define KEY5_PORT_PIN  GPIO_Pin_15

extern u8 key_num;

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);//按键扫描函数					    
#endif
