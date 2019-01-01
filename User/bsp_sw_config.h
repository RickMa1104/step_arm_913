/******************************************************************************
* �ļ�����bsp_software_config.h
* ��  �ܣ��������ͷ�ļ�
* ��  �ߣ��Ʋ���
* ��  �ڣ�2018-02-26
* ��  ע��
******************************************************************************/


#ifndef __BSP_SW_CONFIG_H
#define __BSP_SW_CONFIG_H


//#include "menu.h"
//#include "FunProg.h"
//#include "command.h"


/* PCB��� */
static const uint8_t BoardName[4] = " 172";		//YS172
/* Ӳ���汾�� */
static const uint8_t BoardVersion[4]=" 200";	//V2.00


/* ��������(0~255) */
#define IMAX_R		255
#define IMAX_G		255
#define IMAX_B		255
#define IMAX_W		255

/* ���ز��� */
#define IMAX_E		8	//������		0~10
#define IMAX_C		6	//����Ƶ��	1~10
#define IMAX_T		32	//����ʱ��	0:����  1~50����Ӧ0.1~5.0��

/* X���λ�ò��� */
#define X_OFFSET	235
#define X_MAX		142
/* Y���λ�ò��� */
#define Y_OFFSET	0
#define Y_MAX		110
/* ͼ�����λ�ò��� */
#define F_OFFSET	10
#define F_MAX		124

/* DMX512ͨ�� */
#define DMX512_X_DIR			DMX512_CH1		//X����������  0:�����  1~127:��ת���ٶ���������  128~255:��ת���ٶ��ɿ쵽��
#define DMX512_X_TUNE			DMX512_CH2		//X����ֵ�
#define DMX512_X_FINE			DMX512_CH2		//X���ϸ��
#define DMX512_Y_TUNE			DMX512_CH3		//Y����ֵ�
#define DMX512_Y_FINE			DMX512_CH3		//Y���ϸ��
#define DMX512_F_TUNE			DMX512_CH4		//ͼ������ֵ�
#define DMX512_F_FINE			DMX512_CH4		//ͼ�����ϸ��
#define DMX512_XYF_SPEED		DMX512_CH5		//XYF����ٶ�    0~255:�ɿ쵽��
#define DMX512_TotalBridge		DMX512_CH6		//�ܵ���
#define DMX512_R_Bridge			DMX512_CH7		//��
#define DMX512_G_Bridge			DMX512_CH8		//��
#define DMX512_B_Bridge			DMX512_CH9		//��
#define DMX512_FlashSpeed		DMX512_CH10		//Ƶ���ٶ�       0:����  1~255:�ٶ���������
#define DMX512_PrgFunMode		DMX512_CH11		//�깦��ģʽ
#define DMX512_PrgFunSpeed		DMX512_CH12		//�깦���ٶ�
#define DMX512_ResetChannel		DMX512_CH13		//��λͨ��       0~200:��Ч 201~255:����5�븴λ


#endif
