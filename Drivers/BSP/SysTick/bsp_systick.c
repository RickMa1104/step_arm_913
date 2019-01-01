/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  �Ʋ���
  * @version V3.0.0
  * @date    2018-06-19
  * @brief   SysTick��ʱ����ʼ����us������ʱ��ms����ʱ
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "bsp_SysTick.h"


/* us������ʱ��ʱ�ӷ�Ƶ */
static volatile uint16_t us_div;


/**
  * @brief  SysTick��ʼ��
  * @param  sysclk:ϵͳʱ��(MHz)
  * @retval ��
  */
void SysTick_Init(uint16_t sysclk)
{
	us_div = sysclk;	//��Ƶ
	SysTick->VAL = 0;
	SysTick->LOAD = (uint32_t)us_div*1000-1;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |	//ʱ��Դ FCLK
					SysTick_CTRL_TICKINT_Msk   |	//ʹ���ж�
					SysTick_CTRL_ENABLE_Msk;		//ʹ�ܼ�����
}

/**
  * @brief  us������ʱ
  * @param  nus:��ʱʱ�� 0~2^32
  * @retval ��
  */
void delay_us(uint32_t nus)
{
	uint32_t WaitTick;
	uint32_t Tick;
	uint32_t OldTick=0;
	uint32_t Count=0;
	
	OldTick = SysTick->VAL;				//��ǰ����ֵ
	WaitTick = (uint32_t)nus*us_div;	//�ȴ�����ֵ
	
	do{
		Tick = SysTick->VAL;
		if(OldTick != Tick)
		{
			if(Tick > OldTick){	//�����
				Count += OldTick+(SysTick->LOAD-Tick);
			}else{
				Count += OldTick-Tick;
			}
			OldTick = Tick;
		}
	}while(Count < WaitTick);
}

/**
  * @brief  ms������ʱ
  * @param  nms:��ʱʱ�� 0~2^32
  * @retval ��
  */
void delay_ms(uint32_t nms)
{
	while(nms--)
	{
		delay_us(1000);
	}
}
