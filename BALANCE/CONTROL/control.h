#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

int TIM3_IRQHandler(void); 
int myabs(int a);
void Set_Pwm(int moto);
void Xianfu_Pwm(void);
int Incremental_PI (void);

extern unsigned char flag_Stop;
extern unsigned char delay_flag,delay_50;
extern int set;
extern unsigned int OledTimeMs;
#endif

