/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	恒压输出	过流保护
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
	 
	// LED灯初始化（MODE控制引脚初始化）
 	 LED_GPIO_Config();
	 LED1(0);
	  LED2(0);
	  LED3(0);
	 MODE(0);
	// OLED显示屏初始化
	 OLED_Init();			
	 OLED_Clear(); 
	 
	 OLED_ShowCHinese(00,0,0);		//柯
	 OLED_ShowCHinese(18,0,1);		//宇
	 OLED_ShowCHinese(36,0,2);		//翔
	 OLED_ShowCHinese(54,0,3);		//最
	 OLED_ShowCHinese(72,0,4);		//帅
	 
	//串口初始化  
	Debug_USART_Config();		 	                       
  //初始化16位采样器 
  FSMC_SRAM_Init();	
	// 打开TIM3时钟，输出pwm波驱动16位采样和调整电压
	GENERAL_TIM_Init();
	// 初始化恒压输出
	OUTPUT_Init();

}


/*********************************************END OF FILE**********************/
