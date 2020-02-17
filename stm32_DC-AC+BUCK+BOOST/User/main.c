#include "bsp_AdvanceTim.h" 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"  
#include "bsp_exti.h"
#include "./SysTick/bsp_SysTick.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC[NOFCHANEL];  
// ��Ļ���
char aa[20],bb[20];
// ��׼��ѹ
float adc_base = 24;
// ��ѹ��ʾʱ��
uint32_t see = 0;
// ��־λ
int flag = 0 ;
int flag_wykg = 0;
int flag_glbh = 0;
// boost����ռ�ձ�
int boost_zkb = 7200;
// ������Ƶ��
int bn_pl = 12;


// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

// ������
int main(void)
{	
	// ��ʱ��ʼ��
	SysTick_Init();
	// ���Ե�
	LED_GPIO_Config();
	// ��ʼ��DC - DC ���Ƶ�pwm
	GENERAL_TIM_Init();
	// ��ʼ������PWM���
	ADVANCE_TIM_Init();
	// ���ô���
	USART_Config();
	// ADC ��ʼ��
	ADCx_Init();
	// �ı�Ԥ��Ƶϵ��
	TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
	// �ı�ռ�ձ�
	TIM_SetCompare1(TIM3,boost_zkb);
	while (1)
	{
		ADC[0] =(float) ADC_ConvertedValue[0]/4096*3.3; // ��ȡת����ADֵ
		ADC[1] =(float) ADC_ConvertedValue[1]/4096*3.3; // ��ȡת����ADֵ
		if(ADC[0] > 3){
			flag_glbh = 1;
		}else{
			flag_glbh = 0;
		}
		// ��Сboostռ�ձ�		
		if(flag == 1 && flag_wykg == 0 && flag_glbh == 0){
			flag = 0;
			if(boost_zkb > 72){
					boost_zkb = boost_zkb - 72;
					// �ı�ռ�ձ�
					TIM_SetCompare1(TIM3,boost_zkb);
				}else {
					boost_zkb = 72;
					TIM_SetCompare1(TIM3,boost_zkb);
				}
			// �����������
				sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
				printf(aa);
				Usart_SendByte(DEBUG_USARTx,0xff);
				Usart_SendByte(DEBUG_USARTx,0xff);
				Usart_SendByte(DEBUG_USARTx,0xff);
			}
		// ����boostռ�ձ�
		if(flag == 2 && flag_wykg == 0 && flag_glbh == 0){
			flag = 0;
			if(boost_zkb < 10080){
				boost_zkb = boost_zkb + 72;
				TIM_SetCompare1(TIM3,boost_zkb);
			}else {
				boost_zkb = 10080;
				TIM_SetCompare1(TIM3,boost_zkb);
			}
			// �����������
			sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
			
		// ��ѹ��
		if(flag == 3 && flag_glbh == 0){
			flag = 0;
			flag_wykg = 1;
			printf("boost.t4.txt=\"��ѹ״̬\"");
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// ��ѹ��
		if(flag == 4 && flag_glbh == 0){
			flag = 0;
			flag_wykg = 0;
			boost_zkb = 7200;
			TIM_SetCompare1(TIM3,boost_zkb);
			sprintf(aa,"boost.t4.txt=\"%.1f\"",(float)boost_zkb/144);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// ������ѹ��ѹ
		if(flag == 5){
			flag = 0;
			adc_base = adc_base + 0.5 ;
			sprintf(aa,"wy.t2.txt=\"%.1f\"",adc_base);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}
		// ��С��ѹ��ѹ
		if(flag == 6){
			flag = 0;
			adc_base = adc_base - 0.5 ;
			sprintf(aa,"wy.t2.txt=\"%.1f\"",adc_base);
			printf(aa);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}	
		
		// ��С���Ƶ��
		if(flag == 7 && flag_glbh == 0){
			flag = 0;
				if(bn_pl < 30){
				bn_pl++;
				// �ı�Ԥ��Ƶϵ��
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}else {
				bn_pl = 30;
				// �ı�Ԥ��Ƶϵ��
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}
		}		
			
		// �������Ƶ��
		if(flag == 8 && flag_glbh == 0){
			flag = 0;
			if(bn_pl > 1){
				bn_pl--;
				// �ı�Ԥ��Ƶϵ��
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}else {
				bn_pl = 1;
				// �ı�Ԥ��Ƶϵ��
				TIM_PrescalerConfig(TIM1,bn_pl,TIM_PSCReloadMode_Immediate);
			}
		}		

		if( flag_wykg == 1 && flag_glbh == 0){
			// PID �㷨 P ���������һ��ʱ�̵�ռ�ձ�
			boost_zkb = boost_zkb+( adc_base - ADC[1]*10.83)*3000;
			if(boost_zkb > 10080){
				boost_zkb = 10080;
			}else if(boost_zkb < 72 ){
				boost_zkb = 72;
			}
			TIM_SetCompare1(TIM3,boost_zkb);
		}	
		// ��������
		if( flag_glbh == 1){
			TIM_SetCompare1(TIM3,0);
		}
		
		// ��ѹ��ʾ
		see++;
		if(see > 0xffff){
			see = 0;
			sprintf(bb,"boost.t2.txt=\"%.3f\"",(float)ADC[1]*11.05);
			printf(bb);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
			Usart_SendByte(DEBUG_USARTx,0xff);
		}			
	}
}
/*********************************************END OF FILE**********************/

