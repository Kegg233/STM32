#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H

#include "stm32f10x.h"

// 高级定时器			 TIM8
#define            ADVANCE_TIM                   TIM8
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM8
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (1024)
#define            ADVANCE_TIM_PSC               (1400-1)
#define            ADVANCE_TIM_PULSE              25.55
// 中断
#define            ADVANCE_TIM_IRQ               TIM8_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM8_UP_IRQHandler
// TIM8 输出比较通道一 PC6
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH1_PORT          GPIOC
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_6
// TIM8 输出比较通道三 PC8
#define            ADVANCE_TIM_CH2_GPIO_CLK      	RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH2_PORT          GPIOC
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_8
// TIM8 输出比较通道一的互补通道 PA7
#define            ADVANCE_TIM_CH1N_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH1N_PORT          GPIOA
#define            ADVANCE_TIM_CH1N_PIN           GPIO_Pin_7
// TIM8 输出比较通道三的互补通道 PB1
#define            ADVANCE_TIM_CH2N_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH2N_PORT          GPIOB
#define            ADVANCE_TIM_CH2N_PIN           GPIO_Pin_1
// TIM8 输出比较通道的刹车通道 PB12
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_BKIN_PORT          GPIOA
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_6

/**************************函数声明********************************/

void ADVANCE_TIM_Init(void);


#endif	/* __BSP_ADVANCETIME_H */


