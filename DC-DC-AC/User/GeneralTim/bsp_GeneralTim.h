#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H

#include "stm32f10x.h"

// 通用定时器			 TIM3
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            (100-1)
#define            GENERAL_TIM_Prescaler         (100-1)
// 占空比配置			 GENERAL_TIM_Pulse / 100
#define						 GENERAL_TIM_Pulse						 52.9
// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

/**************************函数声明********************************/

void GENERAL_TIM_Init(void);

#endif	/* __BSP_GENERALTIME_H */


