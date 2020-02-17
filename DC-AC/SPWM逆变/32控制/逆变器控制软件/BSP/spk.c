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
*作者	 ：李良万
*完成日期：2012.7.2
*****************************************************************/

#include "stm32f10x.h"
#include "includes.h"


/*************************************************
*
*	扬声器 初始化
*
**************************************************/

#define GPIO_SPK				GPIOB									//引脚
#define GPIO_SPK_Pin		GPIO_Pin_6						//
#define GPIO_SPK_RCC		RCC_APB2Periph_GPIOB	//时钟

#define JTAG_GPIO  (*(unsigned *)(AFIO_BASE+0x04))	 //复用功能寄存器

void SpkInit(void)
{
	GPIO_InitTypeDef spk;

	RCC_APB2PeriphClockCmd(GPIO_SPK_RCC,ENABLE);

	spk.GPIO_Pin=GPIO_SPK_Pin;
	spk.GPIO_Speed=GPIO_Speed_10MHz;
	spk.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_SPK,&spk);
}

void SpkOut(INT8S i)
{
	if(i==0)
		GPIO_ResetBits(GPIO_SPK,GPIO_SPK_Pin);
	else
		GPIO_SetBits(GPIO_SPK,GPIO_SPK_Pin);
}



























