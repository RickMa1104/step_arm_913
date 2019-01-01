/**
  ******************************************************************************
  * @file    bsp_motor.c
  * @author  �Ʋ���
  * @version V3.1.0
  * @date    2018-06-21
  * @brief   ������������
  *
  ******************************************************************************
  * @attention
  *           12V���磺
  *               1��X�����ֵѡ��16R-20R���
  *               2��Y�����ֵѡ��16R-20R���
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "bsp_motor.h"
#include "sin_table.h"
//#include "menu.h"



/**
  * @brief  �����������
  * @param  ��
  * @retval ��
  */
static void M_Config(void)
{
	
}

/**
  * @brief  ���������ʼ��
  * @param  ��
  * @retval ��
  */
static void BSP_Motor_Driver_Hand(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	EXTI_InitTypeDef EXTI_InitStruct;

	
	/* ʹ��GPIO��ʱ�� */
	RCC_AHBPeriphClockCmd( M1_AXIS_PWMA_GPIO_CLK | M1_AXIS_PWMB_GPIO_CLK |
	                       M2_AXIS_PWMA_GPIO_CLK | M2_AXIS_PWMB_GPIO_CLK |
						   M3_AXIS_PWMA_GPIO_CLK | M3_AXIS_PWMB_GPIO_CLK |
						   M3_AXIS_PWMC_GPIO_CLK | M3_AXIS_PWMD_GPIO_CLK |
						   M1_HALL_GPIO_CLK, ENABLE);
	/* ʹ��SYSCFGʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* ʹ�ܶ�ʱ��ʱ�� */
	M1_AXIS_TIM_CLOCK_CMD(RCC_APB2Periph_TIM1, ENABLE);
	M3_AXIS_TIM_CLOCK_CMD(RCC_APB1Periph_TIM3, ENABLE);

	
	/* �������� */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* M1_Hall���� */
//	GPIO_InitStruct.GPIO_Pin = M1_HALL_GPIO_PIN;
//	GPIO_Init(M1_HALL_GPIO_PORT, &GPIO_InitStruct);
	/* M2_Hall���� */
//	GPIO_InitStruct.GPIO_Pin = M2_HALL_GPIO_PIN;
//	GPIO_Init(M2_HALL_GPIO_PORT, &GPIO_InitStruct);
	
	/* ���츴��������ڲ����� */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* M1_PWMA���� */
	GPIO_InitStruct.GPIO_Pin = M1_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M1_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M1_PWMB���� */
	GPIO_InitStruct.GPIO_Pin = M1_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M1_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	/* M2_PWMA���� */
	GPIO_InitStruct.GPIO_Pin = M2_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M2_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M2_PWMB���� */
	GPIO_InitStruct.GPIO_Pin = M2_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M2_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	
	/* M1_PWMA�������� */
	GPIO_PinAFConfig(M1_AXIS_PWMA_GPIO_PORT, M1_AXIS_PWMA_SOURCE, M1_AXIS_PWMA_GPIO_AF);
	/* M1_PWMB�������� */
	GPIO_PinAFConfig(M1_AXIS_PWMB_GPIO_PORT, M1_AXIS_PWMB_SOURCE, M1_AXIS_PWMB_GPIO_AF);
	/* M2_PWMB�������� */
	GPIO_PinAFConfig(M2_AXIS_PWMA_GPIO_PORT, M2_AXIS_PWMA_SOURCE, M2_AXIS_PWMA_GPIO_AF);
	/* M2_PWMB�������� */
	GPIO_PinAFConfig(M2_AXIS_PWMB_GPIO_PORT, M2_AXIS_PWMB_SOURCE, M2_AXIS_PWMB_GPIO_AF);
	
	/* ���ϼ��� */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = M1_AXIS_TIM_ARR;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/* ��ʼ��M1��ʱ�� */
	TIM_TimeBaseInit(M1_AXIS_TIM_BASE, &TIM_TimeBaseInitStruct);
	

	
	/* PWMģʽ���� */
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	/* ��ʼ��4��ͨ�� */
	TIM_OC1Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC2Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC3Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC4Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	

	
	if(M1_AXIS_TIM_BASE==TIM1)
	{
		/* �����ʹ�� */
		TIM_CtrlPWMOutputs(M1_AXIS_TIM_BASE, ENABLE);
	}
	
	
	
	/* ���츴��������ڲ����� */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* M3_PWMA���� */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWMC���� */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMC_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMC_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWMB���� */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWME���� */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMD_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMD_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(M3_AXIS_PWMA_GPIO_PORT, M3_AXIS_PWMA_SOURCE, M3_AXIS_PWMA_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMC_GPIO_PORT, M3_AXIS_PWMC_SOURCE, M3_AXIS_PWMC_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMB_GPIO_PORT, M3_AXIS_PWMB_SOURCE, M3_AXIS_PWMB_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMD_GPIO_PORT, M3_AXIS_PWMD_SOURCE, M3_AXIS_PWMD_GPIO_AF);
	
	/* ���ϼ��� */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 2400;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/* ��ʼ��M3��ʱ�� */
	TIM_TimeBaseInit(M3_AXIS_TIM_BASE, &TIM_TimeBaseInitStruct);
	
	/* PWMģʽ���� */
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	/* ��ʼ��4��ͨ�� */
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
	

	
	
	/* ʹ��M1��ʱ�� */
	TIM_Cmd(TIM1, ENABLE);
	/* ʹ��M3��ʱ�� */
	TIM_Cmd(TIM3, ENABLE);

}

