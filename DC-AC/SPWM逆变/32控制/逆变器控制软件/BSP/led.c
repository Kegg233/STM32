/****************************************************************
* Copyright (c) 2010 ,
* All rights reserved. 
*
*
*�ļ����ƣ�
*�ļ���ʾ��
*ժҪ	 ��
*
*
*��ǰ�汾��v1.0 
*����	 ��ƻ�� QQ��422720026
*������ڣ�2012.7.2
*****************************************************************/

#include "stm32f10x.h"
#include "includes.h"



/*************************************************
*
*	led ��ʼ��
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
	GPIO_SetBits(GPIOC,GPIO_Pin_15);	 //�ø�
	
	led.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOA,&led);
	
}
void LedGreen(INT8S i)
{
	 if(i==0)	 	
		GPIO_SetBits(GPIOC,GPIO_Pin_13);	 //�ø�
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�õ�		 
}
void LedRed(INT8S i)
{
	if(i==0)
		GPIO_SetBits(GPIOC,GPIO_Pin_14);	 //�ø�
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);//�õ�		 
	
}
void LedBlue(INT8S i)
{
	if(i==0)
		GPIO_SetBits(GPIOC,GPIO_Pin_15);	 //�ø�
	 else
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);//�õ�		 
	
}

void WenKong(INT8U i)
{
	if(i==1)
		GPIO_SetBits(GPIOA,GPIO_Pin_7);	 //�ø�
	 else
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);//�õ�		 	
}
