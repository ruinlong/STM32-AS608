#include <stm32f10x_conf.h>

u8 Key_back;
u8 Key_Count;
u8 state;
u8 Password_Input[7] = {0,0,0,0,0,0,0};
u8 Password_Verify[7] = {0,4,3,9,9,5,8};
u8 i;
u8 admin_key_count=0;
u8 Admin_Password_Input[7] = {0,0,0,0,0,0,0};
u8 Admin_Password_Verify[7] = {0,1,2,3,4,5,6};

u8 Password_EEPR0M[7] = {0,0,0,0,0,0,0};
u8 Password_TWO_EEPR0M[7] = {0,0,0,0,0,0,0};

u8 guangbiao = 0;
extern unsigned char  Mode_State; 

u8 KeyValue;							//0-9获取密码的值
u8 error;

void display_Init(void)
{
				WriteString((u8 *)"STM32 指纹密码锁",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);

}

void Scanf_Input(u8* pss)
	{	
switch(Key_Count)
			{
				case 1:
				pss[1] = KeyValue;
				LCD12864_SetWindow(2,1);
		    Write_Word( pss[1]%10+0x30);
				Delay_ms(100);
				WriteString((u8 *)"  *             ",2,0);				
			  break;		 
			
				case 2:
				pss[2] = KeyValue;
				LCD12864_SetWindow(2,2);
		    Write_Word( pss[2]%10+0x30);
				Delay_ms(100);
				WriteString((u8 *)"  * *           ",2,0);	
				break;
			
				case 3:
				pss[3] = KeyValue;
				LCD12864_SetWindow(2,3);
				Write_Word(pss[3]%10+0x30);
				Delay_ms(100);
				WriteString((u8 *)"  * * *         ",2,0);					
				break;
			
				case 4:	

				pss[4] = KeyValue;
				LCD12864_SetWindow(2,4);
		    Write_Word(pss[4]%10+0x30);
				Delay_ms(100);
			  WriteString((u8 *)"  * * * *     ",2,0);						
				break;
			
				case 5:			

				pss[5] = KeyValue;
				LCD12864_SetWindow(2,5);
				Write_Word(pss[5]%10+0x30);
				Delay_ms(100);
				WriteString((u8 *)"  * * * * *     ",2,0);								
				break;			
			
				case 6:
				pss[6] = KeyValue;
				LCD12864_SetWindow(2,6);
		    Write_Word(pss[6]%10+0x30);
				Delay_ms(100);
				WriteString((u8 *)"  * * * * * *   ",2,0);							
				break;
				default: if(Key_Count>=6)	WriteString((u8 *)"  * * * * * *   ",2,0); break;
	   	}
}
	