/**
  * @brief  ��ȡ����״̬
  * @param  *m:������
  * @retval 0:���ڻ���λ��  1:���ڻ���λ��
  */
//static uint8_t M_IsHall(_mpid *m)
//{
//	uint8_t rev=1;
//	
//	if(m->axis==M1_AXIS) {
//		if(M1_HALL_IN==0)rev=0;
//		else rev = 1;
//	}else if(m->axis==M2_AXIS) {
//		if(M2_HALL_IN==0)rev=0;
//		else rev = 1;
//	}
//	return rev;
//}

/**
  * @brief  �����ʼ��
  * @param  ��
  * @retval ��
  */
void BSP_Motor_Init(void)
{
	/* ���ò��� */
	M_Config();
	/* ��ʼ������ */
	BSP_Motor_Driver_Hand();
}

/**
  * @brief  DMX512���Ƶ��λ��
  * @param  *m:������
  * @param  Position:���λ��
  * @param  speed:�ٶ�
  * @retval ��
//  */
//void BSP_Motor_Position(_mpid *m, uint32_t Position, uint16_t speed)
//{
//	m->EndPosition = Position + m->OffsetPosition;
//	m->EndSpeed    = speed;
//}

/**
  * @brief  ������������ٶ�
  * @param  *m:������
  * @retval ��
  */
//void M_UpdateRunSpeed(_mpid *m)
//{
//	uint16_t retryspeed;
//	
//	retryspeed = m->MoveStep/m->DecelLow;		//�ܹ��ܵ�����ٶ�
//	if(retryspeed < m->EndSpeed) {
//		m->RunSpeed = retryspeed;
//	}else{
//		m->RunSpeed = m->EndSpeed;
//	}
//}


/**
  * @brief  �����жϷ�����
  * @param  ��
  * @retval ��
  */
void M1M2_HALL_COM_IRQHandler(void)
{
	if(EXTI_GetITStatus(M1_HALL_EXTI_Line) != RESET)
	{
		EXTI_ClearITPendingBit(M1_HALL_EXTI_Line);	//����жϱ�־
	}
	
	if(EXTI_GetITStatus(M2_HALL_EXTI_Line) != RESET)
	{
		EXTI_ClearITPendingBit(M2_HALL_EXTI_Line);	//����жϱ�־
		
	}	
}
