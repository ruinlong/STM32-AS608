#include "finger.h"

extern uint8_t Rxflag;
extern uint8_t ucTemp;
int summaf,summas;
unsigned char   UserPassword[7]={0};//����
unsigned char   mimaID[6]={1,2,3,4,5,6};
unsigned char   mima[6];
unsigned char   Member=1,sec;
int   K;
unsigned char   Key;
unsigned char   querenma=11;
unsigned char   sum[2];
unsigned int    PageID;
unsigned int    dz[4];


/********************************************************************
* ���� : Chack(uchar User_Number)
* ���� : ��һ�û�������
* ���� : User_Number
* ��� : ������ȷ����󣬴��󷵻�0����ȷ����1
********************************************************************/
unsigned char Chack(uint8_t User_Number)
{
	uint8_t flag=0, i,temp[6],Address;
	Address=User_Number*10;
//	for(i=0;i<6;i++)
//	{
//		temp[i]=x24c02_read(Address);
//		delayms(10);
//		Address++;
//	}
	if (ee_CheckOk() == 0)
     	/* û�м�⵽EEPROM */
		 LCD_Wstr(1,0,"û�м�⵽EEPROM!");
  else if(ee_ReadBytes(temp, Address, 6)==0)
	      {
	         LCD_Wstr(1,1,"�����ȡʧ��");
					 LCD_Wstr(3,0,"  �����������");	
            while(KEY_Scan()==0);					
		    }
		  		
	for(i=0;i<6;i++)
	{
		if(temp[i]==UserPassword[i])
		{
//			SysTick_Delay_ms(10);
//			printf("%d ",temp[i]);
			flag++;	
		}
	}
	if(flag==6) flag=1;
	else flag=0;
//	printf("\n flag=%d\n",flag);
	return flag;
}


/********************************************************************
* ���� : PassWord_Chack()
* ���� : �����û�������
* ���� : ��
* ��� : ������ȷ����󣬴��󷵻�0����ȷ����1
********************************************************************/
unsigned char PassWord_Chack(void)
{
	uint8_t i=0;
	while(i<User)
	{
		if(Chack(i)==1)
		{
			Member=i+1;
			return 1;
		}
		i++;	
	}
	return 0;	
}
   
void KeyDeal(unsigned char Key)
{  //unsigned char n;
   if(Key!=0)
 {
           
		   switch(Key)
		   {
		   case 0x01: K=1; break;	 
		   case 0x02: K=2; break;  
		   case 0x03: K=3; break;  
		   case 0x04: K=0x81;break;       
		   case 0x05: K=4; break;
		   case 0x06: K=5; break;
		   case 0x07: K=6; break;
		   case 0x08: K=34;break;		
		   case 0x09: K=7; break;
		   case 0x0A: K=8; break;
		   case 0x0B: K=9; break;
		   case 0x0C: K=0x0c;  break;		
		   case 0x0D: K=0X18; break;		
		   case 0x0E: K=0; break;
		   case 0x0F: K=11; break;
		   case 0x10: K=0X88;  break;		
		   default: break;
		   }
  }
}
        
void SFG_GetEcho(void)			      //����
{
	  uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x53,0x00};	
    Usart_SendStr_length( USART3,order,11 );
		
		summaf=0x57;
		USART_SendBety( USART3,summaf);
		
		while(!Rxflag);
		   Rxflag=0;
		  querenma=ucTemp;
		
		while(!Rxflag);
		   Rxflag=0;		
		  sum[1]=ucTemp;
		
	  while(!Rxflag);
		   Rxflag=0;		
		  sum[0]=ucTemp;
		
		summas=(sum[1]<<8)+sum[0];
}

void SFG_getimage(void)			      //¼��ָ��ͼ��
{
	 uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x01,0x00};
	 
	 Usart_SendStr_length( USART3,order,11 );
	 
	 summaf=0x05;
	 USART_SendBety( USART3,summaf);
	 
	 
	 while(!Rxflag);
	   Rxflag=0;
		  querenma=ucTemp;
	   
	 
	 while(!Rxflag);
	    Rxflag=0;		
		  sum[1]=ucTemp;
		
	  while(!Rxflag);
		   Rxflag=0;
		  sum[0]=ucTemp;
		
		summas=(sum[1]<<8)+sum[0];	 

}

