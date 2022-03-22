#ifndef _AT2402_H_
#define _AT2402_H_

#include <stm32f10x_conf.h>

#define AT24C02 0XA0

void AT24C02_PAGE_Write_Data(u8 page,u8 length,u8 *Data);
void AT24C02_PAGE_Read_Data(u16 page,u8 length,u8 *pt);
void AT24C02_Write_Data(u8 addr,u8 data);
u8 AT24C02_Read_Data(u8 addr);
#endif

