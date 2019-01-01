/**
  ******************************************************************************
  * @file    main.c
  * @author  clark
  * @version V1.0.0
  * @date    2018-09-05
  * @brief   NULL
  *
  ****************************************************************************/
#include "main.h"
#include "laser.h"
#include "sin_table.h"
#include "step.h"
#include "draw.h"
#include "coordinate.h"

extern unsigned int xposition;
extern unsigned int yposition;
volatile unsigned int i;
volatile unsigned char btime=0;
extern const float figCircle[16][3];


int main(void)
{

	hstep hs;
	extern hfingure fig;	

	__set_PRIMASK(1);	
	SysTick_Init(48);	
	BSP_Motor_Init();	
	GPIO_laserInit();
	TimerInit();
	B.BIT1=0;
	laserop(0,B);
	
	hs.xdes =1280;
	hs.ydes =1280;	
	hs.xspeed =4000;
	xymove(&hs);

	hs.xdes =-704;
	hs.ydes =-704;
	hs.xspeed =4000;
	xymove(&hs);
	
	hfingureInit(&fig);

	while(1)
	{	  
		selectfig();
		
	}
}

/* @brief  SysTick IRQ callback */
void SysTick_Handler_User(void)
{
	
}

void hfingureInit(hfingure *hf)
{
	hf->nSeries = 0;
	hf->nCurrentCircle = 0;
	hf->nCurrentPoint = 0;
	
	hf->preinterface[0]=0;
	hf->preinterface[1]=0;
	
	hf->radius = 28;
	hf->xcenter = -16;
	hf->ycenter = -80;

	hf->preradius =28;
	hf->prexcenter =-16;
	hf->preycenter =-80;
	
	hf->nfigpoint = 1;	
}
