/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   初始化16位采样器的IO
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "./sram/sram.h"	  

static void SRAM_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 
  /* 使能16位采样器相关的GPIO时钟 */
                  
  RCC_APB2PeriphClockCmd(
                         /*数据信号线*/
                         FSMC_D0_GPIO_CLK | FSMC_D1_GPIO_CLK | FSMC_D2_GPIO_CLK | 
                         FSMC_D3_GPIO_CLK | FSMC_D4_GPIO_CLK | FSMC_D5_GPIO_CLK |
                         FSMC_D6_GPIO_CLK | FSMC_D7_GPIO_CLK | FSMC_D8_GPIO_CLK |
                         FSMC_D9_GPIO_CLK | FSMC_D10_GPIO_CLK| FSMC_D11_GPIO_CLK|
                         FSMC_D12_GPIO_CLK| FSMC_D13_GPIO_CLK| FSMC_D14_GPIO_CLK|
                         FSMC_D15_GPIO_CLK|  
                         /*控制信号线*/
                         FSMC_OE_GPIO_CLK | FSMC_RST_GPIO_CLK |FSMC_CS_GPIO_CLK, ENABLE);
												 
	 /*-- GPIO 配置 -----------------------------------------------------*/

  /* 通用 GPIO 配置 */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //配置为复用功能
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
    
  /*DQ数据信号线 针对引脚配置*/
  GPIO_InitStructure.GPIO_Pin = FSMC_D0_GPIO_PIN; 
  GPIO_Init(FSMC_D0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D1_GPIO_PIN; 
  GPIO_Init(FSMC_D1_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = FSMC_D2_GPIO_PIN; 
  GPIO_Init(FSMC_D2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D3_GPIO_PIN; 
  GPIO_Init(FSMC_D3_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D4_GPIO_PIN; 
  GPIO_Init(FSMC_D4_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D5_GPIO_PIN; 
  GPIO_Init(FSMC_D5_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D6_GPIO_PIN; 
  GPIO_Init(FSMC_D6_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D7_GPIO_PIN; 
  GPIO_Init(FSMC_D7_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D8_GPIO_PIN; 
  GPIO_Init(FSMC_D8_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D9_GPIO_PIN; 
  GPIO_Init(FSMC_D9_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D10_GPIO_PIN; 
  GPIO_Init(FSMC_D10_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D11_GPIO_PIN; 
  GPIO_Init(FSMC_D11_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D12_GPIO_PIN; 
  GPIO_Init(FSMC_D12_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D13_GPIO_PIN; 
  GPIO_Init(FSMC_D13_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D14_GPIO_PIN; 
  GPIO_Init(FSMC_D14_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D15_GPIO_PIN; 
  GPIO_Init(FSMC_D15_GPIO_PORT, &GPIO_InitStructure);
  
  /*读信号线*/
  GPIO_InitStructure.GPIO_Pin = FSMC_OE_GPIO_PIN; 
  GPIO_Init(FSMC_OE_GPIO_PORT, &GPIO_InitStructure);  
	
  /*复位线*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = FSMC_RST_GPIO_PIN; 
  GPIO_Init(FSMC_RST_GPIO_PORT, &GPIO_InitStructure);  
	
	/*片选线*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = FSMC_CS_GPIO_PIN; 
  GPIO_Init(FSMC_CS_GPIO_PORT, &GPIO_InitStructure);  
	
}				  			


// 初始化16位采样器外设

void FSMC_SRAM_Init(void)
{	
	// 定义初始化结构体
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

	// 初始化16位采样器相关的GPIO
	SRAM_GPIO_Config();
		
	// 使能FSMC外设时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

	// 地址建立时间（ADDSET）为1个HCLK 1/72M=14ns
	readWriteTiming.FSMC_AddressSetupTime = 0x03;	

	// 地址保持时间（ADDHLD）模式A未用到
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

	// 数据保持时间（DATAST）+ 1个HCLK = 3/72M=42ns
	readWriteTiming.FSMC_DataSetupTime = 0x06;		  
	
	// 设置总线转换周期，仅用于复用模式的NOR操作
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x01;
	
	// 设置时钟分频，仅用于同步类型的存储器
	readWriteTiming.FSMC_CLKDivision = 0x00;	

	// 数据保持时间，仅用于同步型的NOR
	readWriteTiming.FSMC_DataLatency = 0x00;		
	
	// 选择匹配SRAM的模式
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 
    
	// 选择FSMC映射的存储区域： Bank1 sram3
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	
	//设置地址总线与数据总线是否复用，仅用于NOR
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	
	//设置要控制的存储器类型：SRAM类型
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
	
	//存储器数据宽度：16位
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
	
	//设置是否使用突发访问模式，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
	
	//设置是否使能等待信号，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	
	//设置等待信号的有效极性，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	
	//设置是否支持把非对齐的突发操作，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
	
	//设置等待信号插入的时间，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	
	//存储器写使能 
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	
	//不使用等待信号
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
	
	// 不使用扩展模式，读写使用相同的时序
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
	
	//突发写操作
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	
	//读写时序配置
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	
	//读写同样时序，使用扩展模式时这个配置才有效
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 
	
	//初始化FSMC配置
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  
	
	// 使能BANK
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  										  								
}


void AD7606_Reset(void)
{
	
	RESET(0);	/* 退出复位状态 */
	RESET(1);
	RESET(1);
	RESET(1); /* 复位需要时间 */
	RESET(1);
	RESET(1);
	RESET(0);	/* 退出复位状态 */
	
}

/*********************************************END OF FILE**********************/

