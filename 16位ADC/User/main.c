/**
  ******************************************************************************
  FSMC���ⲿ AD7606
  ******************************************************************************
*/

#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"  
#include "./sram/sram.h"
#include "./bsp_GeneralTim.h" 
#include "./bsp_exti.h"
extern int16_t Data[8];

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

 /**
  * @brief  ������
  */
 int main(void)
 {	     
	//���ڳ�ʼ��  
	Debug_USART_Config();		 	                       
  //��ʼ���ⲿSRAM  
  FSMC_SRAM_Init();			     
	printf("hhhhh");
	GENERAL_TIM_Init();
	CS(0);
	AD7606_Reset();
	double ADC_0 = 0;
	double ADC_1 = 0;
	double ADC_2 = 0;
	double ADC_11 = 0;
	while(1){
		CS(0);
		Data[0] = AD7606_RESULT();
		Data[1] = AD7606_RESULT();
		Data[2] = AD7606_RESULT();
		ADC_0 = (double)Data[0]/32768*5;
		ADC_2 = (double)Data[2]/32768*5;
		ADC_11 = (double)Data[1]/32768*5;
		ADC_1 = ((ADC_11-2.5)/0.255)*1000;
		printf("��ѹ��%f V\r\n",ADC_0);
		printf("��ѹ2��%f V\r\n",ADC_2);
		printf("������%f mA  %f V\r\n",ADC_1,ADC_11);
		printf("\r\n");
		CS(1);
		Delay(0xfffeee);  
	}
	 
}


/*********************************************END OF FILE**********************/
