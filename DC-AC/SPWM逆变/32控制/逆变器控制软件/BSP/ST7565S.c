
#include "includes.h"
#include <stdarg.h>
#include "stzimo.h"

#define JTAG_GPIO  (*(unsigned *)(AFIO_BASE+0x04))	 //复用功能寄存器
void Init_ST7576(void)
{
	GPIO_InitTypeDef st7576;  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	st7576.GPIO_Pin=GPIO_Pin_3;	//ST7576_SDI
	st7576.GPIO_Speed=GPIO_Speed_50MHz;
	st7576.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&st7576);	
	
	st7576.GPIO_Pin=GPIO_Pin_4;	//ST7576_CLK
	st7576.GPIO_Speed=GPIO_Speed_50MHz;
	st7576.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&st7576);
	
	st7576.GPIO_Pin=GPIO_Pin_5;	//ST7576_A0
	st7576.GPIO_Speed=GPIO_Speed_50MHz;
	st7576.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&st7576);
	
	st7576.GPIO_Pin=GPIO_Pin_8;	//ST7576_RES
	st7576.GPIO_Speed=GPIO_Speed_50MHz;
	st7576.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&st7576);

	st7576.GPIO_Pin=GPIO_Pin_9;	//ST7576_CS
	st7576.GPIO_Speed=GPIO_Speed_50MHz;
	st7576.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&st7576);
	
	ST7576Reg_Init();
}
void ST7576_SDI(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
}
void ST7576_CLK(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_4);	
}
void ST7576_A0(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_5);	
}
void ST7576_RES(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_8);	
}
void ST7576_CS(INT8U i)
{
	if(i==0)
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_9);	
}



/******************************delay time***********************************/  
void delay_ms(unsigned int ms)  
{  
 unsigned int n ;  
 while(ms--)  
      {  
       n  =  86;  
       while(n--);  
      }  
} 
//****************************reset IC for start****************************/  
void ST7576_Reset()  
{  
 ST7576_RES(0);  
 OSTimeDlyHMSM( 0, 0, 0, 50 );	 
 ST7576_RES(1);  
 OSTimeDlyHMSM( 0, 0, 0, 50 );	
}    
//======================================================================== 
// 函数: void LCD_DataWrite(unsigned int Data) 
// 描述: 写一个字节的显示数据至LCD中的显示缓冲RAM当中 
// 参数: Data 写入的数据  
//======================================================================== 
void ST7576_DataWrite(unsigned char Dat)//,_Fill_Dot_LCD 
{ 
 unsigned char Num; 
 ST7576_CS(0); 
 ST7576_A0(1); 
 for(Num=0;Num<8;Num++) 
 { 
  if((Dat&0x80) == 0) 
  ST7576_SDI(0); 
  else ST7576_SDI(1); 
  Dat = Dat << 1; 
  ST7576_CLK(0); 
  ST7576_CLK(1); 
 } 
 ST7576_CS(1); 
 } 
//======================================================================== 
// 函数: void ST7576_RegWrite(unsigned char Command) 
// 描述: 写一个字节的数据至ST7576中的控制寄存器当中 
// 参数: Command   写入的数据 
//======================================================================== 
void ST7576_RegWrite(unsigned char Command) 
{ 
 unsigned char Num; 
 ST7576_CS(0); 
 ST7576_A0(0); 
 for(Num=0;Num<8;Num++) 
 { 
  if((Command&0x80) == 0) 
  ST7576_SDI(0);
  else ST7576_SDI(1);
  Command = Command << 1; 
  ST7576_CLK(0);
  ST7576_CLK(1);
 } 
 ST7576_CS(1);
} 
//显示亮暗点=================================================================
void Display_fill(unsigned char fill)  
{  
 unsigned char page,column;  
 for(page=0xB7;page>=0xB0;page--)  
    {  
     ST7576_RegWrite(page);  //set page address   
     ST7576_RegWrite(0x10);  //set Column address MSB   
     ST7576_RegWrite(0x00);  //set column address LSB   
     for(column=0;column<132;column++)  
        {  
         ST7576_DataWrite(fill);  
        }  
    }  
}  
void cls(void)
{
	Display_fill(0x00);
}

