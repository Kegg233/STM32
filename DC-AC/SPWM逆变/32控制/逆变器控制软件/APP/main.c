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
*完成日期：2013.8.8
*****************************************************************/

#include "includes.h"
#include "math.h"

__align(8) static OS_STK 	TaskStartStk[500];
__align(8) static OS_STK	TaskLedStk[500];


#define START_PRIO		1u
#define LED_PRIO			5u


OS_EVENT	* spk;
OS_EVENT	* lcd;
OS_EVENT 	* time_10;


static void TaskStart( void *parg);
static void TaskLed(void *parg);
void MenusTask( void *parg);

int main()

{


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	OSInit();
	
	spk=OSSemCreate( 1 );
	lcd=OSSemCreate( 1 );
	time_10=OSSemCreate( 1 );


	OSTaskCreateExt( TaskStart,
									 (void *)0,
									 &TaskStartStk[500-1], 
									 START_PRIO,
									 START_PRIO,
									 TaskStartStk,
									 500,
									 ( void *)0,
									 OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR);	
							
	OSStart();
	return 0;
}

#include "math.h"
static float x_est_last1 = 0; 
static float P_last1 = 0; 
/*/the noise in the system */
static float Q1 = 0.1; 
static float R1 = 0.8; 
 
static float K1; 
static float P1; 
static float P_temp1; 
static float x_temp_est1; 
static float x_est1; 
static float z_measured1; /*/the 'noisy' value we measured  */
//   float z_real = 0.5; /*/the ideal value we wish to measure */
static float sum_error_kalman1 = 0; 
static float sum_error_measure1 = 0;

static float kalman1(float z_real) 
{ 		
	/*/do a prediction */
	x_temp_est1 = x_est_last1; 
	P_temp1 = P_last1 + Q1; 
	/*/calculate the Kalman gain */
	K1 = P_temp1 * (1.0/(P_temp1 + R1)); 
	/*/measure*/
	z_measured1 = z_real ;
	x_est1 = x_temp_est1 + K1 * (z_measured1 - x_temp_est1);  
	P1 = (1- K1) * P_temp1; 
	 
	sum_error_kalman1 += fabs(z_real - x_est1); 
	sum_error_measure1 += fabs(z_real-z_measured1); 
	 
	P_last1 = P1; 
	x_est_last1 = x_est1; 

	return x_est1; 
}


void halfword(FP32 j);
static void TaskStart( void *parg)
{
	INT16U i=0,j=0,l=0;
	FP32 vbat=0,k=0,oldk=0,dianliu=0,wendu=0;
	(void)parg;
	OS_CPU_SysTickInit();
	OSStatInit();
	
	OSTaskCreateExt( TaskLed,	 
									 (void *)0, 
									 &TaskLedStk[500-1],	
									 LED_PRIO, 
									 LED_PRIO, 
									 TaskLedStk, 
									 500,
									 ( void*)0,  
									 OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR );
	

	LedInit();		//初始化LED指示灯灯
	PWMTimer(25000);	//初始化PWM 	
	DCOut(ENABLE);
	
	ADC1_Configuration();		//采样初始化
	Getk_adc();
	ReadCanShu();
	OSTimeDlyHMSM( 0, 0, 1, 0 );
	vbat=GetDC310();
	gotoxy(0,0);
	dprintf8("12");
	k=310/vbat;
	k=kalman1(k);
	if(k<1)
	{
			halfword(k);
			ban();
	}
	Time1Config();			//SPWM
	SPWMState(ENABLE );
	//halfword();
	while(1)
	{
		OSTimeDlyHMSM( 0, 0, 0, 50 );
		vbat=GetBATE();
		
		if((vbat<10.5)||(vbat>14.5))
		{
			i++;
			if(i==60)
				while(1)
				{
					LedGreen(0);
					WenKong(0);
					DCOut(DISABLE);
					SPWMState(DISABLE );
				}
		}
		else
			i=0;
		
		dianliu=GetElectric();
		if(dianliu>32)
		{
			j++;
			if(j==40)
				while(1)
				{
					LedGreen(0);
					WenKong(0);
					DCOut(DISABLE);
					SPWMState(DISABLE );
				}
		}
		else
			j=0;
		if(dianliu>55)
		{
				while(1)
				{
					LedGreen(0);
					WenKong(0);
					DCOut(DISABLE);
					SPWMState(DISABLE );
				}
		}
		if(dianliu>2)
			WenKong(1);
		if(dianliu<1.5)
			WenKong(0);
		
		vbat=GetDC310();
		vbat=kalman1(vbat);
		k=310/vbat;
		//k=kalman1(k);
		if(k<1)
		{
			halfword(k);
		}
		else
			halfword(1);
		
	}
}


float k_dianya=0.14143920;	//电池电压比例 

extern volatile FP32 vref;
static void TaskLed(void *parg)	  //测试任务 
{	
	INT32U j=0,b=0;
	FP32 vbat=0,k=0;
	//ADC_Config();
	Init_ST7576();
	//Usart1Init(9600);
	DianLiuInit();
	while(1)
	{
		LedGreen(1);		
		OSTimeDlyHMSM( 0, 0, 0, 500 );		
		LedGreen(0);		 
		OSTimeDlyHMSM( 0, 0, 0, 500 );
		Getk_adc();
		vbat=GetBATE();
		gotoxy(0,0);
		dprintf("vbat=%0.2f ",vbat);
		vbat=GetDC310();
		gotoxy(0,2);
		dprintf("DC=%0.2f ",vbat);
		k=310/vbat;
		gotoxy(0,4);
		dprintf("k=%0.1f ",k);
		k=GetWenDu();
		gotoxy(0,6);
		dprintf("wen=%0.1f",k);
		k=GetElectric();
		dprintf(" %0.1f",k);

		if(GetAnJian()==0)
		{
			DCOut(DISABLE);
			SPWMState(DISABLE );
			OSTimeDlyHMSM( 0, 0, 3, 500 );
			Getele();
			SaveCanShu();
			DCOut(ENABLE);
			SPWMState(ENABLE );
			
		}
	}
}


