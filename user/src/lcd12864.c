#include <stm32f10x_conf.h>


void LCD12864_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	
}

/*向12864写入命令*/
void WriteOrder(u8 order)  
{
		RS_Clr();
		RW_Clr();
		Delay_us(5);
		EN_Set();
		DATAOUT(order);
		Delay_us(5);
		EN_Clr();
	
}

/*向12864写入数据*/
void WriteData(u8 dat)		
{
		RS_Set();
		RW_Clr();
		Delay_us(5);
		EN_Set();
		DATAOUT(dat);
		Delay_us(5);
		EN_Clr();
}

void LCD12864_CheckBusy(void)
{
	u8 i = 250;	//局部变量
	RS_Clr();
	RW_Set();
	EN_Set();	  			//使能
	while((i > 0) && (DATAIN & 0x80))i--;  //判断忙标志位
	EN_Clr();	  			//释放
}

unsigned char GetDDRAM(u8 row,u8 column)	
{
	u8 result =0x80;
	switch(row)
	{
		case 0:
			result=0x80+column;
		break;
		
		case 1:
			result=0x90+column;
		break;
		
		case 2:
			result=0x88+column;
		break;
		
		case 3:
			result=0x98+column;
		break;
	}
	return result;
}

void LCD12864_SetWindow(u8 x, u8 y)	
{
	u8 pos;
	if(x == 0)	   // 第一行的地址是80H
	{
		x = 0x80;
	}
	else if(x == 1)  //第二行的地址是90H
	{
		x = 0x90;	
	}
	else if(x == 2)  //第三行的地址是88H
	{
		x = 0x88;
	}
	else if(x == 3)
	{
		x = 0x98;
	}
	
	pos = x + y;
	WriteOrder(pos);
}

void Write_Word(u8 dat)				
{
	LCD12864_CheckBusy();
	RS_Set();
	RW_Clr();
	EN_Clr();
	DATAOUT(dat);
	EN_Set();
	Delay_ms(5);
	EN_Clr();
	
}


void WriteString(u8* stringPoint,u8 row,u8 column)  
{
	u8 order;
	order = GetDDRAM(row,column);
	LCD12864_CheckBusy();
	WriteOrder(order);
	while(*stringPoint !=0)
	{
		LCD12864_CheckBusy();
		WriteData(*stringPoint);
		stringPoint++;
	}	
}

/*初始化*/
void LCD_Init()
{
	EN_Clr();
	Delay_ms(5);
	WriteOrder(0x30);
	Delay_ms(5);
	WriteOrder(0x30);
	Delay_ms(5);
	WriteOrder(0x0c);
	Delay_ms(5);
	WriteOrder(0X01);
	Delay_ms(15);
	WriteOrder(0x06);
	Delay_ms(5);	
}