void SFG_genchar(uint8_t bufferID) //��������������charbuffer1/2  ���ú�Ƭ�������ʱ仯@@@
{
	uint8_t  order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02};	
	Usart_SendStr_length( USART3,order,10 );
	
	USART_SendBety( USART3,bufferID);
	
	summaf=0x07+bufferID;
  sum[0]=summaf;
  sum[1]=summaf>>8;
	
	USART_SendBety( USART3,sum[1]);
	USART_SendBety( USART3,sum[0]);
	
			
	while(!Rxflag);
			 Rxflag=0;
		  querenma=ucTemp;
	 
	 while(!Rxflag);
		  Rxflag=0;
		  sum[1]=ucTemp;
		
	  while(!Rxflag);
		  Rxflag=0;
		  sum[0]=ucTemp;
		
	summas=(sum[1]<<8)+sum[0];	 
}

void SFG_fastsearch(uint8_t bufferID)  //����ָ�Ʒ���ָ��ID��   sum��pagenum>255����ʹ����@@@
{   
	uint8_t i,ID1,ID2;
	uint8_t order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x1b};
	uint8_t order1[4]={0x00,0x00,0x00,180};
	Usart_SendStr_length( USART3,order,10 );
	
	USART_SendBety( USART3,bufferID);
	
	Usart_SendStr_length( USART3,order1,4 );
	
	 summaf=9+0x1b+bufferID+180;
   sum[0]=summaf;
   sum[1]=summaf>>8;
	 
	 USART_SendBety( USART3,sum[1]);
	 USART_SendBety( USART3,sum[0]);
	
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag);
		 Rxflag=0;
	 }
	 
	 while(!Rxflag);
	 Rxflag=0;
	 querenma=ucTemp;
	
	  while(!Rxflag);
	    Rxflag=0;
	  ID1 = ucTemp;
		
		while(!Rxflag);
	    Rxflag=0;
	  ID2 = ucTemp;
		
		while(!Rxflag);
	    Rxflag=0;
	 
	  while(!Rxflag);
	    Rxflag=0;
	 
		sum[1]=ucTemp;
	 
	  while(!Rxflag);
		 Rxflag=0;
		sum[0]=ucTemp;
		 
		summas=(sum[1]<<8)+sum[0];
		
		PageID=(ID1<<8)+ID2;
}

void SFG_enroll(void)				 //�Զ�ע��ģ�巵�ش洢ID  =¼ͼ��+�ϲ�����ģ��+����ģ��
{
   uint8_t i,ID1,ID2;
   uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x10,0x00};	
	 Usart_SendStr_length( USART3,order,11 );
	 
	 summaf=0x14;
	 USART_SendBety( USART3,summaf);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag);
		 Rxflag=0;
	 }
	 
	 while(!Rxflag);
	 Rxflag=0;
	 querenma=ucTemp;
	
	 while(!Rxflag);
	   Rxflag=0;
	  ID1 = ucTemp;
		
		while(!Rxflag);
	    Rxflag=0;
	  ID2 = ucTemp;
	 
	  while(!Rxflag);
		Rxflag=0;
		sum[1]=ucTemp;
	 
		sum[0]=ucTemp;
	 
	   PageID=(ID1<<8)+ID2;
}

void SFG_deletchar(uint16_t pageID)   //ɾ��ָ��		     У�����2�ֽڵ�ҳ�봦Ӧ�ָߵ��ֽ����
{
   uint8_t i,ID1,ID2;
	 uint8_t  order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x0c};	
	 Usart_SendStr_length( USART3,order,10 );
	 
	 ID1=pageID;
	 ID2=pageID>>8;
	 
	 USART_SendBety( USART3,ID2);
	 USART_SendBety( USART3,ID1);
	 USART_SendBety( USART3,0x00);
	 USART_SendBety( USART3,0x01);
	 
	 summaf=0x15+ID1+ID2;
   sum[0]=summaf;
   sum[1]=summaf>>8;
	 
	 USART_SendBety( USART3,sum[1]);
	 USART_SendBety( USART3,sum[0]);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag);
		 Rxflag=0;
//		 ucTemp=0;
	 }
	 
	   querenma=ucTemp;
	 
	 while(!Rxflag);	
   Rxflag=0;	 
	 sum[1]=ucTemp;
	 
	 while(!Rxflag);
	 Rxflag=0;
	 sum[0]=ucTemp;
	 
	 summas=(sum[1]<<8)+sum[0];
}

