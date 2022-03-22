#include <stm32f10x_conf.h>


u8 FLAG;
u8 key_back;

void Key_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initstructure;
		GPIO_Initstructure.GPIO_Pin = HANG;
		GPIO_Initstructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
		GPIO_Init(KEY_PORT,&GPIO_Initstructure);
		GPIO_SetBits(KEY_PORT,HANG);
	
		GPIO_Initstructure.GPIO_Pin = Key1|Key2|Key3|Key4;
		GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(KEY_PORT,&GPIO_Initstructure);
		GPIO_SetBits(KEY_PORT,Key1|Key2|Key3|Key4);
}
	

u8 Key_scanf(void)
{
		GPIO_Write(KEY_PORT,0X7F00);
		if((Key1_Input==RESET)||(Key2_Input==RESET)||(Key3_Input==RESET)||(Key4_Input==RESET))
		{
				Delay_ms(15);
				if(Key1_Input==RESET)
				{			
						Delay_ms(15);
						if(Key1_Input==RESET)
					{		
						key_back = 1;
						FLAG = 1;
					while(!Key1_Input); 
					}
				}
				
				else if(Key2_Input==RESET)
				{				
						Delay_ms(15);
						if(Key2_Input==RESET)
					{						
						key_back = 2;
						FLAG = 1;
					while(!Key2_Input); 
					}
				}
				
				else if(Key3_Input==RESET)
				{			
						Delay_ms(15);
						if(Key3_Input==RESET)
					{							
						key_back = 3;
						FLAG = 1;
					while(!Key3_Input); 
					}
				}
				
				else if(Key4_Input==RESET)
				{				
						Delay_ms(15);
						if(Key4_Input==RESET)
					{							
						key_back = 10;
						FLAG = 1;
					while(!Key4_Input); 
					}
				}
				
				else{
							FLAG = 0;
							GPIO_Write(KEY_PORT,0XFF00);
						}	
		}
		
		
		GPIO_Write(KEY_PORT,0XBF00);
		if((Key1_Input==RESET)||(Key2_Input==RESET)||(Key3_Input==RESET)||(Key4_Input==RESET))
		{
				Delay_ms(15);
				if(Key1_Input==RESET)
				{				
						Delay_ms(15);
						if(Key1_Input==RESET)
					{							
						key_back = 4;
						FLAG = 1;
					while(!Key1_Input); 
					}
				}
				
				else if(Key2_Input==RESET)
				{			
						Delay_ms(15);
						if(Key2_Input==RESET)
					{							
						key_back = 5;
						FLAG = 1;
					while(!Key2_Input); 
					}
				}
				
					else if(Key3_Input==RESET)
				{			
						Delay_ms(15);					
						if(Key3_Input==RESET)
					{						
						key_back = 6;
						FLAG = 1;
					while(!Key3_Input); 
					}
				}
				
				else if(Key4_Input==RESET)
				{		
						Delay_ms(15);					
						if(Key4_Input==RESET)
					{					
						key_back = 11;
						FLAG = 1;
					while(!Key4_Input); 
					}
				}
				
				else{
							FLAG = 0;
							GPIO_Write(KEY_PORT,0XFF00);
						}	
		}
		

		
		GPIO_Write(KEY_PORT,0XDF00);
		if((Key1_Input==RESET)||(Key2_Input==RESET)||(Key3_Input==RESET)||(Key4_Input==RESET))
		{
				Delay_ms(15);
				if(Key1_Input==RESET)
				{			
						Delay_ms(15);
						if(Key1_Input==RESET)
					{							
						key_back = 7;
						FLAG = 1;
					while(!Key1_Input); 
					}
				}
				
				else if(Key2_Input==RESET)
				{				
						Delay_ms(15);
						if(Key2_Input==RESET)
					{							
						key_back = 8;
						FLAG = 1;
					while(!Key2_Input); 
					}
				}
				
				else if(Key3_Input==RESET)
				{			
						Delay_ms(15);
						if(Key3_Input==RESET)
					{							
						key_back = 9;
						FLAG = 1;
					while(!Key3_Input); 
					}
				}
				
				else if(Key4_Input==RESET)
				{			
						Delay_ms(15);					
						if(Key4_Input==RESET)
					{							
						key_back = 12;
						FLAG = 1;
					while(!Key4_Input); 
					}
				}
				else{
							FLAG = 0;
							GPIO_Write(KEY_PORT,0XFF00);
						}	
		}
		
		
		GPIO_Write(KEY_PORT,0XEF00);
		if((Key1_Input==RESET)||(Key2_Input==RESET)||(Key3_Input==RESET)||(Key4_Input==RESET))
		{
				Delay_ms(15);
				if(Key1_Input==RESET)
				{			
						Delay_ms(15);					
						if(Key1_Input==RESET)
					{						
						key_back = 13;
						FLAG = 1;
					while(!Key1_Input); 
					}
				}
				
				else if(Key2_Input==RESET)
				{				
						Delay_ms(15);
						if(Key2_Input==RESET)
					{							
						key_back = 0;
						FLAG = 1;
					while(!Key2_Input); 
					}
				}
					
				else if(Key3_Input==RESET)
				{			
						Delay_ms(15);					
						if(Key3_Input==RESET)
					{						
						key_back = 14;
						FLAG = 1;
					while(!Key3_Input); 
					}
				}
				
				else if(Key4_Input==RESET)
				{				
						Delay_ms(15);				
						if(Key4_Input==RESET)
					{		
						key_back = 15;
						FLAG = 1;
					while(!Key4_Input); 
					}
				}
				else{
						FLAG = 0;
						GPIO_Write(KEY_PORT,0XFF00);
						}	
					}

	return key_back;
}










