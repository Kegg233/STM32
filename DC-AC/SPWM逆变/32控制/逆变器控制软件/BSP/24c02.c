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
*作者	 ：李良万
*完成日期：2012.7.2
*****************************************************************/

#include "includes.h"

extern OS_EVENT	* lcd;


#define JTAG_GPIO  (*(unsigned *)(AFIO_BASE+0x04))	 //复用功能寄存器

void I2C_Init(void)
{
	GPIO_InitTypeDef I2C;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	(*(unsigned *)(AFIO_BASE+0x04))|=AFIO_MAPR_SWJ_CFG_2;		  //设置为引脚
	
	JTAG_GPIO |=AFIO_MAPR_SWJ_CFG_2;		  //设置为引脚
	
	I2C.GPIO_Speed=GPIO_Speed_50MHz;
	I2C.GPIO_Mode=GPIO_Mode_Out_PP;
	
	I2C.GPIO_Pin=GPIO_Pin_3;   //WP
	GPIO_Init(GPIOB,&I2C);	

	I2C.GPIO_Pin=GPIO_Pin_4;   //SCL
	GPIO_Init(GPIOB,&I2C);

	I2C.GPIO_Mode=GPIO_Mode_Out_OD;
	I2C.GPIO_Pin=GPIO_Pin_5;   //SDA
	GPIO_Init(GPIOB,&I2C);

}

static void I2C_WP(INT32S i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_3);	
}

static void I2C_SCL(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_4);	
}
static void I2C_SDA_OUT(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_5);	
}
static INT8U I2C_SDA_IN(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
}
#define I2C_DELAY 4

static void mDelay(INT32S dly)//A normal delay
{
	unsigned int i;
	for(;dly>0;dly--)
    {
	  for(i=0;i<50;i++)
	     {;}
	 }
}

  //启动 IIC总线
static void I2C_Start(void)
{
	I2C_SDA_OUT(1);
	mDelay(I2C_DELAY);
	I2C_SCL(1);
	mDelay(I2C_DELAY);
	I2C_SDA_OUT(0);
	mDelay(I2C_DELAY);
	I2C_SCL(0);
}

//停止 IIC总线
static void I2C_Stop(void)
{
	I2C_SDA_OUT(0);
	mDelay(I2C_DELAY);
	I2C_SCL(1);
	mDelay(I2C_DELAY);
	I2C_SDA_OUT(1);
	mDelay(I2C_DELAY);
	I2C_SCL(0);
	mDelay(I2C_DELAY);
}

//应答 IIC总线
static void I2C_Ack(void)
{
	I2C_SDA_OUT(0);
	mDelay(I2C_DELAY);
	I2C_SCL(1);
	mDelay(I2C_DELAY);
	I2C_SCL(0);
//	mDelay(I2C_DELAY);
}

//非应答 IIC总线
static void I2C_NoAck(void)
{
	I2C_SDA_OUT(1);
	mDelay(I2C_DELAY);
	I2C_SCL(1);
	mDelay(I2C_DELAY);
	I2C_SCL(0);
//	mDelay(I2C_DELAY);
 }

//发送一个字节
static void I2C_Send(INT8U Data)
{ 
	INT8U BitCounter=8;
	INT8U temp;
	
	do
	{
		temp=Data;
		I2C_SCL(0);
		mDelay(I2C_DELAY);
		if((temp&0x80)==0x80)
			I2C_SDA_OUT(1);
		else
			I2C_SDA_OUT(0);

		mDelay(I2C_DELAY);
		
		I2C_SCL(1);
		mDelay(I2C_DELAY);
		temp=Data<<1;
		Data=temp;
		BitCounter--;
	}
	while(BitCounter);
	I2C_SCL(0);
}

//读一个字节并返回变量
static INT8U I2C_Read(void)
{
	INT8U temp=0;
	INT8U temp1=0;
	INT8U BitCounter=8;
	
	I2C_SDA_OUT(1);
	mDelay(I2C_DELAY);
	do
	{
		I2C_SCL(0);
		mDelay(I2C_DELAY);
		I2C_SCL(1);
	//	mDelay(I2C_DELAY);
		if(I2C_SDA_IN())
			temp=temp|0x01;
		else
			temp=temp&0xfe;
		if(BitCounter-1)
		{
		temp1=temp<<1;
		temp=temp1;
		}
		BitCounter--;
	}
	while(BitCounter);
	return(temp);
}

