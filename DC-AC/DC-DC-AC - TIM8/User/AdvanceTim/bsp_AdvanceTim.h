#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H

#include "stm32f10x.h"

// �߼���ʱ��			 TIM8
#define            ADVANCE_TIM                   TIM8
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM8
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (1024)
#define            ADVANCE_TIM_PSC               (1400-1)
#define            ADVANCE_TIM_PULSE              25.55
// �ж�
#define            ADVANCE_TIM_IRQ               TIM8_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM8_UP_IRQHandler
// TIM8 ����Ƚ�ͨ��һ PC6
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH1_PORT          GPIOC
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_6
// TIM8 ����Ƚ�ͨ���� PC8
#define            ADVANCE_TIM_CH2_GPIO_CLK      	RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH2_PORT          GPIOC
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_8
// TIM8 ����Ƚ�ͨ��һ�Ļ���ͨ�� PA7
#define            ADVANCE_TIM_CH1N_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH1N_PORT          GPIOA
#define            ADVANCE_TIM_CH1N_PIN           GPIO_Pin_7
// TIM8 ����Ƚ�ͨ�����Ļ���ͨ�� PB1
#define            ADVANCE_TIM_CH2N_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH2N_PORT          GPIOB
#define            ADVANCE_TIM_CH2N_PIN           GPIO_Pin_1
// TIM8 ����Ƚ�ͨ����ɲ��ͨ�� PB12
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_BKIN_PORT          GPIOA
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_6

/**************************��������********************************/

void ADVANCE_TIM_Init(void);


#endif	/* __BSP_ADVANCETIME_H */


