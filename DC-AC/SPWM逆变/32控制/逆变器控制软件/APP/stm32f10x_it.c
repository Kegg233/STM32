
#include "stm32f10x_it.h"
#include "includes.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_ADC1_DMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers  核心异常处理                       */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception. 这个函数处理 NMI异常
  * @param  None
  * @retval None
  */
extern OS_EVENT	* spk;

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None	   硬件异常
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
  * @param  None	 内存异常
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs内存异常中断 */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None	   	处理		总线	异常
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs总线异常 */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None		   处理	  使用	故障	异常
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
  * @param  None					调试 监视
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */



void EXTI3_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
  OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
  OSIntNesting++; 
	OS_EXIT_CRITICAL();

	if(EXTI_GetITStatus(EXTI_Line3)!= RESET)
	{

   	EXTI_ClearITPendingBit(EXTI_Line3);
	}
	OSIntNesting--; 
}

 


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers  周边设备中断处理                 */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/



void TIM4_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
  OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
  OSIntNesting++;
  OS_EXIT_CRITICAL();
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	OSIntNesting--; 
}


void ReadXYZ(INT16S *x,INT16S *y,INT16S *z);
volatile INT16S xdata[10],ydata[10],zdata[10];
void EXTI15_10_IRQHandler(void)	//中断考虑电平触发
{
	OS_CPU_SR  cpu_sr;
	INT32S value=0;
  OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
  OSIntNesting++; 
	OS_EXIT_CRITICAL();
	if(EXTI_GetITStatus(EXTI_Line12)!= RESET)
	{		
   	EXTI_ClearITPendingBit(EXTI_Line12);
	}
	OSIntNesting--; 
}




