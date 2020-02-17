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
#include "includes.h"


/*************************************************
*
*	读取stm32 id
*
**************************************************/
INT32U ReadStmID(void)
{
	return *(unsigned int*)(0x1FFFF7E8);
}
/*************************************************
*
*	加密函数
*
**************************************************/
void JiaMi(void)
{
	INT8U err;
	INT16U temp;
	INT32U stmid=0,stmid1=0;
	stmid=ReadStmID();

	EE_ReadInt16(0,&temp); 
	if(temp!=0x5555)
	{
		
		FLASH_Unlock();
  	EE_Init();	
		EE_WriteInt16(0,0X5555);
		EE_WriteInt16(1,(INT16U)stmid);
		EE_WriteInt16(2,(INT16U)(stmid>>16));
		OSSemPend(lcd,0,&err);

		OSTimeDlyHMSM( 0, 0, 1, 0 );
		OSSemPost(lcd);
	}
	else
	{
		EE_ReadInt16(2,&temp); 
		stmid1=0;
		stmid1=stmid1+temp;
		stmid1=stmid1<<16;
		EE_ReadInt16(1,&temp); 
		stmid1=stmid1+temp;
		if(stmid1!=stmid)
				while(1);		
	}
	 
}
