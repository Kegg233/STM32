#ifndef __SRAM_H
#define __SRAM_H															    

#include "stm32f10x.h"
#include "./usart/bsp_usart.h"

//使用SRAM的 Bank1.sector3,地址位HADDR[27,26]=10 

#define Bank1_SRAM3_ADDR    ((uint32_t)(0x68000000))

#define AD7606_RESULT()			(*(__IO uint16_t *)(0x68000000))

/*D 数据信号线*/
//			PD14
#define FSMC_D0_GPIO_PORT        GPIOD
#define FSMC_D0_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D0_GPIO_PIN         GPIO_Pin_14

//			PD15
#define FSMC_D1_GPIO_PORT        GPIOD
#define FSMC_D1_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D1_GPIO_PIN         GPIO_Pin_15

//			PD0
#define FSMC_D2_GPIO_PORT        GPIOD
#define FSMC_D2_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D2_GPIO_PIN         GPIO_Pin_0

//			PD1
#define FSMC_D3_GPIO_PORT        GPIOD
#define FSMC_D3_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D3_GPIO_PIN         GPIO_Pin_1

//			PE7
#define FSMC_D4_GPIO_PORT        GPIOE
#define FSMC_D4_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D4_GPIO_PIN         GPIO_Pin_7

//			PE8
#define FSMC_D5_GPIO_PORT        GPIOE
#define FSMC_D5_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D5_GPIO_PIN         GPIO_Pin_8

//			PE9
#define FSMC_D6_GPIO_PORT        GPIOE
#define FSMC_D6_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D6_GPIO_PIN         GPIO_Pin_9

//			PE10
#define FSMC_D7_GPIO_PORT        GPIOE
#define FSMC_D7_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D7_GPIO_PIN         GPIO_Pin_10

//			PE11
#define FSMC_D8_GPIO_PORT        GPIOE
#define FSMC_D8_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D8_GPIO_PIN         GPIO_Pin_11

//			PE12
#define FSMC_D9_GPIO_PORT        GPIOE
#define FSMC_D9_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D9_GPIO_PIN         GPIO_Pin_12

//			PE13
#define FSMC_D10_GPIO_PORT        GPIOE
#define FSMC_D10_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D10_GPIO_PIN         GPIO_Pin_13

//			PE14
#define FSMC_D11_GPIO_PORT        GPIOE
#define FSMC_D11_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D11_GPIO_PIN         GPIO_Pin_14

//			PE15
#define FSMC_D12_GPIO_PORT        GPIOE
#define FSMC_D12_GPIO_CLK         RCC_APB2Periph_GPIOE
#define FSMC_D12_GPIO_PIN         GPIO_Pin_15

//			PD8
#define FSMC_D13_GPIO_PORT        GPIOD
#define FSMC_D13_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D13_GPIO_PIN         GPIO_Pin_8

//			PD9
#define FSMC_D14_GPIO_PORT        GPIOD
#define FSMC_D14_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D14_GPIO_PIN         GPIO_Pin_9

//			PD10
#define FSMC_D15_GPIO_PORT        GPIOD
#define FSMC_D15_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_D15_GPIO_PIN         GPIO_Pin_10


/*NE3 ,对应的基地址0x68000000*/

/*OE读使能*/
//			PD4
#define FSMC_OE_GPIO_PORT        GPIOD
#define FSMC_OE_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_OE_GPIO_PIN         GPIO_Pin_4

/*RST 复位*/
//			PD5
#define FSMC_RST_GPIO_PORT        GPIOD
#define FSMC_RST_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_RST_GPIO_PIN         GPIO_Pin_5

/*CS 片选*/
//			PD1
#define FSMC_CS_GPIO_PORT        GPIOD
#define FSMC_CS_GPIO_CLK         RCC_APB2Periph_GPIOD
#define FSMC_CS_GPIO_PIN         GPIO_Pin_1
							
#define RESET(a)	if (a)	\
					GPIO_SetBits(FSMC_RST_GPIO_PORT,FSMC_RST_GPIO_PIN);\
					else		\
					GPIO_ResetBits(FSMC_RST_GPIO_PORT,FSMC_RST_GPIO_PIN)

#define CS(a)	if (a)	\
					GPIO_SetBits(FSMC_CS_GPIO_PORT,FSMC_CS_GPIO_PIN);\
					else		\
					GPIO_ResetBits(FSMC_CS_GPIO_PORT,FSMC_CS_GPIO_PIN)
					
void FSMC_SRAM_Init(void);
void AD7606_Reset(void);

#endif

