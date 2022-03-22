#include <stm32f10x_conf.h>

//SLACE_ADDRESS 设备地址
//addr 数据地址
//data 数据

void AT24C02_Write_Data(u8 addr,u8 data)
{
		IIC_START();
		IIC_Write_Byte(AT24C02);
		IIC_Wait_ACK();
		IIC_Write_Byte(addr);
		IIC_Wait_ACK();
		IIC_Write_Byte(data);
		IIC_Wait_ACK();
		IIC_STOP();
		Delay_ms(10);
}

//SLAVE_ADDRESS 设备地址
//addr 数据

u8 AT24C02_Read_Data(u8 addr)
{
		u8 dat;																
		IIC_START();													//写0  读1
		IIC_Write_Byte(AT24C02); 							//0XA1  1010 0000
		IIC_Wait_ACK();												//0X00	0000 0000	
		IIC_Write_Byte(addr);									//			1010 0000
		IIC_Wait_ACK();
		
		IIC_START();
		IIC_Write_Byte(AT24C02+1);						//0XA1  1010 0000
		IIC_Wait_ACK();                      	//0X01	0000 0001
		dat = IIC_Read_Data();               	//			1010 0001
		IIC_Wait_ACK();
		IIC_STOP();
		
		return dat;
}

//page   页号
//length 要写入多长的长度
//Data   要写入的数据
void AT24C02_PAGE_Write_Data(u8 page,u8 length,u8* Data)
{
		u8 i;
		IIC_START();
		IIC_Write_Byte(AT24C02);
		IIC_Wait_ACK();
		IIC_Write_Byte(page*16);
		IIC_Wait_ACK();
		
		for(i=0; i<length; i++)
		{
				IIC_Write_Byte(Data[i]);
				IIC_Wait_ACK();
		}
		IIC_STOP();
		Delay_ms(10);
}


//page 		页号
//length 	长度
//Data 		数据
void AT24C02_PAGE_Read_Data(u16 page,u8 length,u8 *Data)
{
		u8 t;

	for(t=0;t<length;t++)
	{
		*Data++=AT24C02_Read_Data(page+t);
	}						

}




