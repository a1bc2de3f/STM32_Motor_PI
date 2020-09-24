#include "timer.h"

//arr：自动重装值  psc：时钟预分频数 
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM3,ENABLE);	  //使能定时器3
}

//arr：自动重装值  psc：时钟预分频数
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM2,ENABLE);	  //使能定时器3
}

//中断处理函数为空，清除中断标志位后结束中断
void TIM2_IRQHandler(void)
{
 if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)//溢出中断
 {
	 TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位 
	 if(OledTimeMs!=0)	OledTimeMs--;
 }
}

