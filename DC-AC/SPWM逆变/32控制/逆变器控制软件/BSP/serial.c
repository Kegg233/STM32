/****************************************************************
* Copyright (c) 2010 ,
* All rights reserved. 
*
*
*文件名称：
*文件标示：
*摘要	 ：
*
*
*当前版本：v1.0
*作者	 ：苹安 QQ：422720026
*完成日期：2012.7.2
*****************************************************************/
#include <stdarg.h>
#include "stm32f10x.h"
#include "includes.h"
#include "serial.h"

void Usart1Init(INT32S val)
{
	USART_InitTypeDef usart;
	GPIO_InitTypeDef usart1;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
	usart1.GPIO_Pin=GPIO_Pin_6;			   //初始化串口引脚配置
	usart1.GPIO_Speed=GPIO_Speed_50MHz;
	usart1.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &usart1);

	usart1.GPIO_Pin=GPIO_Pin_7;
	usart1.GPIO_Speed=GPIO_Speed_50MHz;
	usart1.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &usart1);

	usart.USART_BaudRate=val;				 //初始化串口1 
	usart.USART_WordLength=USART_StopBits_1;
	usart.USART_Parity =USART_Parity_No;
	usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1, &usart);
	USART_Cmd(USART1, ENABLE);

	
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;     	  //选择串口 中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能中断
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开接收中断 
}


void PutUsart1(INT8U ch)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
}
#define BUFFMAX_SIZE  300  //缓冲区长度

 /*********************************************************
函数介绍：
入口参数：
出口参数：
**********************************************************/
typedef struct {
	INT8U uart_data[BUFFMAX_SIZE];
	INT32S  frount;
	INT32S  rear;
	INT32S  counter;	//缓冲区计数器
	}buffer_uart;
	
static volatile  buffer_uart buf={0,0,0};
INT32S GetUartBufferCtr(void)
{
	INT32S temp;
	if(buf.frount>=buf.rear)
		temp= buf.frount-buf.rear;
	else
		temp=BUFFMAX_SIZE-buf.rear+buf.frount;
 	return temp;
}
/*********************************************************
函数介绍： 将字符串写入缓冲区
入口参数： char *p 指针
出口参数： 返回写入字符串个数
**********************************************************/
INT32S Put_Uart(INT8U *q)
{	
	INT32S i=0;

	while((*q)!=0x00)
	{
		while(((buf.rear+1)%BUFFMAX_SIZE==buf.frount))	//队列满就等待	空循环
		{
			OSTimeDly(2); 
		}			
		buf.uart_data[buf.rear]=*q;
		buf.rear=(buf.rear+1)%BUFFMAX_SIZE;
		buf.counter++;
		q++;
		i++;
	}

	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	//开缓冲区中断 
	return i;
}

INT32S Put_Uarts(INT8U *q,INT32U number)
{	
	INT32S i=0;

	while(i<number)
	{
		while(((buf.rear+1)%BUFFMAX_SIZE==buf.frount))	//队列满就等待	空循环
		{
			OSTimeDly(2); 
		}		buf.uart_data[buf.rear]=*q;
		buf.rear=(buf.rear+1)%BUFFMAX_SIZE;
		buf.counter++;
		q++;
		i++;
	}

	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	//开缓冲区中断 
	return i;
}

static char string[300];
void UartPrintf(const char *fmt,...)
{
    va_list ap;
    
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    va_end(ap);
    Put_Uart((INT8U*)string);
}

volatile INT8U command[100];
void serialcom(void);
volatile INT8U comcounter=0,commandflag=0;


void USART1_IRQHandler(void)		 //串口中断
{
	INT8U i=0;
	OS_CPU_SR    cpu_sr = 0;
	OS_ENTER_CRITICAL();
	OSIntNesting++;
	OS_EXIT_CRITICAL(); 

 	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		if(buf.frount==buf.rear)	//队列空关中断
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);	//关缓冲区中断
		else
		{
			USART_SendData(USART1, buf.uart_data[buf.frount]);
			buf.frount=(buf.frount+1)%BUFFMAX_SIZE;
			buf.counter--;
		}
		USART_ClearFlag(USART1,USART_FLAG_TXE);
	}
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		command[comcounter]=USART_ReceiveData(USART1);
		comcounter++;
		if(comcounter==100)
			comcounter=0;
		if(comcounter>2)
		{
			if((command[comcounter-1]==0x0a)&&(command[comcounter-2]==0x0d))
			{
				command[comcounter-1]=0;
				command[comcounter-2]=0;
				//serialcom();//命令判断
				for(i=0;i<100;i++)
					command[i]=0;
				comcounter=0;
			}
		}
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
	}		
	OSIntNesting--; 
}


void Usart2Init(INT32S val)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;			   //初始化串口引脚配置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=val;				 //初始化串口2 
	USART_InitStructure.USART_WordLength=USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);

	
	NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn;     	  //选择串口 中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能中断
	NVIC_Init(&NVIC_InitStructure);
}

static volatile  buffer_uart buf2={0,0,0};
/*********************************************************
函数介绍： 将字符串写入缓冲区
入口参数： char *p 指针
出口参数： 返回写入字符串个数
**********************************************************/
INT32S Put_Uart2(INT8U *q)
{	
	INT32S i=0;			
	while((*q)!=0x00)
	{
		while(((buf2.rear+1)%BUFFMAX_SIZE==buf2.frount))	//队列满就等待	空循环
		{
			OSTimeDly(2); 
		}			
		buf2.uart_data[buf2.rear]=*q;
		buf2.rear=(buf2.rear+1)%BUFFMAX_SIZE;
		buf2.counter++;
		q++;
		i++;
	}

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	//开缓冲区中断 
	return i;
}

static char string2[300];
void Uart2Printf(const char *fmt,...)
{
    va_list ap;
    
    va_start(ap,fmt);
    vsprintf(string2,fmt,ap);
    va_end(ap);
    Put_Uart2((INT8U*)string2);
}

void USART2_IRQHandler(void)		 //串口中断
{
	OS_CPU_SR    cpu_sr = 0;
	OS_ENTER_CRITICAL() ;
	OSIntNesting++;
	OS_EXIT_CRITICAL()  ; 

 	if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
		{
			if(buf2.frount==buf2.rear)	//队列空关中断
				USART_ITConfig(USART2, USART_IT_TXE, DISABLE);	//关缓冲区中断
			else
			{
				USART_SendData(USART2, buf2.uart_data[buf2.frount]);
				buf2.frount=(buf2.frount+1)%BUFFMAX_SIZE;
				buf2.counter--;
			}
		}

	OSIntNesting--; 
}






















