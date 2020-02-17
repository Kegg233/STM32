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
*����	 ��������
*������ڣ�2012.7.2
*****************************************************************/

#include "stm32f10x.h"
#include "includes.h"


/*************************************************
*
*	������ ��ʼ��
*
**************************************************/

#define GPIO_SPK				GPIOB									//����
#define GPIO_SPK_Pin		GPIO_Pin_6						//
#define GPIO_SPK_RCC		RCC_APB2Periph_GPIOB	//ʱ��

#define JTAG_GPIO  (*(unsigned *)(AFIO_BASE+0x04))	 //���ù��ܼĴ���

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



























