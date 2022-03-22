#ifndef __LCD12864_H
#define __LCD12864_H			


#include <stm32f10x_conf.h>
	
	

#define RS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define RS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define RW_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define RW_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define EN_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define EN_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_7)

//PA0~7,作为数据线
#define DATAOUT(x)  GPIO_Write(GPIOA,x)//输出  
#define DATAIN      GPIO_ReadInputData(GPIOA)//输入


void LCD12864_GPIO_Init(void);
void LCD_Init(void);
void Write_Word(u8 dat);
void LCD12864_SetWindow(u8 x, u8 y);
void WriteString(u8* stringPoint,u8 row,u8 column);

#endif  
	 