void SFG_identify(void)				//�Զ���ָ֤��     ¼ͼ��+��������+����
{
   uint8_t i,ID1,ID2;
	 uint8_t  order[11]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x11,0x00};	
	 Usart_SendStr_length( USART3,order,11 );
	 
	 summaf=0x15;
	 
	 USART_SendBety( USART3,summaf);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag)
			ucTemp = 0XFF;
		 Rxflag=0;	
		 
	 }
	 
	 while(!Rxflag);
    Rxflag=0;		 
	 querenma=ucTemp;

	 Rxflag=0;
	 ID2 = ucTemp;
	 
	  while(!Rxflag);
	   Rxflag=0;
	  while(!Rxflag);
	   Rxflag=0;
	 
	  while(!Rxflag);
	   Rxflag=0;
		sum[1]=ucTemp;
	 
	  while(!Rxflag);
	   Rxflag=0;
		sum[0]=ucTemp;
		
		summas=(sum[1]<<8)+sum[0];
		
		PageID=(ID1<<8)+ID2;
		
}

void shuazhiwen(void)
{
	uint8_t IDs1,IDs2,IDs3;
	
	LCD_Clear() ;
	LCD_Wstr(2,1,"�밴��ָ����");
	
	do
	{
	  SFG_identify();
	}	while(querenma==2);		
		
	if(querenma==0)
   {
		LCD_Clear();
		LCD_Wstr(2,2,"���Ѵ�"); 
		IDs1=PageID/100;
		IDs2=PageID/10%10;
		IDs3=PageID%10;
		LCD_Wstr(3,2,"���Ϊ:");
		LCD_SendCom(0x8D);		//ָ����������ʾλ��
		Send_Words(0x30+IDs1);
		Send_Words(0x30+IDs2);
		Send_Words(0x30+IDs3);
		Relay_ON;
		SysTick_Delay_ms(2500);
		Relay_OFF;	
	}
	else if(querenma==9)
 		{
			Beef_ON;
			LCD_Clear();
			LCD_Wstr(2,1,"û������ָ��");
			LCD_Wstr(3,1,"�����°���ָ");
		}
	  SysTick_Delay_ms(100);
		Beef_OFF;

}

void addfinger(void)
{
	uint8_t IDa1,IDa2,IDa3;
	LCD_Clear();
	LCD_Wstr(2,2,"�밴��ָ");    
	SFG_getimage();
	while(querenma!=0)
	SFG_genchar(buffer1ID);
	SFG_fastsearch(buffer1ID);
	while(querenma==1)
	SFG_fastsearch(buffer1ID);
	if(querenma==0)
	{
		LCD_Clear();
		LCD_Wstr(2,1,"��ָ���Ѵ洢");
		LCD_Wstr(3,0,"  �����������"); 
	    while(KEY_Scan()==0);
	}
	else if(querenma==9)
		{
			LCD_Clear();
			LCD_Wstr(2,1,"���ٴΰ���ָ");
			SFG_enroll();
			while(querenma==2)
			SFG_enroll();
			LCD_Clear();
			if(querenma==0)
			{ 
				IDa1=PageID/100;IDa2=PageID/10%10;IDa3=PageID%10;
				LCD_Wstr(1,1,"ָ�Ʋɼ��ɹ�");
				LCD_Wstr(3,1,"���Ϊ:");
				LCD_SendCom(0x8D); 
				Send_Words(0x30+IDa1);Send_Words(0x30+IDa2);Send_Words(0x30+IDa3);
	  		}
	  	else if(querenma!=0)
	  		{
				LCD_Wstr(1,1,"ָ�Ʋɼ�ʧ��");
				LCD_Wstr(2,1,"�����²���");
	 		}
		LCD_Wstr(4,0,"  �����������"); 
	    while(KEY_Scan()==0);
   		}
	      LCD_Clear();
}


