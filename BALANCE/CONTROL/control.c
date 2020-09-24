#include "control.h"

//主要控制流程函数，10ms执行一次
int TIM3_IRQHandler(void) 
{
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //清除定时器3中断标志位
		
		if(!flag_Stop)
		{
			get=Read_Encoder(4);      //取定时器4计数值（反馈值）
			err=set-get;              //计算偏差
			Incremental_PI();    			//增量式PI控制器输出		
			Xianfu_Pwm();						  //输出限幅
			Set_Pwm(pi_out);					//设置pwm
		}
		else
		{
			BIN1=0;BIN2=0;PWMB=0;
			get=0;Last_err=0;
		}
		
		if(delay_flag==1)						//给主函数提供50ms的延时（上位机用）
		{
			if(++delay_50==5)	 
			{
				delay_50=0;
				delay_flag=0;    
			}
		}	
		
	}
	return 0;
}

void Set_Pwm(int out)//赋值给PWM寄存器
{
		if(out>0) BIN1=0,   BIN2=1;
		else      BIN1=1,   BIN2=0;
		PWMB=myabs(out);
}

//pi控制器输出限幅
void Xianfu_Pwm(void) 
{
	int Amplitude=7200;  //===PWM满幅是7200 限制在7100
	if(pi_out<-Amplitude)  pi_out = -Amplitude;
	if(pi_out>Amplitude)   pi_out =  Amplitude;
}

int myabs(int a) //取绝对值
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
/**************************************************************************
函数功能：增量PI控制器
返回  值：pi控制器输出
根据增量式离散PID公式 
out+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
out代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pi_out+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI ()
{ 	
	 pi_out+=Kp*(err-Last_err)+Ki*err;   //增量式PI控制器
	 Last_err=err;	                   //保存上一次偏差 
	 return pi_out;                         //增量输出
}
