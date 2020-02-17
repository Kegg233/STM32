#include "./voltage_output/voltage_output.h"
#include "./sram/sram.h"
#include "./bsp_GeneralTim.h" 
#include "./OLED/oled.h"
#include <stdio.h>
#include "stdlib.h"

// ������ѹֵ
float adc_v = 0;
// �����ѹֵ
float ADC_V = 0;
// ����ռ�ձ�
float vcc_zkb_base = 50;
// ��������ֵ
float adc_i = 0;
// �����ĵ���ֵ
float ADC_I = 0;
// ����Դ��ѹ
float mode_value = 0;
// ����Դ��ѹ
float Mode_value = 0;
// ����ѹѡ��
int Mode = 0;
int old_Mode = 0;
// ���ڣ�OLED��ʾ��ʱ��
uint32_t see = 0;
uint32_t change = 0;
// sprintf ���ɵ��ַ���
char a[25];
char b[25];
char C[25];
char D[25];

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

// �����ʼ������
void OUTPUT_Init(void)
{
	// ��CS���ɵ͵�ƽ��ʹ��16λ������
	CS(0);
	// ��λ������
	AD7606_Reset();
	// ��ѭ��
	while(1){
		// ��CS���ɵ͵�ƽ��ʹ��16λ������
		CS(0);
		// ��λ������
		AD7606_Reset();
		// �ӳٵȴ���λ���
		Delay(0x00ffff); 
		// ��ȡͨ��һ����ֵ
		adc_v = AD7606_RESULT();
//		// ��ȡͨ��������ֵ
//		adc_i = AD7606_RESULT();
//		// ��ȡͨ��������ֵ
//		mode_value = AD7606_RESULT();
//		// ��CS���ɸߵ�ƽ���ر�16λ������
		CS(1);
		// ת���������ѹֵ
		ADC_V = (float)(adc_v/accuracy*highest_V*output_divide);
//		// ת���ɵ���ֵ
//		adc_i = (float)(adc_i/accuracy*highest_V);
//		ADC_I = (adc_i-2.5)/0.255;
//		// ת���������ѹֵ
//		Mode_value = (float)(mode_value/accuracy*highest_V*input_divide);

			// PID �㷨 P ���������һ��ʱ�̵�ռ�ձ�
			vcc_zkb_base = vcc_zkb_base+(  VCC_BASE - ADC_V )*50;
			// ����ֵ���׼ֵ�Աȣ���ֹ����100��С��0
			if(vcc_zkb_base > 3600){
				vcc_zkb_base = 3600;
			}else if(vcc_zkb_base < 360 ){
				vcc_zkb_base = 360;
			}
//			// �����������ʹ�ܵĻ��� ���������ر�ϵͳ
//			if(I_PROTECT){
//				if(ADC_I > I_PROTECT_VALUE){
//					TIM_SetCompare3(TIM3,0);
//					OLED_Clear(); 
//					OLED_ShowString(0,3,"over I protect");
//					printf("\r\n ����������%f V\r\n",ADC_I);
//					break;
//				}
//			}
			// ����PWMռ�ձ�
			TIM_SetCompare3(TIM3,vcc_zkb_base);
			// ��һ��ʱ����������ں���ʾ����
			see++;
			if(see > 0xee){
				OLED_Clear(); 
				see = 0;
				// ��sprintf�������Ѹ�����ת�����ַ�����OLED�������
				sprintf(a, "V = %fV", ADC_V);
//				sprintf(b, "I = %fA", ADC_I);
//				sprintf(C, "OV = %fV", Mode_value);
				sprintf(D, "ZKB =%f%%", vcc_zkb_base/72);
				OLED_ShowString(0,0,a);
//				OLED_ShowString(0,2,b);
//				OLED_ShowString(0,4,C);
				OLED_ShowString(0,6,D);
				printf("��ѹ��%f V\r\n",ADC_V);
//				printf("������%f A\r\n",ADC_I);
//				printf("�ⲿ��ѹ��%f V\r\n",Mode_value);
				printf("ռ�ձȣ�%f %% \r\n",vcc_zkb_base/72);
				printf("\r\n");
			}
			// �ȴ�ռ�ձȵ�����ɲ����ú󣬽�����һ������ѭ��
			Delay(0x000fff); 
	}
}

