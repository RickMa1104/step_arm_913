	#include "main.h"
	#include "customTimer.h"
	volatile unsigned int  nxspeed;
	volatile unsigned int  nyspeed;
  volatile unsigned char nxflag;
  volatile unsigned char nyflag;	
	volatile unsigned int nxcounter;
	volatile unsigned int nycounter;
	
	extern   hstep hs;

	
	void TimerInit(void)
	{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
		
		/*TimeBase*/
		TIM_TimeBaseInitStruct.TIM_Prescaler = 47;
		TIM_TimeBaseInitStruct.TIM_Period = 9;	
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);		
//		TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);	
		
		/* NVIC */
		NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn ;
		NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
//			NVIC_InitStruct.NVIC_IRQChannelPriority = 0x01;	
//		NVIC_InitStruct.NVIC_IRQChannel =TIM14_IRQn; 		
//		NVIC_Init(&NVIC_InitStruct);	
		
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);
//		TIM_ClearFlag(TIM14, TIM_FLAG_Update);		
		__set_PRIMASK(0);		
		TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);		
//		TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);			
		TIM_Cmd(TIM6, ENABLE);
//		TIM_Cmd(TIM14, ENABLE);
		
	}
	
	void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		
		if(hs.aflag ==1 )
		{
				if(nxcounter<(nxspeed+hs.xadCounter))
				nxcounter++;
				else
				{
				nxflag = 1;	
				if(hs.xadCounter>0)
        hs.xadCounter--;					
				}


				if(nycounter<(nyspeed+hs.yadCounter))
				nycounter++;
				else
				{
				nyflag = 1;	
				if(hs.yadCounter>0)	
        hs.yadCounter--;					
				}		
					
		}
		else
		{
				if(nxcounter<nxspeed)
				nxcounter++;
				else
				nxflag = 1;		

				if(nycounter<nyspeed)
				nycounter++;
				else
				nyflag = 1;					
		}
		
		
	}
}

//void TIM14_CUSTOM_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
//		
//	
//	}	
//}
