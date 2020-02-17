#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H

#include "stm32f10x.h"
#define		NUMBER	108

// 高级定时器			 TIM1
#define            ADVANCE_TIM                   TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (1024-1)
#define            ADVANCE_TIM_PSC               (13-1)
#define            ADVANCE_TIM_PULSE             100
// 中断
#define            ADVANCE_TIM_IRQ               TIM1_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM1_UP_IRQHandler
// TIM1 输出比较通道 PA8
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH1_PORT          GPIOA
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_8
// PA9
#define            ADVANCE_TIM_CH2_GPIO_CLK      	RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH2_PORT          GPIOA
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_9
// TIM1 输出比较通道的互补通道 PB13
#define            ADVANCE_TIM_CH1N_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH1N_PORT          GPIOB
#define            ADVANCE_TIM_CH1N_PIN           GPIO_Pin_13
// PB 14
#define            ADVANCE_TIM_CH2N_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH2N_PORT          GPIOB
#define            ADVANCE_TIM_CH2N_PIN           GPIO_Pin_14
// TIM1 输出比较通道的刹车通道 PB12
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_BKIN_PORT          GPIOB
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_12

/**************************函数声明********************************/

void ADVANCE_TIM_Init(void);


#endif	/* __BSP_ADVANCETIME_H */


