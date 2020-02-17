#ifndef __OUTPUT_H
#define	__OUTPUT_H

#include "stm32f10x.h"

// 设置的调整后电压
#define 	VCC_BASE						10
// 电流保护开关					0为关闭	1为开启
#define  	I_PROTECT						0
// 电流保护触发值
#define 	I_PROTECT_VALUE			0.1
// 放大倍率
#define		v_fd								1

// 函数声明
void OUTPUT_Init(void);
void Delay(__IO uint32_t nCount);

#endif /* __OUTPUT_H */
