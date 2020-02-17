#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"

// spwm�� ����Դ
const uint16_t indexWave[] = {
	

512,520,528,536,544,552,560,568,
576,584,591,599,607,615,623,631,
639,646,654,662,669,677,685,692,
700,707,714,722,729,736,743,751,
758,765,772,778,785,792,799,805,
812,818,825,831,837,843,849,855,
861,867,873,878,884,889,895,900,
905,910,915,920,925,930,934,939,
943,947,951,955,959,963,967,970,
974,977,980,984,987,990,992,995,
997,1000,1002,1004,1006,1008,1010,1012,
1013,1015,1016,1017,1018,1019,1020,1021,
1021,1022,1022,1022,1023,1022,1022,1022,
1021,1021,1020,1019,1018,1017,1016,1015,
1013,1012,1010,1008,1006,1004,1002,1000,
997,995,992,990,987,984,980,977,
974,970,967,963,959,955,951,947,
943,939,934,930,925,920,915,910,
905,900,895,889,884,878,873,867,
861,855,849,843,837,831,825,818,
812,805,799,792,785,778,772,765,
758,751,743,736,729,722,714,707,
700,692,685,677,669,662,654,646,
639,631,623,615,607,599,591,584,
576,568,560,552,544,536,528,520,
511,503,495,487,479,471,463,455,
447,439,432,424,416,408,400,392,
384,377,369,361,354,346,338,331,
323,316,309,301,294,287,280,272,
265,258,251,245,238,231,224,218,
211,205,198,192,186,180,174,168,
162,156,150,145,139,134,128,123,
118,113,108,103,98,93,89,84,
80,76,72,68,64,60,56,53,
49,46,43,39,36,33,31,28,
26,23,21,19,17,15,13,11,
10,8,7,6,5,4,3,2,
2,1,1,1,1,1,1,1,
2,2,3,4,5,6,7,8,
10,11,13,15,17,19,21,23,
26,28,31,33,36,39,43,46,
49,53,56,60,64,68,72,76,
80,84,89,93,98,103,108,113,
118,123,128,134,139,145,150,156,
162,168,174,180,186,192,198,205,
211,218,224,231,238,245,251,258,
265,272,280,287,294,301,309,316,
323,331,338,346,354,361,369,377,
384,392,400,408,416,424,432,440,
447,455,463,471,479,487,495,503,

	
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
  // ����Ƚ�ͨ��һ  ����ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1N_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1N_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH1N_PORT, &GPIO_InitStructure);
	// ����Ƚ�ͨ����  ����ͨ�� GPIO ��ʼ��
	GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH2N_PIN;
	GPIO_Init(ADVANCE_TIM_CH2N_PORT, &GPIO_InitStructure);
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

	/*-------------------ɲ���������ṹ���ʼ��-------------------*/
	// �й�ɲ���������ṹ��ĳ�Ա����ɲο�BDTR�Ĵ���������
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	// ����Ƚ��ź�����ʱ�����ã�������μ���ɲο� BDTR:UTG[7:0]������
	// �������õ�����ʱ��Ϊ152ns
	TIM_BDTRInitStructure.TIM_DeadTime = 11;
//  TIM_BDTRInitStructure.TIM_DeadTime = 1;
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
