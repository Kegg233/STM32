
#include "includes.h"
#include <stdarg.h>
#include "stzimo.h"

#define JTAG_GPIO  (*(unsigned *)(AFIO_BASE+0x04))	 //���ù��ܼĴ���
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
// ����: void LCD_DataWrite(unsigned int Data) 
// ����: дһ���ֽڵ���ʾ������LCD�е���ʾ����RAM���� 
// ����: Data д�������  
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
// ����: void ST7576_RegWrite(unsigned char Command) 
// ����: дһ���ֽڵ�������ST7576�еĿ��ƼĴ������� 
// ����: Command   д������� 
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
//��ʾ������=================================================================
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
// ����: void ST7576_Init(void)
// ����: ST7576��ʼ����������������ST7576��ʼ����Ҫ���õ����Ĵ������������
//   �û����˽⣬����鿴DataSheet���и����Ĵ���������
//================================================================
void ST7576Reg_Init(void)
{
 ST7576_CS(0); 
 ST7576_Reset();   
	
 ST7576_RegWrite(0xA2);    //ST7576ƫѹ���ã�V3ʱѡ--ST7576 Bias selection(1/65 Duty,1/9Bias)   
 ST7576_RegWrite(0xA0);    //��������ʾ����  0xA0 ����   0xA1 ��ת
 ST7576_RegWrite(0xC8);		 //��������ʾ����  0xC0 ����   0xC8 ��ת

 ST7576_RegWrite(0x40);    //������ʾ��ʼ�ж�ӦRAM--SHL selection(COM0->COM64)      	
 ST7576_RegWrite(0x26);    //����Rb/Ra=6--Regulator Resistor Selection   
 ST7576_RegWrite(0x81);    //��������ģʽ����ʾ���ȣ�--Electronic Volume  
 ST7576_RegWrite(0x05);     //Reference Register selection  Vo=(1+Rb/Ra)(1+a)*2.1=10 

 ST7576_RegWrite(0x2f);  	 //�����ϵ����ģʽ--Power Control(Vc=1;Vr=1;Vf=1)   
 ST7576_RegWrite(0xF8);    //��ѹ������
 ST7576_RegWrite(0x00);   
 
 ST7576_RegWrite(0xAF);    //ST7576��ʾ��--Display on 

	Display_fill(0);
 
}

//---------------------------------------------
//ST7576_set_XY: ����ST7576���꺯��
//���������X��0��83  Y��0��5
//��д���ڣ�20080918 
//---------------------------------------------
void ST7576_setXY(unsigned char X, unsigned char Y)
{
	unsigned char gao,di; 
	ST7576_RegWrite(0xB0 | Y); //ҳ

	X = X;		 //Һ����0-131�ģ�����ֻ�õ�0-127�����Ե�����ķ���ʱ��131-0����ʵ������127-0��
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

static INT8U gCurRow,gCurCol;	             // ��ǰ�С��д洢���и�16�㣬�п�8��
/*********************************************************
�������ܣ�
��ڲ�����
���ڲ�����
**********************************************************/
static INT8U fnGetRow(void)
{
	return gCurRow;
}
/*********************************************************
�������ܣ�
��ڲ�����
���ڲ�����
**********************************************************/
static INT8U fnGetCol(void)
{
	return gCurCol;
}
void gotoxy(INT8U x,INT8U y)
{
	ST7576_setXY(x*8, y);// �У�ҳ 
	gCurRow = x;
	gCurCol = y;
}


INT8U dprintf(INT8U *fmt, ...)
{
	va_list arg_ptr;
	INT8U  c1,c2;
  INT8U tmpBuf[64];				       // LCD��ʾ���ݻ�����
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
					case LF:		                // �س����� ʱ����һ��
						i++;
						if(uCol < 8)				//�ܹ�8�� ��С�ڵڰ��� �и߼�16 
							uCol +=2;
						else						//����8�� �и߹���
							gotoxy(0,0);
							continue;
					case BS:		                  // �˸�
							if(uRow > 0)
								uCol--;
							break;
						default:		                   // ����
							c1 = 0x1f;					   //С���ַ�ֵС�� 32 �������ڻس� �����˸� �͸�ֵc1=0x1f���ֵ
				}
			}			
			// д����
			if(c1 >= 0x1f)
			{
				gotoxy(uRow,uCol);
				for(s=0;s<8;s++)
					ST7576_DataWrite(ASC_MSK1[(c1-0x1f)*16+s]);
				gotoxy(uRow,uCol+1);
				for(s=8;s<16;s++)
					ST7576_DataWrite(ASC_MSK1[(c1-0x1f)*16+s]);
			}		 //(c1-0x1f)*asc_chr_height+j-4 ��������еĵڼ����ַ� j-4 �����ַ��еĵڼ���Ԫ��
			else
			{
				gotoxy(uRow,uCol);
				for(s=0;s<8;s++)
					ST7576_DataWrite(0xaa);
				gotoxy(uRow,uCol+1);
				for(s=8;s<16;s++)
					ST7576_DataWrite(0xaa);
			}		
			if(c1 != BS)		                       // ���˸�
				uRow=uRow+1;
		}
		//����
		else
		{	     				
			for(j=0;j<sizeof(GB_16_H)/sizeof(GB_16_H[0]);j++)
			{
				if(c1 ==GB_16_H[j].Index[0] && c2 == GB_16_H[j].Index[1])
					break;
			}
										// д����
			if(j < sizeof(GB_16_H)/sizeof(GB_16_H[0]))
			{
				gotoxy(uRow,uCol);
				for(s=0;s<16;s++)
					ST7576_DataWrite(GB_16_H[j].Msk[s]);
				gotoxy(uRow,uCol+1);
				for(s=16;s<32;s++)
					ST7576_DataWrite(GB_16_H[j].Msk[s]);					
			}
			else						              // δ�ҵ�����
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
			if(uRow >= 16)			                        // ������
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
  INT8U tmpBuf[64];				       // LCD��ʾ���ݻ�����
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
									// д����
		if(j < sizeof(SZ_8)/sizeof(SZ_8[0]))
		{
			gotoxy(uRow,uCol);
			for(s=0;s<8;s++)
				ST7576_DataWrite(SZ_8[j].Msk[s]);
		
		}
		else						              // δ�ҵ�����
		{
			gotoxy(uRow,uCol);
			for(s=0;s<8;s++)
				ST7576_DataWrite(0xaa);
		}
		uRow += 1;
		i=i+1;
		if(uRow >= 16)			                        // ������
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
  INT8U tmpBuf[64];				       // LCD��ʾ���ݻ�����
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
									// д����
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
		else						              // δ�ҵ�����
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
		if(uRow >= 16)			                        // ������
		{
			uRow = 0;
			uCol += 4;
		}
		gotoxy(uRow,uCol);
	}

	return uLen;
}
