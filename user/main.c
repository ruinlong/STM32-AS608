#include <stm32f10x_conf.h>
uint8_t Press_Key = 0;
uint16_t ValidN;
unsigned char  Mode_State=0; 

int main(void)
{		
		Delay_Init();
  	usart1_init(57600);
		LCD12864_GPIO_Init();
		LCD_Init();
		Key_GPIO_Init();
		Led_Init();
		IIC_Init();
		PS_StaGPIO_Init();

		
			while (PS_HandShake(&AS608Addr))						//与AS608模块握手
	{
		WriteString((u8 *)"尝试连接模块",0,0);
		Press_Key++;
		if (Press_Key >= 15)
		{
			WriteString((u8 *)"初始化失败",1,0); //显示初始化失败
			while (1)												 //死循环
				;
		}
	}
	
		display_Init();
	
	while(1)
	{
		if(Mode_State == 0)
		{
		press_FR();		
		}
		
		Key_back=Key_scanf();
	
			if(FLAG == 1)
		{	
			switch(state)
			{
			case 0:
				Mode_State = 0;
				UserLock_scanf();						
				admin_index();
			break;
			case 1:
				Mode_State = 1;
				AdminLock_Scanf();	
			break;
			
			case 2:
				Mode_State = 1;
				Manger_Display();
			break;
			
			case 3:	
				Mode_State = 1;				
				State_Three();			
			break;
			
			case 4:
					Mode_State = 1;
					chaek_Two_Passwd();
			break;
			
			case 99:
					Mode_State = 1;
					admin_index();					
		 	break;
			
			}			
		}	
	}	
}
