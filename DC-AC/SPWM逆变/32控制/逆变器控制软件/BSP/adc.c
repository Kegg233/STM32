#include "stm32f10x.h"
#include "includes.h"
#include "stm32f10x_conf.h" 

vu16  AD_Value[10][8];   //�������ADCת�������Ҳ��DMA��Ŀ���ַ

/*����ADC1*/
void ADC1_Configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);        //ʹ��DMA����
	
	//PA0/1/2 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode =ENABLE;        				//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   //�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 8;        						//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);        								//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	ADC_TempSensorVrefintCmd(ENABLE );	//�����¶� ��׼����
	/* ADC1 regular channel11 configuration */ 
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5 );	//�¶�
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 2, ADC_SampleTime_239Cycles5 );	//��׼
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_239Cycles5 );                
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_239Cycles5 );        
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime_239Cycles5 );

	ADC_Cmd(ADC1, ENABLE);	
	ADC_ResetCalibration(ADC1); 									//����ADC1У׼�Ĵ��� 	
	while(ADC_GetResetCalibrationStatus(ADC1));  	//�ȴ�ADC1У׼�������	
	ADC_StartCalibration(ADC1); 									//��ʼADC1У׼	
	while(ADC_GetCalibrationStatus(ADC1)); 				//�ȴ�ADC1У׼���	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 			//ʹ��ADC1�����ʼת��

	ADC_DMACmd(ADC1, ENABLE);  										// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
  /* ADC1  DMA1 Channel Config */	
	DMA_DeInit(DMA1_Channel1);   																  //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&ADC1->DR;   //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  		  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  				  //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = 10*8;  										  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  			//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  							//������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 					//DMAͨ�� xӵ�и����ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  								//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  								//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

  DMA_Cmd(DMA1_Channel1, ENABLE);         //����DMAͨ��
}

volatile FP32 k_adc=0;
void Getk_adc(void)
{
	INT16S i=0;
	INT32U temp=0;
	for(i=0;i<10;i++)
		temp=temp+AD_Value[i][1];
	k_adc=1.2/(temp/10);
}
FP32 GetTemp(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 wendu=0;
	for(i=0;i<10;i++)
	
		temp=temp+AD_Value[i][0];	
	
	temp=temp/10;
	Getk_adc();
	wendu=25 + (1.43 - temp*k_adc)/0.0043;
	return wendu;	
}

const FP32 k_bate=0.163;
FP32 GetBATE(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 vol=0;
	for(i=0;i<10;i++)	
		temp=temp+AD_Value[i][2];	
	temp=temp/10;
	Getk_adc();
	vol=temp*k_adc/k_bate;
	return vol;
}
const FP32 k_dc310=0.00685431;
FP32 GetDC310(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 vol=0;
	for(i=0;i<10;i++)	
		temp=temp+AD_Value[i][5];	
	temp=temp/10;
	Getk_adc();
	vol=temp*k_adc/k_dc310;

	return vol;
}


//-20�� ---- 100��
const FP32 NTC_TABLE[120]=
{

92.65,87.54,82.73,78.22,73.98,69.99,66.24,62.71,59.39,56.26,
53.31,50.54,47.92,45.46,43.14,40.94,38.87,36.92,35.08,33.33,
32.69,30.13,28.66,27.27,25.95,24.71,23.53,22.41,21.35,20.35,
19.40,18.50,17.65,16.84,16.07,15.34,14.65,13.99,13.37,12.77,
12.21,11.67,11.16,10.68,10.22,9.78,9.36,8.96,8.58,8.22,
7.88,7.55,7.24,6.94,6.66,6.39,6.13,5.88,5.65,5.42,
5.21,5.00,4.80,4.62,4.44,4.27,4.10,3.95,3.80,3.65,
3.51,3.38,3.26,3.14,3.02,2.91,2.80,2.70,2.60,2.51,
2.42,2.33,2.25,2.17,2.10,2.02,1.95,1.89,1.82,1.76,
1.70,1.64,1.59,1.53,1.48,1.43,1.39,1.34,1.30,1.25,
1.21,1.17,1.14,1.10,1.07,1.03,1.00,0.97,0.94,0.91,
0.88,0.85,0.83,0.80,0.78,0.75,0.73,0.71,0.69,0.67,
};


#include "math.h"
static float x_est_last1 = 0; 
static float P_last1 = 0; 
/*/the noise in the system */
static float Q1 = 0.5; 
static float R1 = 0.8; 
 
static float K1; 
static float P1; 
static float P_temp1; 
static float x_temp_est1; 
static float x_est1; 
static float z_measured1; /*/the 'noisy' value we measured  */
//   float z_real = 0.5; /*/the ideal value we wish to measure */
static float sum_error_kalman1 = 0; 
static float sum_error_measure1 = 0;

static float kalman1(float z_real) 
{ 		
	/*/do a prediction */
	x_temp_est1 = x_est_last1; 
	P_temp1 = P_last1 + Q1; 
	/*/calculate the Kalman gain */
	K1 = P_temp1 * (1.0/(P_temp1 + R1)); 
	/*/measure*/
	z_measured1 = z_real ;
	x_est1 = x_temp_est1 + K1 * (z_measured1 - x_temp_est1);  
	P1 = (1- K1) * P_temp1; 	 
	sum_error_kalman1 += fabs(z_real - x_est1); 
	sum_error_measure1 += fabs(z_real-z_measured1); 
	P_last1 = P1; 
	x_est_last1 = x_est1; 

	return x_est1; 
}


FP32 GetWenDu(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 vol=0,j=0; 
	for(i=0;i<10;i++)	
		temp=temp+AD_Value[i][4];
	temp=temp/10;
	
	vol=10.0/(4096.0/temp-1);
	
	while(1)
	{
		if(NTC_TABLE[i]<vol)
			break;
		else
			i++;
		if(i==119)
			return 100;
	}		
	vol=(i-20)+(NTC_TABLE[i-1]-vol)*1.0/(NTC_TABLE[i-1]-NTC_TABLE[i]);
	vol=kalman1(vol);
	return vol;
}
FP32 electric_zero=0.07;	//��ѹ��� 
FP32 GetElectric(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 vol=0,j=0; 
	for(i=0;i<10;i++)	
		temp=temp+AD_Value[i][3];
	temp=temp/10;	
	vol=temp*k_adc-electric_zero;	
	vol=vol/10/0.005;
	return vol;
}

void Getele(void)
{
	INT16S i=0;
	INT32U temp=0;
	FP32 vol=0,j=0; 
	for(i=0;i<10;i++)	
		temp=temp+AD_Value[i][3];
	temp=temp/10;	
	
	electric_zero=temp*k_adc;	
}


void SaveCanShu(void)
{
	FLASH_Unlock();
  EE_Init();
	
	DoubleWrite(0,electric_zero);
	FLASH_Lock();
}

void ReadCanShu(void)
{
	DoubleRead(0,&electric_zero);
}
//��������ʼ��
void DianLiuInit(void)
{
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	

	
	led.GPIO_Speed=GPIO_Speed_50MHz;
	led.GPIO_Mode=GPIO_Mode_IPU;
	
	led.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOA,&led);
	
}

/*************************************************
*
*	�񰴼�״̬
*
**************************************************/
INT8U GetAnJian(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
}


