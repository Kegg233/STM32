/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	��ѹ���	��������
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "./OLED/oled.h"
#include "./voltage_output/voltage_output.h"
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"  
#include "./sram/sram.h"
#include "./bsp_GeneralTim.h" 
#include "./bsp_exti.h"
#include <stdio.h>

 int main(void)
 {	 
	 
	// OLED��ʾ����ʼ��
	 OLED_Init();			
	 OLED_Clear(); 
	//���ڳ�ʼ��  
	Debug_USART_Config();		 	                       
  //��ʼ��16λ������ 
  FSMC_SRAM_Init();	
	// ��TIM3ʱ�ӣ����pwm������16λ�����͵�����ѹ
	GENERAL_TIM_Init();
	// ��ʼ����ѹ���
	OUTPUT_Init();
	 
}


/*********************************************END OF FILE**********************/
