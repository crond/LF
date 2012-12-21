#include "lr_header.h"

 /***********************
 STUCORN Version 0.2
 1. 
 
 ****************************/
__CONFIG(FWDT, WDTDIS);
 
int idx=0,Counter=0,an0Val=0,an1Val=0,an2Val=0,an3Val=0,an4Val=0,an5Val=0,rightSide=0,leftSide=0;
 unsigned long int G_userInput=0;
 
    
    
int checkAngNChangeDir()
{
#ifdef TEST_PWM	
	while(RUN_FOREVER)
	{
		generate_primary_pwm(100,2302); //25% DCycle
		delay(5000);
		
		generate_primary_pwm(100,4605); //50% DCycle
		delay(5000);
		
		generate_primary_pwm(100,6907); //75% DCycle
		delay(5000);
	 
 
	
	}
#endif
	while(RUN_FOREVER)
	{
		if( (rightSide >= IN_TRACK_LOW_RANGE) && (rightSide <= IN_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(RIGHT_MOTOR,LOW_SPEED);
		}
		else if( (rightSide >= OUT_TRACK_LOW_RANGE) && (rightSide <= OUT_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(RIGHT_MOTOR,MEDIUM_SPEED);
		}	
		else if( (rightSide >= NO_TRACK_LOW_RANGE) && (rightSide <= NO_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(ALL_MOTORS,STOP_SPEED);
		 
		}
		
		if( (leftSide >= IN_TRACK_LOW_RANGE) && (leftSide <= IN_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(LEFT_MOTOR,LOW_SPEED);
		}
		else if( (leftSide >= OUT_TRACK_LOW_RANGE) && (leftSide <= OUT_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(LEFT_MOTOR,MEDIUM_SPEED);
		}	
		else if( (leftSide >= NO_TRACK_LOW_RANGE) && (leftSide <= NO_TRACK_HIGH_RANGE) )
		{
			generate_primary_pwm(ALL_MOTORS,STOP_SPEED);
		 
		}		 
	 
	
	
	
	
	}	
	
}

	
void tglePort(void)
{
	static char ch=0;
	if(ch == 0)
	{
		ch =1;
		PORTBbits.RB4 = 0x0;
	
		
	}
	else
	{   
		ch = 0;
		PORTBbits.RB4 = 0x1;
	
	}
}
	
int delay(long int period)
{

	long int i=0,j=0;
	for(i=0;i<3;i++)
		for(j=0;j<period;j++);
	 
	return 0;
}
int initPorts(void)
{
	LATA  = 0x0000; 				// set latch levels
	TRISA = 0x0000; 				// set IO as outputs
	LATB  = 0x0000; 				// set latch levels
	TRISB = 0x0000; 				// set IO as outputs
	OSCCON=0x0680;
	
	TRISAbits.TRISA3 = 1;   //User Input switch- Defineing as input
	
	PORTBbits.RB4 = 0x1;   //Set High, which make LED to Turn OFF
	PORTAbits.RA4 = 0x1;   //User LEd, turn off
	
	
	return 0;
}	
	
int main()
{
	initPorts();
	InitUART1();
	
	initTmr(3);
	initAnalog();  
	initPwm();
    initTmr(2);
    
    motorControl(EN_MOTORS);
	generate_primary_pwm(100,0x002b);
	checkAngNChangeDir();
	while(1)
   {
		#ifdef BLINK_LED	   
      		 
      		tglePort();
      		delay(50000); 
		#endif 
		
		
   	    
   	    delay(50);
  	  	    
   }
}
   