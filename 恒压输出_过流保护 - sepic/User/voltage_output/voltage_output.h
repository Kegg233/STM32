#ifndef __OUTPUT_H
#define	__OUTPUT_H

#include "stm32f10x.h"

// ���õĵ������ѹ
#define 	VCC_BASE						10
// ������������					0Ϊ�ر�	1Ϊ����
#define  	I_PROTECT						0
// ������������ֵ
#define 	I_PROTECT_VALUE			0.1
// �Ŵ���
#define		v_fd								1

// ��������
void OUTPUT_Init(void);
void Delay(__IO uint32_t nCount);

#endif /* __OUTPUT_H */
