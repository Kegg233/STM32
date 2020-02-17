/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_AdvanceTim.h" 
#include "bsp_exti.h"
#include "bsp_led.h"  
#include "bsp_usart.h"

extern uint16_t indexWave[];
extern int flag ;
extern int flag_glbh;
extern void Delay(__IO uint32_t nCount);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}



void ADVANCE_TIM_IRQHandler(void)
{	
	static uint16_t pwm_index = 0;			//用于PWM查表
	// 判断中断是否真的到来
	if (TIM_GetITStatus(ADVANCE_TIM, TIM_IT_Update) != RESET){		
			if( pwm_index < NUMBER ){
				// 改变占空比
				TIM_SetCompare1(TIM1,indexWave[pwm_index]);
				TIM_SetCompare2(TIM1,indexWave[pwm_index]);
				pwm_index++;
			}else{
				pwm_index = 0;
				// 改变占空比
				TIM_SetCompare1(TIM1,indexWave[pwm_index]);
				TIM_SetCompare2(TIM1,indexWave[pwm_index]);
				pwm_index++;
			}
		//必须要清除中断标志位
		TIM_ClearITPendingBit (ADVANCE_TIM, TIM_IT_Update);
	}
}

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
	char ch;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ch=getchar();
		switch(ch)
    {
			// 减小boost占空比
			case '1':
				flag = 1;	
				break;
			
			// 增大boost占空比
			case '2':
				flag = 2;	
				break;
			
			// 增大稳压电压
			case '5':
				flag = 5;	
			break;
			
			// 减小稳压电压			
			case '6':
				flag = 6;	
				break;
			
			// 减小逆变频率
			case '8':
				flag = 8;	
				break;
				
			// 增大逆变频率				
			case '7':
				flag = 7;	
				break;
			
			// 稳压开
			case '3':
				flag = 3;	
				break;
			
			// 稳压关
			case '4':
				flag = 4;	
				break;
		}
		
		//清除中断标志
		USART_ClearITPendingBit(DEBUG_USARTx,USART_IT_RXNE); 
	}	 
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