//==============================================================
// 函数: void ST7576_Init(void)
// 描述: ST7576初始化程序，在里面会完成ST7576初始所需要设置的许多寄存器，具体如果
//   用户想了解，建议查看DataSheet当中各个寄存器的意义
//================================================================
void ST7576Reg_Init(void)
{
 ST7576_CS(0); 
 ST7576_Reset();   
	
 ST7576_RegWrite(0xA2);    //ST7576偏压设置，V3时选--ST7576 Bias selection(1/65 Duty,1/9Bias)   
 ST7576_RegWrite(0xA0);    //设置列显示方向  0xA0 正常   0xA1 逆转
 ST7576_RegWrite(0xC8);		 //设置行显示方向  0xC0 正常   0xC8 逆转

 ST7576_RegWrite(0x40);    //设置显示起始行对应RAM--SHL selection(COM0->COM64)      	
 ST7576_RegWrite(0x26);    //设置Rb/Ra=6--Regulator Resistor Selection   
 ST7576_RegWrite(0x81);    //电量设置模式（显示亮度）--Electronic Volume  
 ST7576_RegWrite(0x05);     //Reference Register selection  Vo=(1+Rb/Ra)(1+a)*2.1=10 

 ST7576_RegWrite(0x2f);  	 //设置上电控制模式--Power Control(Vc=1;Vr=1;Vf=1)   
 ST7576_RegWrite(0xF8);    //升压比设置
 ST7576_RegWrite(0x00);   
 
 ST7576_RegWrite(0xAF);    //ST7576显示开--Display on 

	Display_fill(0);
 
}

//---------------------------------------------
//ST7576_set_XY: 设置ST7576坐标函数
//输入参数：X：0－83  Y：0－5
//编写日期：20080918 
//---------------------------------------------
void ST7576_setXY(unsigned char X, unsigned char Y)
{
	unsigned char gao,di; 
	ST7576_RegWrite(0xB0 | Y); //页

	X = X;		 //液晶是0-131的，我们只用到0-127，所以当倒序的方法时（131-0），实际上是127-0，
	gao = X & 0xf0;
	gao = gao >> 4;
	di = X & 0x0f;
	ST7576_RegWrite(0x10 | gao);  //set Column address MSB   
  ST7576_RegWrite(0x00 | di);   //set column address LSB
}   



#define STX			0x02
#define ETX			0x03
#define EOT			0x04
#define ENQ			0x05
#define BS			0x08
#define CR			0x0D
#define LF			0x0A
#define DLE			0x10
#define ETB			0x17
#define SPACE		0x20
#define COMMA		0x2C

static INT8U gCurRow,gCurCol;	             // 当前行、列存储，行高16点，列宽8点
/*********************************************************
函数介绍：
入口参数：
出口参数：
**********************************************************/
static INT8U fnGetRow(void)
{
	return gCurRow;
}
/*********************************************************
函数介绍：
入口参数：
出口参数：
**********************************************************/
static INT8U fnGetCol(void)
{
	return gCurCol;
}
void gotoxy(INT8U x,INT8U y)
{
	ST7576_setXY(x*8, y);// 列，页 
	gCurRow = x;
	gCurCol = y;
}


INT8U dprintf(INT8U *fmt, ...)
{
	va_list arg_ptr;
	INT8U  c1,c2;
  INT8U tmpBuf[64];				       // LCD显示数据缓冲区
	INT8U i=0,j,uLen,uRow,uCol;
	INT32S  s;
	
	va_start(arg_ptr, fmt);
	uLen = (INT8U)vsprintf((char*)tmpBuf, (const char*)fmt, arg_ptr);
	va_end(arg_ptr);
	
	while(i<uLen)
	{
		c1 = tmpBuf[i];
		c2 = tmpBuf[i+1];
		uRow = fnGetRow();
		uCol = fnGetCol();
		
		if(c1 <= 126)
		{	                                    // ASCII
			if(c1 < 0x20)
			{
				switch(c1)
				{
					case CR:
					case LF:		                // 回车或换行 时换下一行
						i++;
						if(uCol < 8)				//总共8行 若小于第八行 行高加16 
							uCol +=2;
						else						//大于8行 行高归零
							gotoxy(0,0);
							continue;
					case BS:		                  // 退格
							if(uRow > 0)
								uCol--;
							break;
						default:		                   // 其他
							c1 = 0x1f;					   //小于字符值小于 32 并不等于回车 换行退格 就赋值c1=0x1f这个值
				}
			}			
			// 写数据
			if(c1 >= 0x1f)
			{
				gotoxy(uRow,uCol);
				for(s=0;s<8;s++)
					ST7576_DataWrite(ASC_MSK1[(c1-0x1f)*16+s]);
				gotoxy(uRow,uCol+1);
				for(s=8;s<16;s++)
					ST7576_DataWrite(ASC_MSK1[(c1-0x1f)*16+s]);
			}		 //(c1-0x1f)*asc_chr_height+j-4 求出数组中的第几组字符 j-4 这组字符中的第几个元素
			else
			{
				gotoxy(uRow,uCol);
				for(s=0;s<8;s++)
					ST7576_DataWrite(0xaa);
				gotoxy(uRow,uCol+1);
				for(s=8;s<16;s++)
					ST7576_DataWrite(0xaa);
			}		
			if(c1 != BS)		                       // 非退格
				uRow=uRow+1;
		}
		//中文
		else
		{	     				
			for(j=0;j<sizeof(GB_16_H)/sizeof(GB_16_H[0]);j++)
			{
				if(c1 ==GB_16_H[j].Index[0] && c2 == GB_16_H[j].Index[1])
					break;
			}
										// 写数据
			if(j < sizeof(GB_16_H)/sizeof(GB_16_H[0]))
			{
				gotoxy(uRow,uCol);
				for(s=0;s<16;s++)
					ST7576_DataWrite(GB_16_H[j].Msk[s]);
				gotoxy(uRow,uCol+1);
				for(s=16;s<32;s++)
					ST7576_DataWrite(GB_16_H[j].Msk[s]);					
			}
			else						              // 未找到该字
			{
				gotoxy(uRow,uCol);
				for(s=0;s<16;s++)
					ST7576_DataWrite(0xca);
				gotoxy(uRow,uCol+1);
				for(s=16;s<32;s++)
					ST7576_DataWrite(0xaa);		
			}
			uRow += 2;
			i++;
			if(uRow >= 16)			                        // 光标后移
			{
				uRow = 0;
				uCol += 2;
			}
		}
		gotoxy(uRow,uCol);
		i++;
	}
		return uLen;
}



