/******************************************************************************
* �ļ�����bsp_hw_config.h
* ��  �ܣ�������ͷ�ļ�
* ��  �ߣ��Ʋ���
* ��  �ڣ�2018-02-26
* ��  ע��
******************************************************************************/


#ifndef __BSP_HW_CONFIG_H
#define __BSP_HW_CONFIG_H


#include "stm32f0xx.h"
#include "stdio.h"


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"


#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */


#define LEDDrivers_Event_OUT		0x0001		//LED����¼�
#define LEDDrivers_Event_InitSalve	0x0002		//��ʼ���ӻ�

#define LEDFlash_Event_SALVE		0x0001		//����Ҫ��ӻ��������

#define APPProgram_Event_UPDATE		0x0001		//���¸���

#define Command_Event_MENU			0x0001		//�˵��¼�
#define Command_Event_Fun			0x0002		//����ִ��
#define Command_Event_DMX512_END	0x0004		//DMX512��������¼�

#define Menu_Event_Key				0x0001		//��������
#define Menu_Event_DmxReady			0x0002		//DMX512�źž���
#define Menu_Event_DmxNoReady		0x0004		//DMX512�źŶϿ�

/* ���������� */
extern TaskHandle_t xHandleTask_Command;




#endif
