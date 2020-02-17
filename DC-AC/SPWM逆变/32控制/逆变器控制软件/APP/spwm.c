/****************************************************************
* Copyright (c) 2013 ,
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
*完成日期：2013.8.2
*****************************************************************/

#include "stm32f10x.h"
#include "includes.h"


#define   Fsys           72000000ul   //  system freq 72MHz
#define   Fpwm           25000        //  PWM freq  20K

void  PWMTimer(INT32U fhz)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB1PeriphClockCmd(  RCC_APB1Periph_TIM2,ENABLE);
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_GPIOA,ENABLE);
  
  TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period = (72000000/2) / fhz;		//重装载寄存器周期的值	25K
  TIM_TimeBaseStructure.TIM_Prescaler = 0;								//TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;  //TIM中央对齐模式1计数模式
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分割
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_Pulse = ((72000000/2 / fhz) * 43) / 100;
  TIM_OC2Init(TIM2,&TIM_OCInitStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_Pulse = ((72000000/2 / fhz) * (100-43)) / 100;
  TIM_OC3Init(TIM2,&TIM_OCInitStructure);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  TIM_Cmd(TIM2,ENABLE);

}
void DCOut(FunctionalState NewState)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(NewState==ENABLE)
	{
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);			
	}
}
INT16U dmabuff[250]={
0x0,0x24,0x49,0x6D,0x92,0xB6,0xDA,0xFF,0x123,0x147,0x16B,0x18F,0x1B3,0x1D7,0x1FB,0x21F,0x242,0x266,
	0x28A,0x2AD,0x2D0,0x2F3,0x316,0x339,0x35C,0x37F,0x3A1,0x3C4,0x3E6,0x408,0x42A,0x44B,0x46D,0x48E,0x4AF,
	0x4D0,0x4F1,0x512,0x532,0x552,0x572,0x592,0x5B1,0x5D0,0x5EF,0x60E,0x62D,0x64B,0x669,0x687,0x6A4,0x6C1,
	0x6DE,0x6FB,0x717,0x733,0x74F,0x76A,0x786,0x7A0,0x7BB,0x7D5,0x7EF,0x809,0x822,0x83B,0x854,0x86C,0x884,
	0x89B,0x8B3,0x8C9,0x8E0,0x8F6,0x90C,0x921,0x936,0x94B,0x95F,0x973,0x987,0x99A,0x9AC,0x9BF,0x9D1,0x9E2,
	0x9F3,0xA04,0xA14,0xA24,0xA34,0xA43,0xA52,0xA60,0xA6E,0xA7B,0xA88,0xA95,0xAA1,0xAAD,0xAB8,0xAC3,0xACD,
	0xAD7,0xAE0,0xAE9,0xAF2,0xAFA,0xB02,0xB09,0xB10,0xB16,0xB1C,0xB22,0xB27,0xB2B,0xB30,0xB33,0xB36,0xB39,0xB3B,0xB3D,0xB3F,0xB40,0xB40,
0xB40,0xB40,0xB3F,0xB3D,0xB3B,0xB39,0xB36,0xB33,0xB30,0xB2B,0xB27,0xB22,0xB1C,0xB16,0xB10,0xB09,0xB02,0xAFA,0xAF2,0xAE9,0xAE0,0xAD7,0xACD,0xAC3,0xAB8,0xAAD,0xAA1,0xA95,0xA88,0xA7B,0xA6E,0xA60,0xA52,0xA43,0xA34,0xA24,0xA14,0xA04,0x9F3,0x9E2,0x9D1,0x9BF,0x9AC,0x99A,0x987,0x973,0x95F,0x94B,0x936,0x921,0x90C,0x8F6,0x8E0,0x8C9,0x8B3,0x89B,0x884,0x86C,0x854,0x83B,0x822,0x809,0x7EF,0x7D5,0x7BB,0x7A0,0x786,0x76A,0x74F,0x733,0x717,0x6FB,0x6DE,0x6C1,0x6A4,0x687,0x669,0x64B,0x62D,0x60E,0x5EF,0x5D0,0x5B1,0x592,0x572,0x552,0x532,0x512,0x4F1,0x4D0,0x4AF,0x48E,0x46D,0x44B,0x42A,0x408,0x3E6,0x3C4,0x3A1,0x37F,0x35C,0x339,0x316,0x2F3,0x2D0,0x2AD,0x28A,0x266,0x242,0x21F,0x1FB,0x1D7,0x1B3,0x18F,0x16B,0x147,0x123,0xFF,0xDA,0xB6,0x92,0x6D,0x49,0x24,0x0
};
INT16U dmabuff1[250]={
0x0,0x24,0x49,0x6D,0x92,0xB6,0xDA,0xFF,0x123,0x147,0x16B,0x18F,0x1B3,0x1D7,0x1FB,0x21F,0x242,0x266,
	0x28A,0x2AD,0x2D0,0x2F3,0x316,0x339,0x35C,0x37F,0x3A1,0x3C4,0x3E6,0x408,0x42A,0x44B,0x46D,0x48E,0x4AF,
	0x4D0,0x4F1,0x512,0x532,0x552,0x572,0x592,0x5B1,0x5D0,0x5EF,0x60E,0x62D,0x64B,0x669,0x687,0x6A4,0x6C1,
	0x6DE,0x6FB,0x717,0x733,0x74F,0x76A,0x786,0x7A0,0x7BB,0x7D5,0x7EF,0x809,0x822,0x83B,0x854,0x86C,0x884,
	0x89B,0x8B3,0x8C9,0x8E0,0x8F6,0x90C,0x921,0x936,0x94B,0x95F,0x973,0x987,0x99A,0x9AC,0x9BF,0x9D1,0x9E2,
	0x9F3,0xA04,0xA14,0xA24,0xA34,0xA43,0xA52,0xA60,0xA6E,0xA7B,0xA88,0xA95,0xAA1,0xAAD,0xAB8,0xAC3,0xACD,
	0xAD7,0xAE0,0xAE9,0xAF2,0xAFA,0xB02,0xB09,0xB10,0xB16,0xB1C,0xB22,0xB27,0xB2B,0xB30,0xB33,0xB36,0xB39,0xB3B,0xB3D,0xB3F,0xB40,0xB40,
0xB40,0xB40,0xB3F,0xB3D,0xB3B,0xB39,0xB36,0xB33,0xB30,0xB2B,0xB27,0xB22,0xB1C,0xB16,0xB10,0xB09,0xB02,0xAFA,0xAF2,0xAE9,0xAE0,0xAD7,0xACD,0xAC3,0xAB8,0xAAD,0xAA1,0xA95,0xA88,0xA7B,0xA6E,0xA60,0xA52,0xA43,0xA34,0xA24,0xA14,0xA04,0x9F3,0x9E2,0x9D1,0x9BF,0x9AC,0x99A,0x987,0x973,0x95F,0x94B,0x936,0x921,0x90C,0x8F6,0x8E0,0x8C9,0x8B3,0x89B,0x884,0x86C,0x854,0x83B,0x822,0x809,0x7EF,0x7D5,0x7BB,0x7A0,0x786,0x76A,0x74F,0x733,0x717,0x6FB,0x6DE,0x6C1,0x6A4,0x687,0x669,0x64B,0x62D,0x60E,0x5EF,0x5D0,0x5B1,0x592,0x572,0x552,0x532,0x512,0x4F1,0x4D0,0x4AF,0x48E,0x46D,0x44B,0x42A,0x408,0x3E6,0x3C4,0x3A1,0x37F,0x35C,0x339,0x316,0x2F3,0x2D0,0x2AD,0x28A,0x266,0x242,0x21F,0x1FB,0x1D7,0x1B3,0x18F,0x16B,0x147,0x123,0xFF,0xDA,0xB6,0x92,0x6D,0x49,0x24,0x0
};
INT16U dmabuff2[250],halfflag=0;
void halfword(FP32 j)
{
	INT16U i=0;
	halfflag=1;
	for(i=0;i<250;i++)
		dmabuff2[i]=(INT16U)(dmabuff1[i]*j);
	halfflag=0;
	for(i=0;i<250;i++)
		dmabuff[i]=dmabuff2[i];
	
}

