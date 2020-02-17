#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"  
#include "bsp_exti.h"
#include "./SysTick/bsp_SysTick.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;        

// ������ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

// ������
int main(void)
{	
	// ��ʱ��ʼ��
	SysTick_Init();
	// ��ť �жϳ�ʼ��
	EXTI_Key_Config();
	// ���Ե�
	LED_GPIO_Config();
	// ��ʼ��DC - DC ���Ƶ�pwm
	GENERAL_TIM_Init();
	// ��ʼ������PWM���
	ADVANCE_TIM_Init();
	// ���ô���
	USART_Config();
	// ADC ��ʼ��
	ADCx_Init();
//	// �ı�Ԥ��Ƶϵ��
//	TIM_PrescalerConfig(TIM1,14,TIM_PSCReloadMode_Immediate);
//	// �ı�ռ�ձ�
//	TIM_SetCompare1(TIM3,50);
	float target_value = 3;
	float difference_value = 0;
	int Compare_value = 50;
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
		difference_value = target_value - ADC_ConvertedValueLocal;
		Compare_value = (int)(Compare_value+difference_value);
		
	}
}
/*********************************************END OF FILE**********************/
