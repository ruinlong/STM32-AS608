#include "myiic.h"



#define   SCL_PIN    GPIO_Pin_11
#define   SDA_PIN    GPIO_Pin_12
#define   IIC_IO	 GPIOA

#define  IIC_SDA_1_() 	GPIO_SetBits(IIC_IO, SDA_PIN)
#define  IIC_SDA_0_() 	GPIO_ResetBits(IIC_IO, SDA_PIN)
#define  IIC_SCL_1_() 	GPIO_SetBits(IIC_IO, SCL_PIN)
#define  IIC_SCL_0_() 	GPIO_ResetBits(IIC_IO, SCL_PIN)
#define  IIC_SDA_IN_() 	GPIO_ReadInputDataBit(IIC_IO, SDA_PIN)   




void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//初始化外设GPIOx寄存器
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高输出速率50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//推挽输出
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//初始化外设GPIOx寄存器
}  

void IIC_Init(void)
{	
//	RCC->APB2ENR|=1<<3;//先使能外设IO PORTC时钟
 				     
//	GPIOB->CRL&=0X00FFFFFF;//PB6,7 推挽输出
//	GPIOB->CRL|=0X33000000;	   
//	GPIOB->ODR|=3<<6;     //PB6,7 输出高

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SCL_PIN | SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高输出速率50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//开漏输出
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//初始化外设GPIOx寄存器

	IIC_Stop();
}

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_1_();IIC_SCL_1_();Delay_us(5);
 	IIC_SDA_0_();Delay_us(5);
	IIC_SCL_0_();//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_0_();
	IIC_SDA_0_();Delay_us(5);//STOP:when CLK is high DATA change form low to high
 	IIC_SCL_1_();Delay_us(5); 
	IIC_SDA_1_();Delay_us(5);//发送I2C总线结束信号
	IIC_SCL_0_(); 								   	
}

void I2Cinit(void)
{
	IIC_SCL_0_();
	IIC_Stop();
}

u8 I2CClock(void)
{
	u8 bt;
	SDA_IN();
	IIC_SCL_1_();Delay_us(2);  	
	bt = IIC_SDA_IN_();
	IIC_SCL_0_();
	return(bt);
}


//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA_1_(); Delay_us(1);	   
	IIC_SCL_1_(); Delay_us(1);	 
	while(IIC_SDA_IN_())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_0_();//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	SDA_OUT();
	IIC_SCL_0_(); 
	IIC_SDA_0_();Delay_us(2);
	IIC_SCL_1_();Delay_us(2);
	IIC_SCL_0_();
	IIC_SDA_1_();
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	SDA_OUT();
	IIC_SCL_0_();

	IIC_SDA_1_();Delay_us(2);
	IIC_SCL_1_();Delay_us(2);
	IIC_SCL_0_(); 
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET)	  
u8 IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_0_();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {    
		if(txd&0x80)  IIC_SDA_1_();
		else  IIC_SDA_0_();	 
        txd<<=1; 	  
		Delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_1_(); 	Delay_us(2);
		IIC_SCL_0_();	Delay_us(2);
    }
	IIC_SDA_1_();
	return(~I2CClock());	 
}
    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_0_(); 
        Delay_us(2);
		IIC_SCL_1_();
        receive<<=1;
        if(IIC_SDA_IN_())receive++;   
		Delay_us(1); 
    }					 
    if (ack)
        IIC_Ack(); //发送ACK  
    else
		IIC_NAck();//发送nACK
         
    return receive;
}

#define IICWRITE 0xa0
#define IICREAD 0xa1 

u8 TX_address(u8 addr)
{
	IIC_Start();
	if(IIC_Send_Byte(IICWRITE))
		return(IIC_Send_Byte(addr));
	else
		return(0); 
}


























