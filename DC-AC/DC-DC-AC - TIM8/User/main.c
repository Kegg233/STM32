#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"  
#include "bsp_exti.h"

//// ADC1转换的电压值通过MDA方式传到SRAM
//extern __IO uint16_t ADC_ConvertedValue;

//// 局部变量，用于保存转换计算后的电压值 	 
//float ADC_ConvertedValueLocal;        

//// 软件延时
//void Delay(__IO uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//} 

// 主函数
int main(void)
{	
//	// 按钮 中断初始化
//	EXTI_Key_Config();
//	// 测试灯
//	LED_GPIO_Config();
//	// 初始化DC - DC 控制的pwm
//	GENERAL_TIM_Init();
	// 初始化互补PWM输出
	ADVANCE_TIM_Init();
//	// 配置串口
//	USART_Config();
//	// ADC 初始化
//	ADCx_Init();
//	// 改变预分频系数
//	TIM_PrescalerConfig(TIM1,14,TIM_PSCReloadMode_Immediate);
//	// 改变占空比
//	TIM_SetCompare1(TIM3,50);
	float target_value = 3;
	float difference_value = 0;
	int Compare_value = 50;
	while (1)
	{
//		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
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

