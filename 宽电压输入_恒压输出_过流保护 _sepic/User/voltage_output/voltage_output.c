#include "./voltage_output/voltage_output.h"
#include "./sram/sram.h"
#include "./bsp_GeneralTim.h" 
#include "./OLED/oled.h"
#include <stdio.h>
#include "stdlib.h"

// 采样电压值
float adc_v = 0;
// 换算电压值
float ADC_V = 0;
// 调整占空比
float vcc_zkb_base = 50;
// 采样电流值
float adc_i = 0;
// 换算后的电流值
float ADC_I = 0;
// 采样源电压
float mode_value = 0;
// 换算源电压
float Mode_value = 0;
// 升降压选择
int Mode = 0;
int old_Mode = 0;
// 串口，OLED显示计时器
uint32_t see = 0;
uint32_t change = 0;
// sprintf 生成的字符串
char a[25];
char b[25];
char C[25];
char D[25];

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

// 输出初始化函数
void OUTPUT_Init(void)
{
	// 把CS调成低电平，使能16位采样器
	CS(0);
	// 复位采样器
	AD7606_Reset();
	// 主循环
	while(1){
		// 把CS调成低电平，使能16位采样器
		CS(0);
		// 复位采样器
		AD7606_Reset();
		// 延迟等待复位完成
		Delay(0x00ffff); 
		// 读取通道一的数值
		adc_v = AD7606_RESULT();
//		// 读取通道二的数值
//		adc_i = AD7606_RESULT();
//		// 读取通道三的数值
//		mode_value = AD7606_RESULT();
//		// 把CS调成高电平，关闭16位采样器
		CS(1);
		// 转换成输出电压值
		ADC_V = (float)(adc_v/accuracy*highest_V*output_divide);
//		// 转换成电流值
//		adc_i = (float)(adc_i/accuracy*highest_V);
//		ADC_I = (adc_i-2.5)/0.255;
//		// 转换成输入电压值
//		Mode_value = (float)(mode_value/accuracy*highest_V*input_divide);

			// PID 算法 P ，计算出下一个时刻的占空比
			vcc_zkb_base = vcc_zkb_base+(  VCC_BASE - ADC_V )*50;
			// 采样值与基准值对比，防止超过100或小于0
			if(vcc_zkb_base > 3600){
				vcc_zkb_base = 3600;
			}else if(vcc_zkb_base < 360 ){
				vcc_zkb_base = 360;
			}
//			// 如果电流保护使能的话， 启动过流关闭系统
//			if(I_PROTECT){
//				if(ADC_I > I_PROTECT_VALUE){
//					TIM_SetCompare3(TIM3,0);
//					OLED_Clear(); 
//					OLED_ShowString(0,3,"over I protect");
//					printf("\r\n 过流保护：%f V\r\n",ADC_I);
//					break;
//				}
//			}
			// 调整PWM占空比
			TIM_SetCompare3(TIM3,vcc_zkb_base);
			// 隔一段时间输出到串口和显示屏上
			see++;
			if(see > 0xee){
				OLED_Clear(); 
				see = 0;
				// 用sprintf函数，把浮点型转换成字符串，OLED才能输出
				sprintf(a, "V = %fV", ADC_V);
//				sprintf(b, "I = %fA", ADC_I);
//				sprintf(C, "OV = %fV", Mode_value);
				sprintf(D, "ZKB =%f%%", vcc_zkb_base/72);
				OLED_ShowString(0,0,a);
//				OLED_ShowString(0,2,b);
//				OLED_ShowString(0,4,C);
				OLED_ShowString(0,6,D);
				printf("电压：%f V\r\n",ADC_V);
//				printf("电流：%f A\r\n",ADC_I);
//				printf("外部电压：%f V\r\n",Mode_value);
				printf("占空比：%f %% \r\n",vcc_zkb_base/72);
				printf("\r\n");
			}
			// 等待占空比调整完成并作用后，进行下一个采样循环
			Delay(0x000fff); 
	}
}

