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
// ���ڣ�OLED��ʾ��ʱ��
uint32_t see = 0;
// sprintf ���ɵ��ַ���
char a[25];
char b[25];

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
		Delay(0x000fff); 
		// ��ȡͨ��һ����ֵ
		adc_v = AD7606_RESULT();
		// ת���ɵ�ѹֵ
		ADC_V = (float)adc_v*5/32768;
		// ��ȡͨ��������ֵ
		adc_i = AD7606_RESULT();
		// ת���ɵ���ֵ
		adc_i = (float)adc_i/32768*5;
		ADC_I = (adc_i-2.5)/0.255;
		// ��CS���ɸߵ�ƽ���ر�16λ������
		CS(1);
		// PID �㷨 P ���������һ��ʱ�̵�ռ�ձ�
		vcc_zkb_base = vcc_zkb_base+( ADC_V - VCC_BASE)*0.5-0.001;
		// ����ֵ���׼ֵ�Աȣ���ֹ����100��С��0
		if(vcc_zkb_base > 100){
			vcc_zkb_base = 100;
		}else if(vcc_zkb_base < 0 ){
			vcc_zkb_base = 0;
		}
		// �����������ʹ�ܵĻ��� ���������ر�ϵͳ
		if(I_PROTECT){
			if(ADC_I > I_PROTECT_VALUE){
				TIM_SetCompare3(TIM3,100);
				OLED_ShowString(0,3,"over I protect");
				printf("\r\n ����������%f V\r\n",ADC_I);
				break;
			}
		}
		// ����PWMռ�ձ�
		TIM_SetCompare3(TIM3,vcc_zkb_base);
		// ��һ��ʱ����������ں���ʾ����
		see++;
		if(see > 0xeee){
			see = 0;
			// ��sprintf�������Ѹ�����ת�����ַ�����OLED�������
			sprintf(a, "V = %f V", ADC_V);
			sprintf(b, "I = %f A", ADC_I);
			OLED_ShowString(0,0,a);
			OLED_ShowString(0,3,b);
			printf("��ѹ��%f V\r\n",ADC_V);
			printf("������%f V\r\n",ADC_I);
			printf("ռ�ձȣ� %f %% \r\n",vcc_zkb_base);
		}
		// �ȴ�ռ�ձȵ�����ɲ����ú󣬽�����һ������ѭ��
		Delay(0x000fff); 
	}
}

