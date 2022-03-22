#include <stm32f10x_conf.h>

void IIC_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
		GPIO_InitStructure.GPIO_Pin = SCL|SDA;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(IIC_PORT,&GPIO_InitStructure);
}

void IIC_SDA_Mode(u8 addr)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		if(addr)
		{
			GPIO_InitStructure.GPIO_Pin = SDA;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(IIC_PORT,&GPIO_InitStructure);
		}
		else
		{
			GPIO_InitStructure.GPIO_Pin = SDA;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_Init(IIC_PORT,&GPIO_InitStructure);
		}
}

void IIC_START(void)
{
		IIC_SDA_Mode(OUT);
		SCL_SET;
		Delay_us(5);
		SDA_CLR;
		Delay_us(5);
		SCL_CLR;
		Delay_us(5);
}

void IIC_STOP(void)
{
		IIC_SDA_Mode(OUT);
		SDA_CLR;
		Delay_us(5);
		SCL_SET;
		Delay_us(5);
		SDA_SET;
}



u8 IIC_Wait_ACK(void)
{
	u8 TimeACK;
		IIC_SDA_Mode(INPUT);
		SCL_SET;
		Delay_us(4);
		while(SDA_READ)
		{
				if(++TimeACK > 250)
				{
					IIC_STOP();
					return 1;
				}
		}
		SCL_CLR;
		Delay_us(4);
		
		return 0;
}

void IIC_SendAck(void)
{
		SDA_CLR;
		Delay_us(5);
		SCL_SET;
		Delay_us(5);
		SCL_CLR;
		SDA_SET;
		Delay_us(5);
}

void IIC_SendNoAck(void)
{
		SDA_SET;
		Delay_us(5);
		SCL_SET;
		Delay_us(5);
		SCL_CLR;
		SDA_SET;
		Delay_us(5);

}



void IIC_Write_Byte(u8 data)
{
	u8 i;
		SCL_CLR;
		Delay_us(4);
		
		for(i=0; i<8; i++)
		{
				IIC_SDA_Mode(OUT);
				if((data<<i) & 0x80) SDA_SET;
				else SDA_CLR;
			
			SCL_SET;
			Delay_us(4);
			SCL_CLR;
			Delay_us(4);		
		}	
}
	
u8 IIC_Read_Data(void)
{
		u8 Data,i;
	
		for(i=0; i<8; i++)
	{
		IIC_SDA_Mode(INPUT);
			SCL_SET;
			Delay_ms(4);	
			Data <<= 1;
			
			if(SDA_READ == 1)
			{
				Data |= 0x01;
			}
			SCL_CLR;
			Delay_ms(4);
	}
		return Data;
}










