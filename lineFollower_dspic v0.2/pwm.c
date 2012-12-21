#include "lr_header.h" 
 
 
void initPwm(void)
{
	OC1R	= 0x002b;
	
	//Mapping OC1-OC4 PB9 as OC1 , RB8=OC2, RB7=OC3, RB6=OC4
	RPOR3 = 0b0001010000010101;
	RPOR4 = 0b0001001000010011;
 
	
	//setting as o/p
	TRISBbits.TRISB6	= 0;//output
	TRISBbits.TRISB7	= 0;//output
	TRISBbits.TRISB8	= 0;//output
	TRISBbits.TRISB9	= 0;//output
	
	//Init the starting PWM
	OC1R	= 0x002b;
	OC2R	= 0x002b;  
	OC3R	=0x002b; 
	OC4R	= 0x002b;  
 
	
	//configuring the OC ctrl regs
	OC1CONbits.OCSIDL = 0; //continue oper when CPU idle
	OC1CONbits.OCTSEL = 0; //Timer -2 as source
	OC1CONbits.OCM = 0b110; //PWM mode, fault pin disabled
	
	OC2CONbits.OCSIDL = 0; //continue oper when CPU idle
	OC2CONbits.OCTSEL = 0; //Timer -2 as source
	OC2CONbits.OCM = 0b110; //PWM mode, fault pin disabled
	
	OC3CONbits.OCSIDL = 0; //continue oper when CPU idle
	OC3CONbits.OCTSEL = 0; //Timer -2 as source
	OC3CONbits.OCM = 0b110; //PWM mode, fault pin disabled
	
	
	OC4CONbits.OCSIDL = 0; //continue oper when CPU idle
	OC4CONbits.OCTSEL = 0; //Timer -2 as source
	OC4CONbits.OCM = 0b110; //PWM mode, fault pin disabled
	
	
	
}

int generate_primary_pwm(int channel,long int dutyCycle)
{
 
	switch(channel)
 	{
		case 1:
			OC1RS   = dutyCycle;
			break;
	    case 2:
			OC2RS   = dutyCycle;
			break;
	    case 3:
			OC3RS   = dutyCycle;
			break;
	    case 4:
			OC4RS   = dutyCycle;
			break;
		case 100:
			OC1RS   = dutyCycle;
			OC2RS   = dutyCycle;
			OC3RS   = dutyCycle;
			OC4RS   = dutyCycle;
			break;
	  
	    default:
			break;
	    		
	}		
	return 0;
}

int motorControl(char function)
{
	if(function == EN_MOTORS)
	{
		PORTBbits.RB5 = 0x1; //Set High Voltage	
	}
	else if(function == DIS_MOTORS)
	{
		PORTBbits.RB5 = 0x0; //Set 0v voltage	
	}
	else
	{
		return -1;
	}		
		
	return 0;
}	
