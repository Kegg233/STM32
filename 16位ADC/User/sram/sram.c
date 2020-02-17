#include "./sram/sram.h"	  

/**
   ��ʼ������SRAM��IO
*/

int16_t Data[7] = {1,1,1,1,1,1,1};

static void SRAM_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 
  /* ʹ��SRAM��ص�GPIOʱ�� */
                  
  RCC_APB2PeriphClockCmd(
                         /*�����ź���*/
                         FSMC_D0_GPIO_CLK | FSMC_D1_GPIO_CLK | FSMC_D2_GPIO_CLK | 
                         FSMC_D3_GPIO_CLK | FSMC_D4_GPIO_CLK | FSMC_D5_GPIO_CLK |
                         FSMC_D6_GPIO_CLK | FSMC_D7_GPIO_CLK | FSMC_D8_GPIO_CLK |
                         FSMC_D9_GPIO_CLK | FSMC_D10_GPIO_CLK| FSMC_D11_GPIO_CLK|
                         FSMC_D12_GPIO_CLK| FSMC_D13_GPIO_CLK| FSMC_D14_GPIO_CLK|
                         FSMC_D15_GPIO_CLK|  
                         /*�����ź���*/
                         FSMC_OE_GPIO_CLK | FSMC_RST_GPIO_CLK | FSMC_CS_GPIO_CLK , ENABLE);
												 
	 /*-- GPIO ���� -----------------------------------------------------*/

  /* ͨ�� GPIO ���� */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //����Ϊ���ù���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
    
  /*DQ�����ź��� �����������*/
  GPIO_InitStructure.GPIO_Pin = FSMC_D0_GPIO_PIN; 
  GPIO_Init(FSMC_D0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D1_GPIO_PIN; 
  GPIO_Init(FSMC_D1_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = FSMC_D2_GPIO_PIN; 
  GPIO_Init(FSMC_D2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D3_GPIO_PIN; 
  GPIO_Init(FSMC_D3_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D4_GPIO_PIN; 
  GPIO_Init(FSMC_D4_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D5_GPIO_PIN; 
  GPIO_Init(FSMC_D5_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D6_GPIO_PIN; 
  GPIO_Init(FSMC_D6_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D7_GPIO_PIN; 
  GPIO_Init(FSMC_D7_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D8_GPIO_PIN; 
  GPIO_Init(FSMC_D8_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D9_GPIO_PIN; 
  GPIO_Init(FSMC_D9_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D10_GPIO_PIN; 
  GPIO_Init(FSMC_D10_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D11_GPIO_PIN; 
  GPIO_Init(FSMC_D11_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D12_GPIO_PIN; 
  GPIO_Init(FSMC_D12_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D13_GPIO_PIN; 
  GPIO_Init(FSMC_D13_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D14_GPIO_PIN; 
  GPIO_Init(FSMC_D14_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D15_GPIO_PIN; 
  GPIO_Init(FSMC_D15_GPIO_PORT, &GPIO_InitStructure);
  
  /*���ź���*/
  GPIO_InitStructure.GPIO_Pin = FSMC_OE_GPIO_PIN; 
  GPIO_Init(FSMC_OE_GPIO_PORT, &GPIO_InitStructure);  
	
  /*��λ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = FSMC_RST_GPIO_PIN; 
  GPIO_Init(FSMC_RST_GPIO_PORT, &GPIO_InitStructure);  
	
	/*Ƭѡ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = FSMC_CS_GPIO_PIN; 
  GPIO_Init(FSMC_CS_GPIO_PORT, &GPIO_InitStructure);  
	
}				  			


/**
  * @brief  ��ʼ��FSMC����
  */
void FSMC_SRAM_Init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

	/*��ʼ��SRAM��ص�GPIO*/
	SRAM_GPIO_Config();
		
	/*ʹ��FSMC����ʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK 1/72M=14ns
	readWriteTiming.FSMC_AddressSetupTime = 0x03;	

	//��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

	//���ݱ���ʱ�䣨DATAST��+ 1��HCLK = 3/72M=42ns(��EM��SRAMоƬ)	
	readWriteTiming.FSMC_DataSetupTime = 0x06;		  
	
	//��������ת�����ڣ������ڸ���ģʽ��NOR����
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x01;
	
	//����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
	readWriteTiming.FSMC_CLKDivision = 0x00;	

	//���ݱ���ʱ�䣬������ͬ���͵�NOR
	readWriteTiming.FSMC_DataLatency = 0x00;		
	
	//ѡ��ƥ��SRAM��ģʽ
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 
    
	// ѡ��FSMCӳ��Ĵ洢���� Bank1 sram3
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	
	//���õ�ַ���������������Ƿ��ã�������NOR
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	
	//����Ҫ���ƵĴ洢�����ͣ�SRAM����
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
	
	//�洢�����ݿ�ȣ�16λ
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
	
	//�����Ƿ�ʹ��ͻ������ģʽ��������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
	
	//�����Ƿ�ʹ�ܵȴ��źţ�������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	
	//���õȴ��źŵ���Ч���ԣ�������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	
	//�����Ƿ�֧�ְѷǶ����ͻ��������������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
	
	//���õȴ��źŲ����ʱ�䣬������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	
	//�洢��дʹ�� 
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	
	//��ʹ�õȴ��ź�
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
	
	// ��ʹ����չģʽ����дʹ����ͬ��ʱ��
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
	
	//ͻ��д����
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	
	//��дʱ������
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	
	//��дͬ��ʱ��ʹ����չģʽʱ������ò���Ч
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  // ʹ��BANK										  								
}


void AD7606_Reset(void)
{
	RESET(0);	/* �˳���λ״̬ */
	RESET(1);
	RESET(1);
	RESET(1);
	RESET(1);
	RESET(1);
	RESET(1);
	RESET(0);	/* �˳���λ״̬ */
}
/*********************************************END OF FILE**********************/





