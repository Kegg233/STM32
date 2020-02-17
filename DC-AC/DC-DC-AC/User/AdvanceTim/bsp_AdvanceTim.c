#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"

// spwm波 数据源
const uint16_t indexWave[] = {
	

0x0,0x21,0x41,0x62,0x82,0xA3,0xC3,0xE3,0x102,0x122,0x141,0x15F,0x17E,0x19C,0x1B9,0x1D7,0x1F3,0x20F,0x22B,0x246,0x260,0x27A,0x293,0x2AC,0x2C4,0x2DB,0x2F1,0x307,0x31C,0x330,0x343,0x355,0x367,0x377,0x387,0x396,0x3A4,0x3B1,0x3BD,0x3C8,0x3D2,0x3DB,0x3E3,0x3EB,0x3F1,0x3F6,0x3FA,0x3FD,0x3FF,0x400,
0x400,0x3FF,0x3FD,0x3FA,0x3F6,0x3F1,0x3EB,0x3E3,0x3DB,0x3D2,0x3C8,0x3BD,0x3B1,0x3A4,0x396,0x387,0x377,0x367,0x355,0x343,0x330,0x31C,0x307,0x2F1,0x2DB,0x2C4,0x2AC,0x293,0x27A,0x260,0x246,0x22B,0x20F,0x1F3,0x1D7,0x1B9,0x19C,0x17E,0x15F,0x141,0x122,0x102,0xE3,0xC3,0xA3,0x82,0x62,0x41,0x21,0x0


};

static void ADVANCE_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // 输出比较通道一 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);
	// 输出比较通道二 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2_PIN;
	GPIO_Init(ADVANCE_TIM_CH2_PORT, &GPIO_InitStructure);
  // 输出比较通道一  互补通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1N_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1N_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1N_PORT, &GPIO_InitStructure);
	// 输出比较通道二  互补通道 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2N_PIN;
	GPIO_Init(ADVANCE_TIM_CH2N_PORT, &GPIO_InitStructure);
  // 输出比较通道刹车通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_BKIN_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_BKIN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_BKIN_PORT, &GPIO_InitStructure);
	// BKIN引脚默认先输出低电平
	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);	
}

static void NVIC_Config_PWM(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 配置NVIC为优先级组1   更新中断*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* 配置TIM1_IRQ中断为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ;
	/* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= ADVANCE_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/		
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 互补输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	// 设置占空比大小
	TIM_OCInitStructure.TIM_Pulse = ADVANCE_TIM_PULSE;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// 互补输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// 互补输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	// 使能通道一
	TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
	// 使能通道二
	TIM_OC2Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);

	/*-------------------刹车和死区结构体初始化-------------------*/
	// 有关刹车和死区结构体的成员具体可参考BDTR寄存器的描述
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	// 输出比较信号死区时间配置，具体如何计算可参考 BDTR:UTG[7:0]的描述
	// 这里配置的死区时间为152ns
  TIM_BDTRInitStructure.TIM_DeadTime = 11;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	// 当BKIN引脚检测到高电平的时候，输出比较信号被禁止，就好像是刹车一样
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);
	// 使能计数器
	TIM_Cmd(ADVANCE_TIM, ENABLE);	
	// 主输出使能，当使用的是通用定时器时，这句不需要
	TIM_CtrlPWMOutputs(ADVANCE_TIM, ENABLE);
	//使能update中断
	TIM_ITConfig(ADVANCE_TIM, TIM_IT_Update, ENABLE);										
	// 配置中断优先级
	NVIC_Config_PWM();		
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();		
}

/*********************************************END OF FILE**********************/
