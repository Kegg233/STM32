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
	 
	// LED�Ƴ�ʼ����MODE�������ų�ʼ����
 	 LED_GPIO_Config();
	 LED1(0);
	  LED2(0);
	  LED3(0);
	 MODE(0);
	// OLED��ʾ����ʼ��
	 OLED_Init();			
	 OLED_Clear(); 
	 
	 OLED_ShowCHinese(00,0,0);		//��
	 OLED_ShowCHinese(18,0,1);		//��
	 OLED_ShowCHinese(36,0,2);		//��
	 OLED_ShowCHinese(54,0,3);		//��
	 OLED_ShowCHinese(72,0,4);		//˧
	 
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
