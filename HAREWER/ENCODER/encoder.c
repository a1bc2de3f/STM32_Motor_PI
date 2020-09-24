#include "encoder.h"


//TIM4初始化为编码器接口模式
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					     
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD-1; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//时钟不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;////向上计数  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,
														 TIM_ICPolarity_Rising, 
														 TIM_ICPolarity_Rising);//编码器模式3
	
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = 10;  //设置滤波器长度
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//使能定时器中断
  TIM_SetCounter(TIM4,1000);//设置TIMx 计数器寄存器值
  TIM_Cmd(TIM4, ENABLE); //使能定时器
}


//中断处理函数为空，清除中断标志位后结束中断
void TIM4_IRQHandler(void)
{
 if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//溢出中断
 {
	 TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位 
 }
}
//单位时间读取编码器计数值（正转为正值，反转为负值，1000为计数初始值）
int Read_Encoder(u8 TIMX)//读取计数器的值
{
  int count;
	switch(TIMX)
	{
	  case 2:count=(short)TIM2->CNT; TIM2 -> CNT=0;  break;
		case 3:count=(short)TIM3->CNT; TIM3 -> CNT=0;  break;
		case 4:count=(short)TIM4->CNT; TIM4 -> CNT=1000; break;
		default: count=0;
	}
  return (count-1000);
}
