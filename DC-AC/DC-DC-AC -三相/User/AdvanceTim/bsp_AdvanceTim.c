#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"

// spwm波 数据源

const uint16_t indexWave1[] = {
	

0x0,0x2E,0x5D,0x8B,0xB9,0xE7,0x114,0x142,0x16F,0x19B,0x1C7,0x1F3,0x21E,0x249,0x273,0x29C,0x2C4,0x2EC,0x313,0x33A,0x35F,0x383,0x3A7,0x3CA,0x3EB,0x40C,0x42B,0x44A,0x467,0x483,0x49E,0x4B8,0x4D0,0x4E7,0x4FD,0x512,0x525,0x537,0x548,0x557,0x565,0x571,0x57C,0x586,0x58E,0x594,0x599,0x59D,0x59F,
0x5A0,0x59D,0x59D,0x594,0x594,0x586,0x586,0x571,0x571,0x557,0x557,0x537,0x537,0x512,0x512,0x4E7,0x4E7,0x4B8,0x4B8,0x483,0x483,0x44A,0x44A,0x40C,0x40C,0x3CA,0x3CA,0x383,0x383,0x33A,0x33A,0x2EC,0x2EC,0x29C,0x29C,0x249,0x249,0x1F3,0x1F3,0x19B,0x19B,0x142,0x142,0xE7,0xE7,0x8B,0x8B,0x2E,0x0
	
};

const uint16_t indexWave2[] = {
	

0x4E7,0x4FD,0x512,0x525,0x537,0x548,0x557,0x565,0x571,0x57C,0x586,0x58E,0x594,0x599,0x59D,0x59F,
0x5A0,0x59D,0x59D,0x594,0x594,0x586,0x586,0x571,0x571,0x557,0x557,0x537,0x537,0x512,0x512,0x4E7,0x4E7,0x4B8,0x4B8,0x483,0x483,0x44A,0x44A,0x40C,0x40C,0x3CA,0x3CA,0x383,0x383,0x33A,0x33A,0x2EC,0x2EC,0x29C,0x29C,0x249,0x249,0x1F3,0x1F3,0x19B,0x19B,0x142,0x142,0xE7,0xE7,0x8B,0x8B,0x2E,0x0,0x0,0x2E,0x5D,0x8B,0xB9,0xE7,0x114,0x142,0x16F,0x19B,0x1C7,0x1F3,0x21E,0x249,0x273,0x29C,0x2C4,0x2EC,0x313,0x33A,0x35F,0x383,0x3A7,0x3CA,0x3EB,0x40C,0x42B,0x44A,0x467,0x483,0x49E,0x4B8,0x4D0


};

const uint16_t indexWave3[] = {
	


0x4B8,0x4B8,0x483,0x483,0x44A,0x44A,0x40C,0x40C,0x3CA,0x3CA,0x383,0x383,0x33A,0x33A,0x2EC,0x2EC,0x29C,0x29C,0x249,0x249,0x1F3,0x1F3,0x19B,0x19B,0x142,0x142,0xE7,0xE7,0x8B,0x8B,0x2E,0x0,0x0,0x2E,0x5D,0x8B,0xB9,0xE7,0x114,0x142,0x16F,0x19B,0x1C7,0x1F3,0x21E,0x249,0x273,0x29C,0x2C4,0x2EC,0x313,0x33A,0x35F,0x383,0x3A7,0x3CA,0x3EB,0x40C,0x42B,0x44A,0x467,0x483,0x49E,0x4B8,0x4D0,0x4E7,0x4FD,0x512,0x525,0x537,0x548,0x557,0x565,0x571,0x57C,0x586,0x58E,0x594,0x599,0x59D,0x59F,0x5A0,0x59D,0x59D,0x594,0x594,0x586,0x586,0x571,0x571,0x557,0x557,0x537,0x537,0x512,0x512,0x4E7,0x4E7


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
	// 输出比较通道三 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH3_PIN;
	GPIO_Init(ADVANCE_TIM_CH3_PORT, &GPIO_InitStructure);
  // 输出比较通道一  互补通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1N_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1N_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1N_PORT, &GPIO_InitStructure);
	// 输出比较通道二  互补通道 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2N_PIN;
	GPIO_Init(ADVANCE_TIM_CH2N_PORT, &GPIO_InitStructure);
	// 输出比较通道三  互补通道 GPIO 初始化
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH3N_PIN;
	GPIO_Init(ADVANCE_TIM_CH3N_PORT, &GPIO_InitStructure);
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
	// 使能通道三
	TIM_OC3Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);

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