void deletfinger(void)
{
	uint8_t i,j=0;
	LCD_Clear();
	LCD_Wstr(2,0,"����ɾȥ��ָ�ƺ�");
	for(i=0;i<5;i++) dz[i]=0;	
	   Key=KEY_Scan();
	   while(Key!=queren)
	   {
	     Key=KEY_Scan();
	     KeyDeal(Key);
	     SysTick_Delay_ms(30);			                              //�����ж���@@@
	     if(Key==0) K=10;
	     if((0<=K)&&(K<=9))
	     {
	      dz[j]=K;
		   if(j<3)
					{	
						LCD_SendCom(0x88+j);		//ָ����������ʾλ��
						Send_Words(0x30+dz[j]);	
					}
						++j;
		  if(j==4)
	      j=3;												   //@@#yinhuang
	     }   //��ʾLCD12864������ʾ 
		 if(K==34)		//����ɾ����
		  {
		    if(j==0)
			{
				LCD_SendCom(0x88);		//ָ����������ʾλ��
				Send_Words(0x20);
			}
			else
			{
				--j;
				LCD_SendCom(0x88+j);	    //ָ����������ʾλ��
				Send_Words(0x20);
			}
		}
	}
	if(j>=2)
	PageID=dz[2]+dz[1]*10+dz[0]*100;
	if(j==0)
	PageID=dz[0];
	SFG_deletchar(PageID);
	if(querenma==0)
	{
		LCD_Clear();
		LCD_Wstr(2,0,"ɾȥָ�ƺųɹ���"); 
	}
	else
	{
		LCD_Clear();
		LCD_Wstr(2,0,"ɾȥָ�ƺ�ʧ�ܣ�");  
	}
	LCD_Wstr(3,1,"�����������"); 
	while(KEY_Scan()==0);
	LCD_Clear();
}
        

void gaimima(void)
{
	uint8_t i,j=0,mima1[6],mima2[6];
	uint8_t temp;
	LCD_Clear();
	LCD_Wstr(1,1,"������������");
	for(i=0;i<6;i++)mima1[i]=0;									
	   Key=0;//KEY_Scan();
      while(Key!=queren)
	   {
	     Key=KEY_Scan();
	     KeyDeal(Key);
	     SysTick_Delay_ms(30);				                              
	     if(Key==0)K=10;
	     if((K>=0)&&(K<=9))
	     {
	      mima1[j]=K;
		  if(j<6)
		  {	
				LCD_SendCom(0x89+j);		//ָ����������ʾλ��
				Send_Words(0x0f);	
		  }
	      ++j;
		  if(j==7)
	      j=6;												   //@@#yinhuang
	     }   //��ʾLCD12864������ʾ 
		 if(K==34)		//����ɾ����
		  {
		    if(j==0)
			{
				LCD_SendCom(0x89);		//ָ����������ʾλ��
				Send_Words(0x20);
			}
			else
			{
				--j;
				LCD_SendCom(0x89+j);	    //ָ����������ʾλ��
				Send_Words(0x20);
			}
		}
	}
	LCD_Clear();
	j=0;
	LCD_Wstr(2,0,"���ٴ�����������");
	for(i=0;i<6;i++)mima2[i]=0;									
	   Key=KEY_Scan();
      while(Key!=queren)
	   {
	     Key=KEY_Scan();
	     KeyDeal(Key);
	     SysTick_Delay_ms(30);				                              
	     if(Key==0)K=10;
	     if((K>=0)&&(K<=9))
	     {
	      mima2[j]=K;
		  if(j<6)
		  {		
				LCD_SendCom(0x89+j);		//ָ����������ʾλ��
		  }
	      ++j;
		  if(j==7)
	      j=6;												   //@@#yinhuang
	     }   //��ʾLCD12864������ʾ 
		 if(K==34)		//����ɾ����
		  {
		    if(j==0)
			{
				LCD_SendCom(0x89);		//ָ����������ʾλ��
				Send_Words(0x20);
			}
			else
			{
				--j;
				LCD_SendCom(0x89+j);	    //ָ����������ʾλ��
				Send_Words(0x20);
			}
		}
	}
	LCD_Clear();
	if((mima1[0]==mima2[0])&&(mima1[1]==mima2[1])&&(mima1[2]==mima2[2])&&(mima1[3]==mima2[3])&&(mima1[4]==mima2[4])&&(mima1[5]==mima2[5]))
	{
		for(i=0;i<6;i++)
		mimaID[i]=mima1[i];
		/////////////////////////////////////////////////////
//		printf("�洢�������ǣ�\n");
		for(i=0;i<6;i++)           //����������6λ����
		{
			UserPassword[i]=mima1[i]+0x30; 
//      printf("%d ",UserPassword[i]);			
		}
//		printf("\n");
		temp=(Member-1)*10;	
		SysTick_Delay_ms(5);
//		for(k=0;k<6;k++)
//		{
////			x24c02_write(temp,UserPassword[k]);
//			SysTick_Delay_ms(10);
//			temp++;
//		} 
     if (ee_CheckOk() == 0)
     	/* û�м�⵽EEPROM */
		 {
		  LCD_Wstr(1,0,"û�м�⵽EEPROM!");
			LCD_Wstr(3,0,"  �����������");
		 }
     else	if(ee_WriteBytes(UserPassword,temp, 6))	
		 {
		  LCD_Wstr(1,1,"�����޸ĳɹ�"); 
		  LCD_Wstr(3,0,"  �����������");
		 }
		 else
		 {
			 LCD_Wstr(1,1,"����洢ʧ��"); 
		   LCD_Wstr(3,0,"  �����������");		 
		 }
		while(KEY_Scan()==0);
	}
	else
	{
		LCD_Wstr(1,0,"  �����޸�ʧ��  ");
		LCD_Wstr(2,0,"������������벻"); 
		LCD_Wstr(3,0,"һ�£������²���");       
		LCD_Wstr(4,0,"  �����������"); 
		while(KEY_Scan()==0);
	}
	LCD_Clear();
}


