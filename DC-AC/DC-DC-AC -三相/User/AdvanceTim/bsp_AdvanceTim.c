#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"

// spwm�� ����Դ

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
  // ����Ƚ�ͨ��һ GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);
	// ����Ƚ�ͨ���� GPIO ��ʼ��
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2_PIN;
	GPIO_Init(ADVANCE_TIM_CH2_PORT, &GPIO_InitStructure);
	// ����Ƚ�ͨ���� GPIO ��ʼ��
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH3_PIN;
	GPIO_Init(ADVANCE_TIM_CH3_PORT, &GPIO_InitStructure);
  // ����Ƚ�ͨ��һ  ����ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1N_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1N_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1N_PORT, &GPIO_InitStructure);
	// ����Ƚ�ͨ����  ����ͨ�� GPIO ��ʼ��
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2N_PIN;
	GPIO_Init(ADVANCE_TIM_CH2N_PORT, &GPIO_InitStructure);
	// ����Ƚ�ͨ����  ����ͨ�� GPIO ��ʼ��
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH3N_PIN;
	GPIO_Init(ADVANCE_TIM_CH3N_PORT, &GPIO_InitStructure);
  // ����Ƚ�ͨ��ɲ��ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_BKIN_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_BKIN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_BKIN_PORT, &GPIO_InitStructure);
	// BKIN����Ĭ��������͵�ƽ
	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);	
}

static void NVIC_Config_PWM(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* ����NVICΪ���ȼ���1   �����ж�*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* ����TIM1_IRQ�ж�Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ;
	/* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_PERIOD;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= ADVANCE_TIM_PSC;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/		
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// �������ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	// ����ռ�ձȴ�С
	TIM_OCInitStructure.TIM_Pulse = ADVANCE_TIM_PULSE;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// �������ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// �������ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	// ʹ��ͨ��һ
	TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
	// ʹ��ͨ����
	TIM_OC2Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
	// ʹ��ͨ����
	TIM_OC3Init(ADVANCE_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);

	/*-------------------ɲ���������ṹ���ʼ��-------------------*/
	// �й�ɲ���������ṹ��ĳ�Ա����ɲο�BDTR�Ĵ���������
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	// ����Ƚ��ź�����ʱ�����ã�������μ���ɲο� BDTR:UTG[7:0]������
	// �������õ�����ʱ��Ϊ152ns
  TIM_BDTRInitStructure.TIM_DeadTime = 11;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	// ��BKIN���ż�⵽�ߵ�ƽ��ʱ������Ƚ��źű���ֹ���ͺ�����ɲ��һ��
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);
	// ʹ�ܼ�����
	TIM_Cmd(ADVANCE_TIM, ENABLE);	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	TIM_CtrlPWMOutputs(ADVANCE_TIM, ENABLE);
	//ʹ��update�ж�
	TIM_ITConfig(ADVANCE_TIM, TIM_IT_Update, ENABLE);										
	// �����ж����ȼ�
	NVIC_Config_PWM();		
}

void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();		
}

/*********************************************END OF FILE**********************/
