/****************************************************************
* Copyright (c) 2010 ,
* All rights reserved. 
*
*
*文件名称：
*文件标示：
*摘要	 ：
*
*
*当前版本：v1.0 
*作者	 ：苹安 QQ：422720026
*完成日期：2012.7.2
*****************************************************************/

#include "stm32f10x.h"
#include "includes.h"



/*************************************************
*
*	led 初始化
*
**************************************************/


void LedInit(void)
{
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);	

	
	led.GPIO_Speed=GPIO_Speed_50MHz;
	led.GPIO_Mode=GPIO_Mode_Out_PP;
	

	led.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC,&led);
	led.GPIO_Pin=GPIO_Pin_14;
	GPIO_Init(GPIOC,&led);
	
	led.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init(GPIOC,&led);
	GPIO_SetBits(GPIOC,GPIO_Pin_15);	 //置高
	
	led.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOA,&led);
	
}
void LedGreen(INT8S i)
{
	 if(i==0)	 	
		GPIO_SetBits(GPIOC,GPIO_Pin_13);	 //置高
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);//置低		 
}
void LedRed(INT8S i)
{
	if(i==0)
		GPIO_SetBits(GPIOC,GPIO_Pin_14);	 //置高
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);//置低		 
	
}
void LedBlue(INT8S i)
{
	if(i==0)
		GPIO_SetBits(GPIOC,GPIO_Pin_15);	 //置高
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);//置低		 
	
}

void WenKong(INT8U i)
{
	if(i==1)
		GPIO_SetBits(GPIOA,GPIO_Pin_7);	 //置高
	 else
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);//置低		 	
}
