#include "common.h"
#include "main.h"


void GPIO_laserInit(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed =  GPIO_Speed_Level_3 ;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}
void laserop(unsigned char n, BIT b )
{
	if(b.BIT1)
		GPIO_WriteBit( GPIOB, GPIO_Pin_15,  Bit_SET);
	else
		GPIO_WriteBit( GPIOB, GPIO_Pin_15,  Bit_RESET);
}


