#ifndef __OUTPUT_H
#define	__OUTPUT_H

#include "stm32f10x.h"

// 控制开关 GPIO						PB5
#define MODE_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define MODE_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define MODE_GPIO_PIN				GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */


// 设置的调整后电压
#define 	VCC_BASE						3
// 电流保护开关					0为关闭	1为开启
#define  	I_PROTECT						1
// 电流保护触发值
#define 	I_PROTECT_VALUE			1.6
// 输入电压采样分频率
#define		input_divide							1
//#define		input_divide							10
// 输出电压采样分频率
#define		output_divide							11
// 采样器分辨率				
#define		accuracy						32768
// 最高电压
#define 	highest_V						5

/* 使用标准的固件库控制IO*/
#define MODE(a)	if (a)	\
					GPIO_SetBits(MODE_GPIO_PORT,MODE_GPIO_PIN);\
					else		\
					GPIO_ResetBits(MODE_GPIO_PORT,MODE_GPIO_PIN)

// 函数声明
void OUTPUT_Init(void);
void Delay(__IO uint32_t nCount);

#endif /* __OUTPUT_H */
