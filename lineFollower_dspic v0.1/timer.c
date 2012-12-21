#include "lr_header.h"

extern int  idx,Counter,an0Val,an1Val,rightSide,leftSide;
 /*=============================================================================  
Timer 3 is setup to time-out every 125 microseconds (8Khz Rate). As a result, the module 
will stop sampling and trigger a conversion on every Timer3 time-out, i.e., Ts=125us. 
=============================================================================*/
void initTmr(int id) 
{
      
      if(id == 3)
      {
	      //  T3CONbits.T32 = 1; //32  bit timer
	        T3CONbits.TCS = 0; //internal clock
	        T3CONbits.TCKPS = 0b00;
	        TMR3 = 0x0000;
	        PR3 = 0x11;
	        IFS0bits.T3IF = 0;
	        IEC0bits.T3IE = 1;
	
	        //Start Timer 3
	        T3CONbits.TON = 1;
      }
      else if(id ==2)
      {
			//loading PR2 value,for 20mSec , F=7.3Mhz
			PR2 = 9211; //1561;  
			//Timer-2 i/p clk prescale=1:8 and start the timer
	    	T2CON   = 0x8010;
		}

}

void __attribute__((interrupt, auto_psv)) _T3Interrupt( void )
{

	
//	timer_expired = 1;				/* flag */
	Counter++;
	if(Counter == 5)
		AD1CON1bits.SAMP = 0;					/* keep a running counter */
	else if(Counter == 12)
	{
	   //sendToUart(buffer);
   	   Counter=0;
	}	
 	IFS0bits.T3IF = 0;				/* reset timer interrupt flag	*/

}