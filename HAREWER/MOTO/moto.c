#include "moto.h"

void Moto_Init(void)//初始化控制电机的IO
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
//	//LED
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOC,&GPIO_InitStruct);	
}

void Pwm_Init(u16 arr,u16 psc) //初始化pwm输出
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //使能定时器1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA的时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;         //复用输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;   //PA8(CH1) PA11(CH4)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;                     //设定计数器自动重装值 
	TIM_TimeBaseInitStruct.TIM_Prescaler  = psc;                 //设定预分频器
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;                //设置时钟分割
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //初始化定时器
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //PWM模式1:CNT<CCR时输出有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;                             //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;       //有效为高电平
	TIM_OC4Init(TIM1,&TIM_OCInitStruct);                         //初始化输出比较参数
	
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH1使能预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE);              //使能TIM1在ARR上的预装载寄存器
	TIM_Cmd(TIM1,ENABLE);                            //使能定时器1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                 //高级定时器输出必须设置这句
}

