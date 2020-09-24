/*
* @file         main.c	
* @author       土匪
* @version      Text
* @date         2020.09.12
* @brief        Capstone主程序
* @remark       一些支持：平衡小车之家、中景园电子、B站MjGame阿婆主     
*/

#include "sys.h"

unsigned char flag_Stop=1;     //电机停止标志位
int set=30;  //速度设定值（每10ms的脉冲数）
int get;     //编码器反馈脉冲数
int Kp=60,Ki=7;		//p,i参数
int err,Last_err,pi_out;//偏差/上次偏差/pi控制器输出
int step=10;//加减速步进值

int main(void)
{	
	delay_init();             //延时初始化
	OLED_Init();							//OLED初始化
//	uart_init(128000);        //初始化串口1（上位机通讯）
	Moto_Init();              //初始化控制电机的IO
	Pwm_Init(7199,0);         //初始化pwm输出(10kHZ)
	Encoder_Init_TIM4();      //定时器编码器模式
	EXTIX_Init();							//按键外部中断
	start_show();							//开始动画展示
	uart2_init(9600);        //蓝牙串口2初始化（APP）
	TIM3_Int_Init(99,7199);   //10ms中断
	while(1)
	{
//		DataScope();	          //上位机
    printf("{B%d:%d:%d}$",0,set,get);//APP波形显示
		delay_flag=1;	          //50ms标志位	
		capstone_show();				//capstone主界面刷新
		while(delay_flag);      //50ms延时到  波形显示上位机需要严格的50ms传输周期  
	}
}