void ban(void)
{
	INT16U i=0;
	if(halfflag==1)
		return ;
// 	for(i=0;i<250;i++)
// 		dmabuff[i]=dmabuff2[i];	
}


#define TIM1_CCR1_Address                        ((uint32_t)0x40012C34)        /* 0x 4001 2C00 + 0x 34 */
#define TIM1_DMAR_Address    0x40012C4C
void Time1Config(void)
{
	
	INT32U j=0,K=(u32)&dmabuff;
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
  TIM_BDTRInitTypeDef TIM_BDTR_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_TIM1|RCC_APB2Periph_AFIO,ENABLE);
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_GPIOB,ENABLE);
  
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);


	
  TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period = Fsys / Fpwm;		//重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = 0;							//TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM中央对齐模式1计数模式
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分割
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_Pulse = ((Fsys / Fpwm) * 50) / 100;
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  TIM_OCInitStructure.TIM_Pulse = ((Fsys / Fpwm) * 50) / 100;
  TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	


 TIM_BDTR_InitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
 TIM_BDTR_InitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
 TIM_BDTR_InitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
 TIM_BDTR_InitStructure.TIM_DeadTime = 0x15;
 TIM_BDTR_InitStructure.TIM_Break = TIM_Break_Disable;
 TIM_BDTR_InitStructure.TIM_BreakPolarity =TIM_BreakPolarity_High;

  TIM_BDTRConfig(TIM1,&TIM_BDTR_InitStructure);

  TIM_ARRPreloadConfig(TIM1, ENABLE);//ARR预装载缓冲器
  TIM_CtrlPWMOutputs(TIM1, ENABLE);	
	TIM_Cmd(TIM1,ENABLE);	

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;		//SD
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//置低	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	TIM_DMAConfig(TIM1, TIM_DMABase_CCR2, TIM_DMABurstLength_1Byte );  
	TIM_DMACmd(TIM1,TIM_DMA_Update,ENABLE);

	DMA_DeInit(DMA1_Channel5);	//初始化DMA1 第五通道 
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(TIM1_DMAR_Address) ;
  DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)dmabuff;	
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;								//外设作为目的地
  DMA_InitStructure.DMA_BufferSize = 250;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//内存递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	

  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;										//工作模式 DMA_Mode_Normal;//
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel5, ENABLE);


  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;                                                                         //DMA通道1中断允许
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);	//开传输完成中断
}
void SPWMState(FunctionalState NewState)
{
	if(NewState==ENABLE)
		
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//置低		
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_12);	 //置高
}

