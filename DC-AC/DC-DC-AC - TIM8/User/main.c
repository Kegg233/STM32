#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"  
#include "bsp_exti.h"

//// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
//extern __IO uint16_t ADC_ConvertedValue;

//// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
//float ADC_ConvertedValueLocal;        

//// �����ʱ
//void Delay(__IO uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//} 

// ������
int main(void)
{	
//	// ��ť �жϳ�ʼ��
//	EXTI_Key_Config();
//	// ���Ե�
//	LED_GPIO_Config();
//	// ��ʼ��DC - DC ���Ƶ�pwm
//	GENERAL_TIM_Init();
	// ��ʼ������PWM���
	ADVANCE_TIM_Init();
//	// ���ô���
//	USART_Config();
//	// ADC ��ʼ��
//	ADCx_Init();
//	// �ı�Ԥ��Ƶϵ��
//	TIM_PrescalerConfig(TIM1,14,TIM_PSCReloadMode_Immediate);
//	// �ı�ռ�ձ�
//	TIM_SetCompare1(TIM3,50);
	float target_value = 3;
	float difference_value = 0;
	int Compare_value = 50;
	while (1)
	{
//		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
//		difference_value = target_value - ADC_ConvertedValueLocal;
//		Compare_value = (int)(Compare_value+difference_value);
		
//		if(Compare_value > 95){
//			Compare_value = 95;
//		}else if(Compare_value < 20){
//			Compare_value = 20;
//		}
//		TIM_SetCompare1(TIM3,Compare_value);
		
//		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
//		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
//		printf("\r\n The Compare_value = %d V \r\n",Compare_value); 
//		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/