void UserLock_scanf(void)
{
			GPIO_SetBits(LED_PORT,LED);
			//printf("按键值:%d\r\n",Key_back);		
			Delay_ms(10);
			FLAG = 0;
			
			if(Key_back<=9)				//如果输入值小于9
			{
			Key_Count++;
			KeyValue=Key_scanf();
			}
		Scanf_Input(Password_Input);
		
			
						if(Key_back == 10)		//重置密码
			{		
				Key_Count = 0;												
				display_Init();			
				Password_Input[0] = 0;Password_Input[1] = 0;Password_Input[2] = 0;Password_Input[3] = 0;
				Password_Input[4] = 0;Password_Input[5] = 0;Password_Input[6] = 0;				
			}	
			
			if(Key_back == 15)
			{			
			Password_Verify[0]=AT24C02_Read_Data(0x01);
			Password_Verify[1]=AT24C02_Read_Data(0x02);
			Password_Verify[2]=AT24C02_Read_Data(0x03);
			Password_Verify[3]=AT24C02_Read_Data(0x04);
			Password_Verify[4]=AT24C02_Read_Data(0x05);
			Password_Verify[5]=AT24C02_Read_Data(0x06);
			Password_Verify[6]=AT24C02_Read_Data(0x07);

				
					 Key_Count = 0;	
					Password_Verify[0]=0;			
					if(Password_Input[1] == Password_Verify[1] && Password_Input[2] == Password_Verify[2] && Password_Input[3] == Password_Verify[3] &&
						 Password_Input[4] == Password_Verify[4] && Password_Input[5] == Password_Verify[5] && Password_Input[6] == Password_Verify[6])
					{
						error = 0;
					WriteString((u8 *)"                ",0,0);Delay_ms(1);
					WriteString((u8 *)"    开锁成功    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"                ",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);	
						
				Password_Input[0] = 0;Password_Input[1] = 0;Password_Input[2] = 0;Password_Input[3] = 0;
				Password_Input[4] = 0;Password_Input[5] = 0;Password_Input[6] = 0;		

					GPIO_ResetBits(LED_PORT,LED);
					GPIO_SetBits(REALY_PORT,Realy);
					Delay_ms(3000);
					GPIO_ResetBits(REALY_PORT,Realy);	
					display_Init();		 
					}
					else
					{
					error++;
						if(error == 1)
						{
					WriteString((u8 *)"    密码错误    ",0,0);Delay_ms(1);
					WriteString((u8 *)"  请重新尝试！  ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"您还有两次机会！",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);
					GPIO_ResetBits(LED_PORT,LED);
					Delay_ms(2000);
					display_Init();	
							
							
						}
						else if(error == 2)
						{	
					WriteString((u8 *)"    密码错误    ",0,0);Delay_ms(1);
					WriteString((u8 *)"  请重新尝试！  ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"您还有一次机会！",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);	
					GPIO_ResetBits(LED_PORT,LED);
					Delay_ms(2000);
					display_Init();								
						}
						else
						{
					WriteString((u8 *)"您已输入错误三次",0,0);Delay_ms(1);
					WriteString((u8 *)"你的密码已经冻结",1,0);Delay_ms(1);
			  	WriteString((u8 *)"请输入管理员密码",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);						
						state = 99;	  
						}
					}
		}
			
}


void admin_index(void)				//按5次按键进入管理员模式
{
	FLAG = 0;
	if(Key_back == 11)
	{		
	admin_key_count++;
		if(admin_key_count >= 5)
		{
			admin_key_count=0;
			Key_Count=0;
			state = 1;
		}	
	}		
}

void Clear_LCD12864(void)
{
				WriteString((u8 *)"                ",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);
}

void AdminLock_Scanf(void)
{
		
			GPIO_SetBits(LED_PORT,LED);
			//printf("按键值:%d\r\n",Key_back);		
			Delay_ms(6);
			FLAG = 0;
			error =0;
	
				WriteString((u8 *)"请输入管理员密码",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);
					
			if(Key_back<=9)				//如果输入值小于9
			{
			Key_Count++;
			KeyValue=Key_scanf();
			}
		
			Scanf_Input(Admin_Password_Input);
			
			
			if(Key_back == 15)
			{			
					Key_Count = 0;	
					Password_Verify[0]=0;			
					if(Admin_Password_Input[1] == Admin_Password_Verify[1] && Admin_Password_Input[2] == Admin_Password_Verify[2] && Admin_Password_Input[3] == Admin_Password_Verify[3] &&
						 Admin_Password_Input[4] == Admin_Password_Verify[4] && Admin_Password_Input[5] == Admin_Password_Verify[5] && Admin_Password_Input[6] == Admin_Password_Verify[6])
					{
						state = 0;
					WriteString((u8 *)"                ",0,0);Delay_ms(1);
					WriteString((u8 *)"    密码正确    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"                ",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);	
						
				Admin_Password_Input[0] = 0;Admin_Password_Input[1] = 0;Admin_Password_Input[2] = 0;Admin_Password_Input[3] = 0;
				Admin_Password_Input[4] = 0;Admin_Password_Input[5] = 0;Admin_Password_Input[6] = 0;		

					GPIO_ResetBits(LED_PORT,LED);
					Delay_ms(3000);
				
						
					WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
					WriteString((u8 *)">   修改密码    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"    录入指纹    ",2,0);Delay_ms(1);
					WriteString((u8 *)"    删除指纹    ",3,0);Delay_ms(1);
						
						state = 2;
					}
					else
					{
					WriteString((u8 *)"                ",0,0);Delay_ms(1);
					WriteString((u8 *)"    密码错误    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"                ",2,0);Delay_ms(1);
					WriteString((u8 *)"                ",3,0);Delay_ms(1);	
					GPIO_ResetBits(LED_PORT,LED);							
					delay_ms(1000);
					GPIO_ResetBits(LED_PORT,LED);		
					display_Init();
					  state = 0;
						
					}
		}
			
			if(Key_back == 10)		//重置密码
			{		
				Key_Count = 0;												
				WriteString((u8 *)"请输入管理员密码",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);	
				Admin_Password_Input[0] = 0;Admin_Password_Input[1] = 0;Admin_Password_Input[2] = 0;Admin_Password_Input[3] = 0;
				Admin_Password_Input[4] = 0;Admin_Password_Input[5] = 0;Admin_Password_Input[6] = 0;					
			}	

}

void Manger_Display(void)
{					
					FLAG = 0;
					WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
					WriteString((u8 *)">   修改密码    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"    录入指纹    ",2,0);Delay_ms(1);
					WriteString((u8 *)"    删除指纹    ",3,0);Delay_ms(1);

					GPIO_SetBits(LED_PORT,LED);
					Delay_ms(10);
					if(Key_back<=9)				//如果输入值小于9
					{
						Key_Count++;
						KeyValue=Key_scanf();
					}
		
	
					if(Key_back == 12)
					{
						guangbiao++;
						if(guangbiao >= 3)
						{
							guangbiao = 0;
						}
					}
	
			
					if(guangbiao == 0)
					{
					WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
					WriteString((u8 *)">   修改密码    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"    录入指纹    ",2,0);Delay_ms(1);
					WriteString((u8 *)"    删除指纹    ",3,0);Delay_ms(1);
							if(Key_back == 15)
							{
									WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(1);
									WriteString((u8 *)"                ",1,0);Delay_ms(1);
									WriteString((u8 *)"                ",2,0);Delay_ms(1);
									WriteString((u8 *)"                ",3,0);Delay_ms(1);
									state = 3;
							}		
						if(Key_back == 10)
							{
								display_Init();
								Mode_State=0;
								state = 0;					
							}							
					}																
					
								
								
					else if(guangbiao == 1)
					{
					WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
					WriteString((u8 *)"    修改密码    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)">   录入指纹    ",2,0);Delay_ms(1);
					WriteString((u8 *)"    删除指纹    ",3,0);Delay_ms(1);		
						if(Key_back == 15)
							{
										WriteString((u8 *)"                ",0,0);Delay_ms(1);
										WriteString((u8 *)"录入指纹        ",1,0);Delay_ms(1);
										WriteString((u8 *)"                ",2,0);Delay_ms(1);
										WriteString((u8 *)"                ",3,0);Delay_ms(1);
										Add_FR();									
							}		
						if(Key_back == 10)
					{
						display_Init(); 
						Mode_State = 0;
						state = 0;					
					}
						
					}
					else if(guangbiao == 2)
					{
					WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
					WriteString((u8 *)"    修改密码    ",1,0);Delay_ms(1);
			  	WriteString((u8 *)"    录入指纹    ",2,0);Delay_ms(1);
					WriteString((u8 *)">   删除指纹    ",3,0);Delay_ms(1);
						
						if(Key_back == 15)
						{
							WriteString((u8 *)"删除指纹        ",0,0);Delay_ms(1);
							WriteString((u8 *)"                ",1,0);Delay_ms(1);
							WriteString((u8 *)"                ",2,0);Delay_ms(1);
							WriteString((u8 *)"                ",3,0);Delay_ms(1);
							Del_FR();										
						}
									if(Key_back == 10)
					{
						
						display_Init();	
						Mode_State=0;		
						state = 0;
					}
				
					}
	
}



void State_Three(void)
{	
	GPIO_SetBits(LED_PORT,LED);
			
			Delay_ms(6);
			FLAG = 0;
				
				WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);
					
			if(Key_back<=9)				//如果输入值小于9
			{
			Key_Count++;
			KeyValue=Key_scanf();
			}
		
			Scanf_Input(Password_EEPR0M);
			
			
			if(Key_back == 10)		//重置密码
			{		
				Key_Count = 0;												
				WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(1);
				WriteString((u8 *)"                ",1,0);Delay_ms(1);
				WriteString((u8 *)"                ",2,0);Delay_ms(1);
				WriteString((u8 *)"                ",3,0);Delay_ms(1);	
				Password_EEPR0M[0] = 0;Password_EEPR0M[1] = 0;Password_EEPR0M[2] = 0;Password_EEPR0M[3] = 0;
				Password_EEPR0M[4] = 0;Password_EEPR0M[5] = 0;Password_EEPR0M[6] = 0;					
			}	
			
			if(Key_back == 15)
			{
					WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(2);
					WriteString((u8 *)"                ",1,0);Delay_ms(2);
			  	WriteString((u8 *)"                ",2,0);Delay_ms(2);
					WriteString((u8 *)"                ",3,0);Delay_ms(2);		
					Key_Count = 0;
					state = 4;	
			}		
		}		
	

void chaek_Two_Passwd(void)
{
			GPIO_SetBits(LED_PORT,LED);	
			Delay_ms(6);
			FLAG = 0;

					
				WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(2);
				WriteString((u8 *)"                ",1,0);Delay_ms(2);
			  WriteString((u8 *)"                ",2,0);Delay_ms(2);
				WriteString((u8 *)"                ",3,0);Delay_ms(2);

					
			if(Key_back<=9)				//如果输入值小于9
			{
			Key_Count++;
			KeyValue=Key_scanf();
			}
						Scanf_Input(Password_TWO_EEPR0M);

			if(Key_back == 10)		//重置密码
			{		
				Key_Count = 0;												
				WriteString((u8 *)"请输入新的密码！",0,0);Delay_ms(5);
				WriteString((u8 *)"                ",1,0);Delay_ms(5);
				WriteString((u8 *)"                ",2,0);Delay_ms(5);
				WriteString((u8 *)"                ",3,0);Delay_ms(5);	
				Password_TWO_EEPR0M[0] = 0;Password_TWO_EEPR0M[1] = 0;Password_TWO_EEPR0M[2] = 0;Password_TWO_EEPR0M[3] = 0;
				Password_TWO_EEPR0M[4] = 0;Password_TWO_EEPR0M[5] = 0;Password_TWO_EEPR0M[6] = 0;				
				
			}	
			
				if(Key_back == 12)
				{
						Key_Count = 0;
						state  = 0;display_Init();
				}
			
						if(Key_back == 15)
				{
							if(Password_EEPR0M[1]==Password_TWO_EEPR0M[1] && Password_EEPR0M[2]==Password_TWO_EEPR0M[2] && Password_EEPR0M[3]==Password_TWO_EEPR0M[3] &&
								Password_EEPR0M[4]==Password_TWO_EEPR0M[4] &&Password_EEPR0M[5]==Password_TWO_EEPR0M[5] &&Password_EEPR0M[6]==Password_TWO_EEPR0M[6])
							{						
									AT24C02_Write_Data(0x01,Password_TWO_EEPR0M[0]);
									AT24C02_Write_Data(0x02,Password_TWO_EEPR0M[1]);
									AT24C02_Write_Data(0x03,Password_TWO_EEPR0M[2]);
									AT24C02_Write_Data(0x04,Password_TWO_EEPR0M[3]);
									AT24C02_Write_Data(0x05,Password_TWO_EEPR0M[4]);
									AT24C02_Write_Data(0x06,Password_TWO_EEPR0M[5]);
									AT24C02_Write_Data(0x07,Password_TWO_EEPR0M[6]);
								
									WriteString((u8 *)"                ",0,0);Delay_ms(2);
									WriteString((u8 *)"****修改成功****",1,0);Delay_ms(2);
									WriteString((u8 *)"                ",2,0);Delay_ms(2);
									WriteString((u8 *)"                ",3,0);Delay_ms(2);
								
									GPIO_ResetBits(LED_PORT,LED);	
									Delay_ms(2000);
									state = 2;  Key_Count = 0;
									WriteString((u8 *)"  管理员界面！  ",0,0);Delay_ms(1);
									WriteString((u8 *)">   修改密码    ",1,0);Delay_ms(1);
									WriteString((u8 *)"    录入指纹    ",2,0);Delay_ms(1);
									WriteString((u8 *)"    删除指纹    ",3,0);Delay_ms(1);
							}
							else
							{
									WriteString((u8 *)"                ",0,0);Delay_ms(1);
									WriteString((u8 *)"    重新输入    ",1,0);Delay_ms(1);
									WriteString((u8 *)"                ",2,0);Delay_ms(1);
									WriteString((u8 *)"           		 ",3,0);Delay_ms(1);	
									state = 3;
							}								
				}

}







								
								




