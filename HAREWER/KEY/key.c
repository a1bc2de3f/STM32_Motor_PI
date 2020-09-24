#include "key.h"

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能相应端口时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_4;//K1,2,4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//K3
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/**************************************************************************
函数功能：按键扫描
入口参数：双击等待时间
返回  值：按键状态 0：无动作 1：单击 2：双击 
**************************************************************************/
u8 click_N_Double (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
			if(flag_key==1) 
			{
				double_key++;
				count_key=1;	
			}
			if(double_key==2) 
			{
		  	double_key=0;
			  count_single=0;
				return 2;//双击执行的指令
			}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			if(++count_single>time)
			{
			double_key=0;
			count_single=0;	
			return 1;//单击执行的指令
			}
		}	
		return 0;
}
/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：单击 
**************************************************************************/
u8 click(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY==0)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(1==KEY)			flag_key=1;
			return 0;//无按键按下
}
