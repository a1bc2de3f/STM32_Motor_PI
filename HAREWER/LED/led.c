#include "led.h"

void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能 PORTB 时钟 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_5);                 //PB5 输出高电平
}
/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁频率 
返回  值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
		if(++temp==time)	LED=~LED,temp=0; //低电平点亮
}