void zhu(void)
{  	 
    LCD_Clear();
	  LCD_Wstr(2,2,"���Ѵ�");
   	Relay_ON;
	  SysTick_Delay_ms(2500);
	  Relay_OFF;
    LCD_Wstr(3,0,"  �����������");
	  while(KEY_Scan()==0);
}

void guanliyuan(void)
{ 
	  uint8_t i,j=0;
   	uint8_t Right_flag;
    LCD_Clear();
		LCD_Wstr(1,1,"���������룺");	
	   for(i=0;i<6;i++)mima[i]=0;									
	   Key=0;//KEY_Scan();
      while(Key!=queren)
	   {
	     Key=KEY_Scan();
	     KeyDeal(Key);
	     SysTick_Delay_ms(30);				                              
	     if(Key==0)  K=10;
	     if((K>=0)&&(K<=9))
	     {
	      mima[j]=K;

		  if(j<6)
		  {	
		   LCD_SendCom(0x89+j);		//ָ����������ʾλ��
	     Send_Words(0x0f);	
		  }
	      ++j;
		  if(j==7)
	      j=6;												  
	     }   //��ʾLCD12864������ʾ 
		 if(K==34)		//����ɾ����
		  {
		    if(j==0)
			{
		      LCD_SendCom(0x89);		//ָ����������ʾλ��
	        Send_Words(0x20);
			}
			else
			{
			  --j;
		      LCD_SendCom(0x89+j);	    //ָ����������ʾλ��
	        Send_Words(0x20);
			}
		  }
	   }
    LCD_Clear();

	  for(i=0;i<6;i++)
         {
            UserPassword[i]=mima[i]+0x30;           					 
          } 

	 if(j==6){ Right_flag=PassWord_Chack(); }
	  if (Right_flag==1)
	 {
	  	   Right_flag=0;

//     while(KEY_Scan()!=tuichu)
		 do
      {	 
		LCD_Wstr(1,0,"����1 : ����ָ��"); 
		LCD_Wstr(2,0,"����2 : ɾȥָ��");
		LCD_Wstr(3,0,"����3 : �ֶ�����");
		LCD_Wstr(4,0,"����4 : �޸�����");
		KeyDeal(KEY_Scan());  
	    switch(K)
	    {
	     case 1:    addfinger();K=6; break;
	     case 2:    deletfinger();    break;
		   case 3:	 zhu();	K=8;  break;
		   case 4:    gaimima();        break;
	     default: break;
	    }
      }while(KEY_Scan()!=tuichu) ;
     } 
    else
    { 
		Beef_ON;
		LCD_Wstr(1,2,"�������");
		LCD_Wstr(2,0,"  �����²�����"); 
		LCD_Wstr(3,1,"�����������");
    SysTick_Delay_ms(1000);	
    Beef_OFF;			
	     while(KEY_Scan()==0);
    }
  Key=0;
  LCD_Clear();
}


void fan(void)

{
//	LCD_Wstr(1,2,"���Ȱ���");
//	LCD_Wstr(2,2,"��ˢָ��");
	LCD_Wstr(1,2,"��ӭʹ��");
	LCD_Wstr(2,1,"ָ���Ž�ϵͳ");
	LCD_Wstr(3,1,"�밴��ָ����");
  Key=KEY_Scan();
	Beef_OFF;
  if(Key==0x04)			//����Ա����
  {
  	LCD_Clear();
	  guanliyuan();
    LCD_Clear();
  }
  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))		//ָ��ˢ��

  {
  	LCD_Clear();
	  shuazhiwen();
  	LCD_Clear();
  }
}	










