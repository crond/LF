#include "linefollower_header.h"

int delay(int cnt)
{
	int i=0,j=0;
	for(i =0;i<cnt;i++)
	{
		for(j=0;j<cnt;j++)
		{
		}	
	}
	return 0;	
}
int toggleLed(void)
{
	PORTB = 0x00;
	if(1)
	{
		PORTB = 0xAA;
		delay(200);
		PORTB	=0x00;//~(PORTB);
		delay(200);
	}	
	return 0;	
}	
int initAnalog(void)
{
	/**
	rserved2,continuous mode,multi channel,mode seq:00,GO/DONE:1,start:1
	**/
	ADCON0 = 0b00110011;
	
	//AN2,AN3 are voltage pins, not analog pins-11,RO-0,EN FIFO-1,4 RO bits-0000
	ADCON1 = 0b11010000;
	
	//Right justified-1,start conversion immediately -0000,internal osc-111
	ADCON2 = 0b10000111;
	
	//disble int -11,RO-0,all possible triggers that start A/D seq -11111
	ADCON3 = 0b11011111;
	
	//disable Group D-11,Enable Group B-00[AN1],Disable Group C-11,Enable Group A-00[AN0]
	ADCHS = 0b11001100;
	
	//Enabling Analog Pins. AN0 and AN1
	ANSEL0 = 0b00000011;
	ANSEL1 = 0b00000000;
	
	//configuring thre corresponding Analog Pins as Input
	TRISA  = 0xFF;
	 
	return 0;
}
int init(void)
{
	//8Mhx interal osc
	OSCCON	= 0x73;
	
	//For LED
	PORTB	= 0x00;
	TRISB	= 0x00;
	
	//PIN ctrl for I2C
	TRISD	=0xFF;
	PORTD	=0xFF;
	
	//Clk -High,I2C Pin-Enble,Addr-7 bit
	SSPCON = 0x36;
	
	//Enable general,peripheral,ssp interrupts
	//GIE=1;
//	PEIE=1;
//	SSPIE=1;
	
	return 0;
}		




int main()
{
	short int angVal=0;
	init();
	initAnalog();
//	PORTB=0xAA;
	toggleLed();
	toggleLed();
		toggleLed();
			toggleLed();
				toggleLed();
	
	
	while(1);	
	{
		angVal = ADRESH;
		angVal = (angVal << 8) |ADRESL ; 
		ADIF =0;
		delay(angVal);
		toggleLed();
		/**
		rserved2,continuous mode,multi channel,mode seq:00,GO/DONE:1,start:1
		**/
		ADCON0 = 0b00110011;
	}
	return 0;

}
