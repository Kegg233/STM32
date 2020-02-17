#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"  
#include "bsp_exti.h"
#include "./SysTick/bsp_SysTick.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
// 局部变量，用于保存转换计算后的电压值 	 
float ADC[NOFCHANEL];  
// 屏幕输出
char aa[20],bb[20];
// 基准电压
float adc_base = 24;
// 电压显示时间
uint32_t see = 0;
// 标志位
int flag = 0 ;
int flag_wykg = 0;
int flag_glbh = 0;
// boost控制占空比
int boost_zkb = 7200;
// 逆变控制频率
int bn_pl = 12;


// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

// 主函数
int main(void)
{	
	// 延时初始化
	SysTick_Init();
	// 测试灯
	LED_GPIO_Config();
	// 初始化DC - DC 控制的pwm
	GENERAL_TIM_Init();
	// 初始化互补PWM输出
	ADVANCE_TIM_Init();
	// 配置串口
	USART_Config();
	// ADC 初始化
	ADCx_Init();
	// 改变预分频系数
	TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
	// 改变占空比
	TIM_SetCompare1(TIM3,boost_zkb);
	while (1)
	{
		ADC[0] =(float) ADC_ConvertedValue[0]/4096*3.3; // 读取转换的AD值
		ADC[1] =(float) ADC_ConvertedValue[1]/4096*3.3; // 读取转换的AD值
		if(ADC[0] > 3){
			flag_glbh = 1;
		}else{
			flag_glbh = 0;
		}
		// 减小boost占空比		
		if(flag == 1 && flag_wykg == 0 && flag_glbh == 0){
			flag = 0;
			if(boost_zkb > 72){
					boost_zkb = boost_zkb - 72;
					// 改变占空比
					TIM_SetCompare1(TIM3,boost_zkb);
				}else {
					boost_zkb = 72;
					TIM_SetCompare1(TIM3,boost_zkb);
				}
			// 输出到串口屏
				sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
				printf(aa);
				Usart_SendByte(DEBUG_USARTx,0xff);
				Usart_SendByte(DEBUG_USARTx,0xff);
				Usart_SendByte(DEBUG_USARTx,0xff);
			}
		// 增大boost占空比
		if(flag == 2 && flag_wykg == 0 && flag_glbh == 0){
			flag = 0;
			if(boost_zkb < 10080){
				boost_zkb = boost_zkb + 72;
				TIM_SetCompare1(TIM3,boost_zkb);
			}else {
				boost_zkb = 10080;
				TIM_SetCompare1(TIM3,boost_zkb);
			}
			// 输出到串口屏
			sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
			
		// 稳压开
		if(flag == 3 && flag_glbh == 0){
			flag = 0;
			flag_wykg = 1;
			printf("boost.t4.txt=\"稳压状态\"");
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// 稳压关
		if(flag == 4 && flag_glbh == 0){
			flag = 0;
			flag_wykg = 0;
			boost_zkb = 7200;
			TIM_SetCompare1(TIM3,boost_zkb);
			sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// 增大稳压电压
		if(flag == 5){
			flag = 0;
			adc_base = adc_base + 0.5 ;
			sprintf(aa,"wy.t2.txt=\"%.1f\"",adc_base);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// 减小稳压电压
		if(flag == 6){
			flag = 0;
			adc_base = adc_base - 0.5 ;
			sprintf(aa,"wy.t2.txt=\"%.1f\"",adc_base);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}	
		
		// 减小逆变频率
		if(flag == 7 && flag_glbh == 0){
			flag = 0;
				if(bn_pl < 30){
				bn_pl++;
				// 改变预分频系数
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}else {
				bn_pl = 30;
				// 改变预分频系数
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}
		}		
			
		// 增大逆变频率
		if(flag == 8 && flag_glbh == 0){
			flag = 0;
			if(bn_pl > 1){
				bn_pl--;
				// 改变预分频系数
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}else {
				bn_pl = 1;
				// 改变预分频系数
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}
		}		

		if( flag_wykg == 1 && flag_glbh == 0){
			// PID 算法 P ，计算出下一个时刻的占空比
			boost_zkb = boost_zkb+( adc_base - ADC[1]*10.83)*3000;
			if(boost_zkb > 10080){
				boost_zkb = 10080;
			}else if(boost_zkb < 72 ){
				boost_zkb = 72;
			}
			TIM_SetCompare1(TIM3,boost_zkb);
		}	
		// 过流保护
		if( flag_glbh == 1){
			TIM_SetCompare1(TIM3,0);
		}
		
		// 电压显示
		see++;
		if(see > 0xffff){
			see = 0;
			sprintf(bb,"boost.t2.txt=\"%.3f\"",(float)ADC[1]*11.05);
			printf(bb);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}			
	}
}
/*********************************************END OF FILE**********************/

