#ifndef _FINGER_
#define _FINGER_

#include "stm32f10x.h"
#include "usart.h"
#include "Sys_delay.h"
#include "key.h"
#include "Lcd12864.h"
#include "I2C.h"
#include "AT24C02.h"

#define User 1
#define buffer1ID  0x01
#define buffer2ID  0x02
#define queren  0x10
#define tuichu  0x0C
#define shanchu 0x08

//int summaf,summas;
//unsigned char   UserPassword[7]={0};//√‹¬Î
//unsigned char   mimaID[6]={1,2,3,4,5,6};
//unsigned char   mima[6];
//unsigned char   Member=1,sec;
//unsigned char   K;
//unsigned char   Key;
//unsigned char   querenma=11;
//unsigned char   sum[2];
//unsigned int    PageID;
//unsigned int    dz[4];

unsigned char Chack(uint8_t User_Number);
unsigned char PassWord_Chack(void);
void KeyDeal(unsigned char Key);
void SFG_GetEcho(void);
void SFG_getimage(void);
void SFG_genchar(uint8_t bufferID);
void SFG_fastsearch(uint8_t bufferID);
void SFG_enroll(void);
void SFG_deletchar(uint16_t pageID);
void SFG_identify(void);
void shuazhiwen(void);
void addfinger(void);
void deletfinger(void);
void gaimima(void);
void zhu(void);
void guanliyuan(void);
void fan(void);


#endif



