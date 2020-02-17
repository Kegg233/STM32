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
// 串口，OLED显示计时器
uint32_t see = 0;
// sprintf 生成的字符串
char a[25];
char b[25];

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
		Delay(0x000fff); 
		// 读取通道一的数值
		adc_v = AD7606_RESULT();
		// 转换成电压值
		ADC_V = (float)adc_v*5/32768;
		// 读取通道二的数值
		adc_i = AD7606_RESULT();
		// 转换成电流值
		adc_i = (float)adc_i/32768*5;
		ADC_I = (adc_i-2.5)/0.255;
		// 把CS调成高电平，关闭16位采样器
		CS(1);
		// PID 算法 P ，计算出下一个时刻的占空比
		vcc_zkb_base = vcc_zkb_base+( ADC_V - VCC_BASE)*0.5-0.001;
		// 采样值与基准值对比，防止超过100或小于0
		if(vcc_zkb_base > 100){
			vcc_zkb_base = 100;
		}else if(vcc_zkb_base < 0 ){
			vcc_zkb_base = 0;
		}
		// 如果电流保护使能的话， 启动过流关闭系统
		if(I_PROTECT){
			if(ADC_I > I_PROTECT_VALUE){
				TIM_SetCompare3(TIM3,100);
				OLED_ShowString(0,3,"over I protect");
				printf("\r\n 过流保护：%f V\r\n",ADC_I);
				break;
			}
		}
		// 调整PWM占空比
		TIM_SetCompare3(TIM3,vcc_zkb_base);
		// 隔一段时间输出到串口和显示屏上
		see++;
		if(see > 0xeee){
			see = 0;
			// 用sprintf函数，把浮点型转换成字符串，OLED才能输出
			sprintf(a, "V = %f V", ADC_V);
			sprintf(b, "I = %f A", ADC_I);
			OLED_ShowString(0,0,a);
			OLED_ShowString(0,3,b);
			printf("电压：%f V\r\n",ADC_V);
			printf("电流：%f V\r\n",ADC_I);
			printf("占空比： %f %% \r\n",vcc_zkb_base);
		}
		// 等待占空比调整完成并作用后，进行下一个采样循环
		Delay(0x000fff); 
	}
}