void shang(INT8U i)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
  TIM_BDTRInitTypeDef TIM_BDTR_InitStructure;
	
	TIM_CtrlPWMOutputs(TIM1, DISABLE);	//关断输出	
	ban();
	if(i==0)
	{
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;			//H桥左壁
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);//置低
		GPIO_SetBits(GPIOB,GPIO_Pin_14);	 //置高
		TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_1Byte );
	}
	if(i==1)
	{
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;			//H桥左壁
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
 		
 		GPIO_ResetBits(GPIOA,GPIO_Pin_8);//置低
 		GPIO_SetBits(GPIOB,GPIO_Pin_13);	 //置高
		TIM_DMAConfig(TIM1, TIM_DMABase_CCR2, TIM_DMABurstLength_1Byte );
	}
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	//关断输出	
	
}

volatile INT8U cishu=0;
void DMA1_Channel5_IRQHandler(void)		//开传输完成中断
{
	OS_CPU_SR  cpu_sr;
	INT32S value=0;
  OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	
	cishu=!cishu;	
	shang(cishu);
  DMA_ClearITPendingBit(DMA1_IT_TC5);
	OS_EXIT_CRITICAL();
}


void spwminit(void)
{
	
	GPIO_InitTypeDef spwm;
	
	Time1Config();

}

