#ifndef _IIC_H_
#define _IIC_H_

#include <stm32f10x_conf.h>

#define SCL GPIO_Pin_11
#define SDA GPIO_Pin_12

#define IIC_PORT GPIOA

#define OUT 1
#define INPUT 0

#define SDA_CLR GPIO_ResetBits(IIC_PORT,SDA)
#define SDA_SET GPIO_SetBits(IIC_PORT,SDA)
#define SCL_CLR GPIO_ResetBits(IIC_PORT,SCL)
#define SCL_SET GPIO_SetBits(IIC_PORT,SCL)

#define SDA_READ GPIO_ReadInputDataBit(IIC_PORT,SDA)



void IIC_Init(void);
void IIC_START(void);
void IIC_STOP(void);
void IIC_SendAck(void);
void IIC_SendNoAck(void);
u8 IIC_Wait_ACK(void);
void IIC_Write_Byte(u8 data);
u8 IIC_Read_Data(void);


#endif





