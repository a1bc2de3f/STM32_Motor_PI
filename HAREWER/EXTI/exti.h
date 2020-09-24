#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"

#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键1
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键2
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键4
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//读取按键3

void EXTIX_Init(void);//外部中断初始化		
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI15_IRQHandler(void);
extern int set;
#endif