//    //write to ROM
//void WrToROM(INT16U address,INT8U Data)
//{
//	INT16U addWr;
//	addWr=address/256*2+0xa0;
//	I2C_WP(0);
//	I2C_Start();
//	I2C_Send(addWr);//Write Address
//	I2C_Ack();
//	I2C_Send(address%256);//Write sub Address
//	I2C_Ack();
//	I2C_Send(Data);//Write Data
//	I2C_Ack();
//	I2C_Stop();
////	mDelay(20);
//	I2C_WP(1);
//	   
//}
//read from ROM
//INT8U RdFromROM(INT16U address)
//{
//	INT16U addWr,addRd;
//	INT8U Data;
//	addWr=address/256*2+0xa0;
//	addRd=addWr+0x01;//addWr+1;
//	I2C_WP(0);
//	I2C_Start();
//	I2C_Send(addWr);//Write Address
//	I2C_Ack();
//	I2C_Send(address%256);//Write sub Address
//	I2C_Ack();
//	I2C_Start();
//	I2C_Send(addRd);//Read Address
//	I2C_Ack();
//	Data=I2C_Read();//Read Data
//	I2C_SCL(0);
//	I2C_NoAck();
//	I2C_Stop();
//	I2C_WP(1);
//	return Data;
//}

    //write to ROM
void WrToROM(INT16U address,INT8U Data)
{
	INT16U addWr;
	addWr=0xa0;
	I2C_WP(0);
	I2C_Start();
	I2C_Send(addWr);//Write Address
	I2C_Ack();
	I2C_Send((INT8U)(address>>8));//Write sub Address
	I2C_Ack();
	I2C_Send((INT8U)address);//Write sub Address

	I2C_Ack();
	I2C_Send(Data);//Write Data
	I2C_Ack();
	I2C_Stop();
//	mDelay(20);
	I2C_WP(1);	   
}
//read from ROM
INT8U RdFromROM(INT16U address)
{
	INT16U addWr,addRd;
	INT8U Data;
	addWr=0xa0;
	addRd=0xa1;//addWr+1;
	I2C_WP(0);
	I2C_Start();
	I2C_Send(addWr);//Write Address
	I2C_Ack();
	I2C_Send((INT8U)(address>>8));//Write sub Address
	I2C_Ack();
	I2C_Send((INT8U)address);//Write sub Address

	I2C_Ack();
	I2C_Start();
	I2C_Send(addRd);//Read Address
	I2C_Ack();
	Data=I2C_Read();//Read Data
	I2C_SCL(0);
	I2C_NoAck();
	I2C_Stop();
	I2C_WP(1);
	return Data;
}


//先用共用体定义，然后在定义一个变量，存储时用hh.u8[]; 做浮点数运算时用hh.f_type; 

void WriteFloat(INT16U address,float data)
{
    int i=0; 
    char *p; 
    p=(char *)&data; 
    for(i=0;i<sizeof(data);i++) 
    { 
        WrToROM(address , *p); 
        p++; 
        address++; 
    } 

}
float ReadFloat(INT16U address)
{	
	float *pp;
	INT8U ch[4];
	ch[0]=RdFromROM(address);
	ch[1]=RdFromROM(address+1);
	ch[2]=RdFromROM(address+2);
	ch[3]=RdFromROM(address+3);
	pp=(float *)ch;
	return *pp;
}
void WriteINT32U(INT16U address,INT32U data)
{
	INT8U temp;
	temp=(INT8U)data;
	WrToROM(address+0,temp);
	temp=(INT8U)(data>>8);
	WrToROM(address+1,temp);
	temp=(INT8U)(data>>16);
	WrToROM(address+2,temp);
	temp=(INT8U)(data>>24);
	WrToROM(address+3,temp);
}
INT32U ReadINT32U(INT16U address)
{
	INT32U temp=0;
	temp=RdFromROM(address+3);
	temp=temp<<8;
	temp=temp+RdFromROM(address+2);
	temp=temp<<8;
	temp=temp+RdFromROM(address+1);
	temp=temp<<8;
	temp=temp+RdFromROM(address+0);
	return temp;
	
}

void WriteINT16U(INT16U address,INT16U data)
{
	INT8U temp;
	temp=(INT8U)data;
	WrToROM(address+0,temp);
	temp=(INT8U)(data>>8);
	WrToROM(address+1,temp);
}
INT16U ReadINT16U(INT16U address)
{
	INT32U temp=0;
	temp=temp+RdFromROM(address+1);
	temp=temp<<8;
	temp=temp+RdFromROM(address+0);
	return temp;
}

void test(void)
{
// 	int j=0;
// 	cls(0);
// 	dprintf8(0,0,"---\n");
// 	while(1)
// 	{
// 	 	j++;
// 		WriteFloat(j,12.3424345);
// 		dprintf8(0,10,"  %04d   %f",j,ReadFloat(j));
// 		if(j==8188)
// 			j=0;
// 	}
}
/*************************************************
*
*	清零 EEPROM
*
**************************************************/
void I2C_Clean(void)
{
	INT32S i;
	INT8U err;
	for(i=0;i<8192;i++)
	{
   		WrToROM(i,0x00);
		if(i%200==0)
		{
			OSSemPend(lcd,0,&err);
			dprintf("." );
			OSSemPost(lcd);
		}
	}
}















