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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//��ʼ������GPIOx�Ĵ���
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����������50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//�������
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//��ʼ������GPIOx�Ĵ���
}  

void IIC_Init(void)
{	
//	RCC->APB2ENR|=1<<3;//��ʹ������IO PORTCʱ��
 				     
//	GPIOB->CRL&=0X00FFFFFF;//PB6,7 �������
//	GPIOB->CRL|=0X33000000;	   
//	GPIOB->ODR|=3<<6;     //PB6,7 �����

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SCL_PIN | SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����������50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��©���
	GPIO_Init(IIC_IO, &GPIO_InitStructure);//��ʼ������GPIOx�Ĵ���

	IIC_Stop();
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_1_();IIC_SCL_1_();Delay_us(5);
 	IIC_SDA_0_();Delay_us(5);
	IIC_SCL_0_();//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_0_();
	IIC_SDA_0_();Delay_us(5);//STOP:when CLK is high DATA change form low to high
 	IIC_SCL_1_();Delay_us(5); 
	IIC_SDA_1_();Delay_us(5);//����I2C���߽����ź�
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


//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL_0_();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	SDA_OUT();
	IIC_SCL_0_(); 
	IIC_SDA_0_();Delay_us(2);
	IIC_SCL_1_();Delay_us(2);
	IIC_SCL_0_();
	IIC_SDA_1_();
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	SDA_OUT();
	IIC_SCL_0_();

	IIC_SDA_1_();Delay_us(2);
	IIC_SCL_1_();Delay_us(2);
	IIC_SCL_0_(); 
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET)	  
u8 IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_0_();//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {    
		if(txd&0x80)  IIC_SDA_1_();
		else  IIC_SDA_0_();	 
        txd<<=1; 	  
		Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_1_(); 	Delay_us(2);
		IIC_SCL_0_();	Delay_us(2);
    }
	IIC_SDA_1_();
	return(~I2CClock());	 
}
    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_Ack(); //����ACK  
    else
		IIC_NAck();//����nACK
         
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


























