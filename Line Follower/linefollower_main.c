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
	
		//configuring thre corresponding Analog Pins as Input
	TRISA  = 0xFF;
	
	//Enabling Analog Pins. AN0 and AN1
	ANSEL0 = 0b00000011;
	ANSEL1 = 0b00000000;
	
	
	 
	
	//AN2,AN3 are voltage pins, analog ref-00,RO-0,EN no FIFO-0,4 RO bits-0000
	//ADCON1 = 0b00000000;
	
		/**
	rserved2,continuous mode,single channel-0,mode seq:00,GO/DONE:0,start:1
	**/
	ADCON0 = 0b00100001;
	
	//Left justified0,start conversion immediately -0000,internal osc-111
	ADCON2 = 0b00000111;
	
	//enable int -00,RO-0,all possible triggers that start A/D seq -11111
	//ADCON3 = 0b00011111;
	
		//Enabling the Int
//	GIE=1;
//	PEIE=1;
//	ADIE=1;
//	ADIF=0;
	
	
	
 
	delay(500);
 
	 
	
	//disable Group D-11,disable Group B-00[AN1],Disable Group C-11,Enable Group A-00[AN0]
	//ADCHS = 0b11111100;
	
	 
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
	//SSPCON = 0x36;
	
	//Enable general,peripheral,ssp interrupts
	//GIE=1;
//	PEIE=1;
//	SSPIE=1;
	
	return 0;
}		




int main()
{
	short int angValL=0,angValH=0;
    char buffer[32];
	init();
//	initAnalog();
	eusart_init(ASYNC_MODE,0,0,0);
	
 
	toggleLed();
	toggleLed();
	toggleLed();
	toggleLed();
	toggleLed();
 	
 	if(0)
 	{
	  uart_send_pkt("FUCK-Started\n",(int)25);
	  delay(500);
	  uart_send_pkt("FUCK-In Prograss\n",(int)25);
	  delay(500);
	  uart_send_pkt("FUCK-Finished\n",(int)25);
	  delay(500);	
	 }
	 
	 	
 uart_send_pkt("started\n",8);
	GO_nDONE =1;
	while(1)	
	{
	    	 
		while ((GO_nDONE));

		angValH =  ADRESH;
		//angVal = (angVal << 8) |ADRESL ; 
		angValL =  ADRESL ; 
		ADIF =0;
	 
	 
		
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"0x%x 0x%x\n",angValH,angValL);
		uart_send_pkt(buffer,strlen((const char *)buffer));
		
		GO_nDONE =1;
		delay(500);
	}
	return 0;

}