INT8U dprintf8(INT8U *fmt, ...)
{
	va_list arg_ptr;
	INT8U  c1,c2;
  INT8U tmpBuf[64];				       // LCD显示数据缓冲区
	INT8U i=0,j,uLen,uRow,uCol;
	INT32S  s;
	
	va_start(arg_ptr, fmt);
	uLen = (INT8U)vsprintf((char*)tmpBuf, (const char*)fmt, arg_ptr);
	va_end(arg_ptr);
	
	while(i<uLen)
	{
		c1 = tmpBuf[i];
		c2 = tmpBuf[i+1];
		uRow = fnGetRow();
		uCol = fnGetCol();
   				
		for(j=0;j<sizeof(SZ_8)/sizeof(SZ_8[0]);j++)
		{
			if(c1 ==SZ_8[j].Index[0])
				break;
		}
									// 写数据
		if(j < sizeof(SZ_8)/sizeof(SZ_8[0]))
		{
			gotoxy(uRow,uCol);
			for(s=0;s<8;s++)
				ST7576_DataWrite(SZ_8[j].Msk[s]);
		
		}
		else						              // 未找到该字
		{
			gotoxy(uRow,uCol);
			for(s=0;s<8;s++)
				ST7576_DataWrite(0xaa);
		}
		uRow += 1;
		i=i+1;
		if(uRow >= 16)			                        // 光标后移
		{
			uRow = 0;
			uCol += 1;
		}
		gotoxy(uRow,uCol);
	}
	return uLen;
}

INT8U dprintf24(INT8U *fmt, ...)
{
	va_list arg_ptr;
	INT8U  c1,c2;
  INT8U tmpBuf[64];				       // LCD显示数据缓冲区
	INT8U i=0,j,uLen,uRow,uCol;
	INT32S  s;
	
	va_start(arg_ptr, fmt);
	uLen = (INT8U)vsprintf((char*)tmpBuf, (const char*)fmt, arg_ptr);
	va_end(arg_ptr);
	
	while(i<uLen)
	{
		c1 = tmpBuf[i];
		c2 = tmpBuf[i+1];
		uRow = fnGetRow();
		uCol = fnGetCol();
   				
		for(j=0;j<sizeof(GB_24_H)/sizeof(GB_24_H[0]);j++)
		{
			if(c1 ==GB_24_H[j].Index[0] && c2 == GB_24_H[j].Index[1])
				break;
		}
									// 写数据
		if(j < sizeof(GB_24_H)/sizeof(GB_24_H[0]))
		{
			gotoxy(uRow,uCol);
			for(s=0;s<24;s++)
				ST7576_DataWrite(GB_24_H[j].Msk[s]);
			gotoxy(uRow,uCol+1);
			for(s=24;s<48;s++)
				ST7576_DataWrite(GB_24_H[j].Msk[s]);	
			gotoxy(uRow,uCol+2);
			for(s=48;s<72;s++)
				ST7576_DataWrite(GB_24_H[j].Msk[s]);				
		}
		else						              // 未找到该字
		{
			gotoxy(uRow,uCol);
			for(s=0;s<24;s++)
				ST7576_DataWrite(0xaa);
			gotoxy(uRow,uCol+1);
			for(s=24;s<48;s++)
				ST7576_DataWrite(0xaa);		
			gotoxy(uRow,uCol+2);
			for(s=48;s<72;s++)
				ST7576_DataWrite(0xaa);		
		}
		uRow += 4;
		i=i+2;
		if(uRow >= 16)			                        // 光标后移
		{
			uRow = 0;
			uCol += 4;
		}
		gotoxy(uRow,uCol);
	}

	return uLen;
}
