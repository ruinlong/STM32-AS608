#ifndef _LOCK_H_
#define _LOCK_H_

#include <stm32f10x_conf.h>
extern u8 Key_Count;
extern u8 Key_back;
extern u8 state;
void UserLock_scanf(void);
void AdminLock_Scanf(void);
void admin_index(void);
void Clear_LCD12864(void);
void Manger_Display(void);
void State_Three(void);
void chaek_Two_Passwd(void);
void Scanf_Input(u8* pss);
void display_Init(void);
#endif
