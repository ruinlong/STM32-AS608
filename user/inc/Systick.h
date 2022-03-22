#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

//  0: AHB/8   				 1: Processor clock (AHB)
enum{Clk_Source_Div8,Clk_Source_AHB};   

//	 0: not assert SysTick exception request   1: assert SysTick exception request
enum{DIS_TickInt_assert,EN_TickInt_assert}; 

//  0: Counter disable  1:counter enable																						 
enum{DIS_SysTick,EN_Systick};								 


/*ClkSource: configuration clock source for AHB or AHB/8  
TickInt:     whether interrupt SysTick exception request When counting down to zero 
Enable:      Must load value before set disable. After load value enable Counter*/
void Systick_Init(uint32_t ClkSource,uint32_t TickInt,uint32_t Enable); 

/*set SysTick exception request enable/disbale  */ 
void Systick_TickInit(uint32_t Enable);  //allow

/*set initialize value for counter .After set value if you wang enable counter
 you must enable else disable.																								*/
void Systick_Load_Value(uint32_t num);

/* use this function can get Systick timer counter current value*/
uint32_t Systick_GetValue(void);


#endif
