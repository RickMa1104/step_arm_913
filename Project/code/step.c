#include "main.h"
#define SINCOS 
#include "step.h"
#include "sin_table.h"
#include "stdlib.h"
volatile unsigned int xposition=25600;
volatile unsigned int yposition=25600;


extern	volatile unsigned int  nxspeed;
extern	volatile unsigned int  nyspeed;
extern  volatile unsigned char nxflag;
extern  volatile unsigned char nyflag;	
extern	volatile unsigned int nxcounter;
extern 	volatile unsigned int nycounter;




unsigned int ystepmove(signed int *smove,unsigned int position,unsigned char dir)
{
	
	    unsigned int index;
			index = position%128;

		switch(index>>5)	//4 quadrant
		{
			case 0:
				M3_AXIS_PWMA = (uint32_t)SinTable[index-0];
				M3_AXIS_PWMB = 0;
				M3_AXIS_PWMC = 0;
				M3_AXIS_PWMD = (uint32_t)CosTable[index-0];
			break;
			
			case 1:
				M3_AXIS_PWMA = (uint32_t)CosTable[index-32];
				M3_AXIS_PWMB = 0;
				M3_AXIS_PWMC = (uint32_t)SinTable[index-32];
				M3_AXIS_PWMD = 0;
			break;
			
			case 2:
				M3_AXIS_PWMA = 0;
				M3_AXIS_PWMB = (uint32_t)SinTable[index-64];
				M3_AXIS_PWMC = (uint32_t)CosTable[index-64];
				M3_AXIS_PWMD = 0;
			break;
			
			case 3:
				M3_AXIS_PWMA = 0;
				M3_AXIS_PWMB = (uint32_t)CosTable[index-96];
				M3_AXIS_PWMC = 0;
				M3_AXIS_PWMD = (uint32_t)SinTable[index-96];
			break;
		}
//		if(dir==1)
//		position++;
//		else
//		position--;
		
		if(dir==1)
		position+=2;
		else
		position-=2;		
		
		if(*smove>0)
		(*smove)--;
		else
		(*smove)++;
			
		
		return position;

}


unsigned int xstepmove(signed int *smove,unsigned int position,unsigned char dir)
{
	    unsigned int index;
			index = position%128;
		switch(index>>5)	//4 quadrant
		{
				case 0:
					M1_AXIS_PWMA = (uint32_t)SinTable[index-0];
					M2_AXIS_PWMA = 0;
					M1_AXIS_PWMB = 0;				
					M2_AXIS_PWMB = (uint32_t)CosTable[index-0];
				break;
				
				case 1:
					M1_AXIS_PWMA = (uint32_t)CosTable[index-32];
					M2_AXIS_PWMA = 0;
					M1_AXIS_PWMB = (uint32_t)SinTable[index-32];
					M2_AXIS_PWMB = 0;
				break;
				
				case 2:					
					M1_AXIS_PWMA = 0;
					M2_AXIS_PWMA= (uint32_t)SinTable[index-64];
					M1_AXIS_PWMB= (uint32_t)CosTable[index-64];
					M2_AXIS_PWMB = 0;
				break;
				
				case 3:						
					M1_AXIS_PWMA = 0;
					M2_AXIS_PWMA= (uint32_t)CosTable[index-96];
					M1_AXIS_PWMB = 0;
					M2_AXIS_PWMB = (uint32_t)SinTable[index-96];						
				break;
		}
//		if(dir==1)
//		position++;
//		else
//		position--;
		
		if(dir==1)
		position+=2;
		else
		position-=2;	

		if(*smove>0)
			(*smove)--;
		else
			(*smove)++;
		
		return position;

}

void xmove(signed int smove)
{

	while(smove!=0)
	{
			if(smove<0)
			{
       xposition = xstepmove(&smove,xposition,0);
			}
			else
			{
       xposition = xstepmove(&smove,xposition,1);				
			}
			
					delay_us(1000);
	}

	
}


void ymove(signed int smove)
{

	while(smove!=0)
	{
			if(smove<0)
			{
       yposition = ystepmove(&smove,yposition,0);
			}
			else
			{
       yposition = ystepmove(&smove,yposition,1);				
			}
			
					delay_us(1000);
	}

	
}

void xymove(hstep *hs)
{
		volatile int i=100,k=100,j=0;
	while( hs->xdes!=0 ||  hs->ydes!=0)
	{

			if( hs->xdes<0)
			{
       xposition = xstepmove(& hs->xdes,xposition,0);
				i = 0 - hs->xdes;
			}
			else if(hs->xdes>0)
			{
       xposition = xstepmove(& hs->xdes,xposition,1);	
        i = hs->xdes;				
			}
			
			if( hs->ydes<0)
			{
       yposition = ystepmove(& hs->ydes,yposition,0);
						k = 0 - hs->ydes;
			}
			else if( hs->ydes>0)
			{
       yposition = ystepmove(& hs->ydes,yposition,1);				
				   k = hs->ydes;	
			}
			
			if(i<10 || k<10)
			{
				hs->xspeed = hs->xspeed +14;

			}
			if(j<10 && hs->xspeed<999)
			{
				hs->xspeed  -= 14;
				j++;
				
			}

			delay_us(hs->xspeed);
	}
}


void xymoveT(hstep *hs)
{
	nxspeed =  hs->xspeed;
	nyspeed =  hs->yspeed ;
	nxcounter =0;
	nycounter =0;
	nxflag=1;
	nyflag =1;

	while( hs->xdes!=0 ||  hs->ydes!=0)
	{

		if(nxflag==1)
		{
			nxflag =0;
			nxcounter=0;
			
			if( hs->xdes<0)
			{
       xposition = xstepmove(& hs->xdes,xposition,0);
			}
			else if(hs->xdes>0)
			{
       xposition = xstepmove(& hs->xdes,xposition,1);	
			}		
	 		
		}
		
		if(nyflag ==1)
		{
			nyflag = 0;
			nycounter=0;
			
			if( hs->ydes<0)
			{
       yposition = ystepmove(& hs->ydes,yposition,0);

			}
			else if( hs->ydes>0)
			{
       yposition = ystepmove(& hs->ydes,yposition,1);				
				
			}
					

		}

	}
}

