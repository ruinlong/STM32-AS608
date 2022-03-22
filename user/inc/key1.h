#ifndef _KEY1_H_
#define _KEY1_H_

#include <stm32f10x_conf.h>

#define KEY_PORT GPIOB

#define HANG 0XF000

#define Key1 GPIO_Pin_11
#define Key2 GPIO_Pin_10
#define Key3 GPIO_Pin_9
#define Key4 GPIO_Pin_8

#define Key1_Input GPIO_ReadInputDataBit(KEY_PORT,Key1)
#define Key2_Input GPIO_ReadInputDataBit(KEY_PORT,Key2)
#define Key3_Input GPIO_ReadInputDataBit(KEY_PORT,Key3)
#define Key4_Input GPIO_ReadInputDataBit(KEY_PORT,Key4)
extern u8 FLAG;
void Key_GPIO_Init(void);
u8 Key_scanf(void);


#endif

