#ifndef _COMMON_H_
#define _COMMON_H_


typedef struct {
	unsigned int BIT1 :1;
} BIT;

typedef struct{
  signed int xdes;
	signed int ydes;
	unsigned int xspeed;
	unsigned int yspeed;
  volatile	unsigned int aflag;
	volatile  unsigned int dflag;
	volatile  unsigned int xadCounter;
	volatile  unsigned int yadCounter;

}hstep;

typedef struct {
	
	volatile unsigned char nSeries;
	
	unsigned char nfigpoint;
	unsigned char nCurrentPoint;
	unsigned char nCurrentCircle;
	
	unsigned int radius;
	signed int xcenter;
	signed int ycenter;
	
	unsigned int preradius;
	signed int prexcenter;
	signed int preycenter;
	
	unsigned int  speedref;
	signed int arrInfo[20][3] ;	
	signed int figbuff[20][3];
	
	signed int interface[3];
	signed int preinterface[3];
} hfingure;



#ifdef MAINCOMMON
#define EXTERN 
#else
#define EXTERN extern 
#endif

EXTERN volatile BIT B;


#endif



