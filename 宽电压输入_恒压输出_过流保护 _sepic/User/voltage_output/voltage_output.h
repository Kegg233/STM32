#ifndef __OUTPUT_H
#define	__OUTPUT_H

#include "stm32f10x.h"

// ���ƿ��� GPIO						PB5
#define MODE_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define MODE_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define MODE_GPIO_PIN				GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */


// ���õĵ������ѹ
#define 	VCC_BASE						3
// ������������					0Ϊ�ر�	1Ϊ����
#define  	I_PROTECT						1
// ������������ֵ
#define 	I_PROTECT_VALUE			1.6
// �����ѹ������Ƶ��
#define		input_divide							1
//#define		input_divide							10
// �����ѹ������Ƶ��
#define		output_divide							11
// �������ֱ���				
#define		accuracy						32768
// ��ߵ�ѹ
#define 	highest_V						5

/* ʹ�ñ�׼�Ĺ̼������IO*/
#define MODE(a)	if (a)	\
					GPIO_SetBits(MODE_GPIO_PORT,MODE_GPIO_PIN);\
					else		\
					GPIO_ResetBits(MODE_GPIO_PORT,MODE_GPIO_PIN)

// ��������
void OUTPUT_Init(void);
void Delay(__IO uint32_t nCount);

#endif /* __OUTPUT_H */
