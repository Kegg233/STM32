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



void Time2Start(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;      //ѡ���ж�ͨ��3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);

//	TIM_TimeBaseStructure.TIM_Period = 36000; //10���� 
//	TIM_TimeBaseStructure.TIM_Prescaler =19;  
	TIM_TimeBaseStructure.TIM_Period = 35999; //1���� 
	TIM_TimeBaseStructure.TIM_Prescaler =19; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  
	TIM_Cmd(TIM2, ENABLE);
}
void Time2End( void )
{
	TIM_Cmd(TIM2,DISABLE);	
}


extern OS_EVENT 	* time_10;
// volatile INT32U time2count=0;
// TIM2_IRQHandler()
// {
// 	OS_CPU_SR  cpu_sr;
//   OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
//   OSIntEnter();
//   OS_EXIT_CRITICAL();
// 	
// 	OSSemPost(time_10);
// 	time2count++;
// 	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
// 	OSIntExit();
// }


volatile INT32S timcounter=0;	
void TIM2_IRQHandler(void )	//2ms ��ʱ
{			
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
  OSIntNesting++; 
	OS_EXIT_CRITICAL();
	
	timcounter=1; 
	OSSemPost(time_10);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	OSIntNesting--; 
}


















