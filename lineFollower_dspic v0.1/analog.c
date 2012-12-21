  #include "lr_header.h"
  
  
 char buffer[128],G_anPinChangeFlag=0;
 
 extern int  idx,Counter,an0Val,an1Val,an2Val,an3Val,an4Val,an5Val,rightSide,leftSide;
  extern unsigned long int G_userInput;
 int initAnalog(void)
{
	AD1PCFGLbits.PCFG0 =0; //AN0 as Analg PIN
	AD1PCFGLbits.PCFG1 =0; //AN1 as Analg PIN
	AD1PCFGLbits.PCFG2 =0;
	AD1PCFGLbits.PCFG3 =0;
	AD1PCFGLbits.PCFG4 =0;
	AD1PCFGLbits.PCFG5 =0;

 
	
	TRISAbits.TRISA0	= 1;//input
	TRISAbits.TRISA1	= 1;//input
	TRISBbits.TRISB0	= 1;//input
	TRISBbits.TRISB1	= 1;//input
	TRISBbits.TRISB2	= 1;//input
	TRISBbits.TRISB3	= 1;//input
	
 
	
	AD1CON2bits.VCFG = 0b000; //setting voltage reference to MC VOltage
	
	AD1CON1bits.FORM = 0b00;   //Integer values as analog Output
	AD1CON1bits.SSRC = 0b0000; //Decides, when to stop sampling and start Analog Conversion.
								//Here, by clearing the Sample Bit.
	AD1CON1bits.ASAM   = 1;       //Start the conversion immediately, after sampling End
	AD1CON1bits.AD12B  = 0;		// 10-bit ADC operation
	
	AD1CON2bits.CSCNA = 1;		// Scan Input Selections for CH0+ during Sample A bit
	AD1CON2bits.CHPS  = 0b11;		// Converts CH0,CH1,CH2
	AD1CON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
	AD1CON3bits.ADCS = 0b00111111;  //ADC conversion , clock select bits. 
	AD1CON2bits.SMPI    = 0b0000; //sample at every time
	
	AD1CSSLbits.CSS0=1;//AN0 for input scan
	
	 
	 
    IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
    IEC0bits.AD1IE = 1;			// Enable A/D interrupt 
        	
	delay(1000);
	
	AD1CON1bits.ADON=0x1;   //Start the Analog Functionality
	return 0;
}
 
   
/*================================================================================
_ADC1Interrupt(): ISR name is chosen from the device linker script
=================================================================================*/
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
 	G_userInput =LATA;// & 0x08;
	idx++;	
	if(idx == MAX_BUFF_SIZE)
	{
		idx = 0;
		tglePort();
	
		if(G_anPinChangeFlag == 0)
		{
   	    	G_anPinChangeFlag =1;
   	    	an0Val = ADC1BUF0;
   	    	
   	    	AD1CSSLbits.CSS0=0;//exclude AN0 for input scan
   	    	AD1CSSLbits.CSS2=0;//exclude AN2 for input scan
   	    	AD1CSSLbits.CSS3=0;//exclude AN3 for input scan
   	    	AD1CSSLbits.CSS4=0;//exclude AN4 for input scan
   	    	AD1CSSLbits.CSS5=0;//exclude AN5 for input scan
   	    	
   	    	AD1CSSLbits.CSS1=1;//AN1 for input scan
   	    
  		} 	    
  		else if(G_anPinChangeFlag == 1)
  		{
	  		an1Val = ADC1BUF0;
	  		//leftSide=an1Val;
	  		G_anPinChangeFlag =2;
	  		
	  		AD1CSSLbits.CSS0=0;
	  		AD1CSSLbits.CSS1=0;//exclude AN1 for input scan
	  		AD1CSSLbits.CSS3=0;//exclude AN3 for input scan
   	    	AD1CSSLbits.CSS4=0;//exclude AN4 for input scan
   	    	AD1CSSLbits.CSS5=0;//exclude AN5 for input scan
   	    	
   	    	AD1CSSLbits.CSS2=1;//exclude AN2 for input scan
   		} 
   		else if(G_anPinChangeFlag == 2)
  		{
	  		an2Val = ADC1BUF0;
	  	//	leftSide=an2Val;
	  		G_anPinChangeFlag =3;
	  		
	  		AD1CSSLbits.CSS0=0;
	  		AD1CSSLbits.CSS1=0;//exclude AN1 for input scan
	  		AD1CSSLbits.CSS2=0;//exclude AN2 for input scan
   	    	AD1CSSLbits.CSS4=0;//exclude AN4 for input scan
   	    	AD1CSSLbits.CSS5=0;//exclude AN5 for input scan
   	    	
   	    	AD1CSSLbits.CSS3=1;//exclude AN3 for input scan
   		}
   		else if(G_anPinChangeFlag == 3)
  		{
	  		an3Val = ADC1BUF0;
	  	//	leftSide=an3Val;
	  		G_anPinChangeFlag =4;
	  		
	  		AD1CSSLbits.CSS0=0;
	  		AD1CSSLbits.CSS1=0;//exclude AN1 for input scan
	  		AD1CSSLbits.CSS2=0;//exclude AN2 for input scan
   	    	AD1CSSLbits.CSS3=0;//exclude AN3 for input scan
   	    	AD1CSSLbits.CSS5=0;//exclude AN5 for input scan
   	    	
   	    	AD1CSSLbits.CSS4=1;//exclude AN4 for input scan
   		}
   		else if(G_anPinChangeFlag == 4)
  		{
	  		an4Val = ADC1BUF0;
	  	//	leftSide=an4Val;
	  		G_anPinChangeFlag =5;
	  		
	  		AD1CSSLbits.CSS0=0;
	  		AD1CSSLbits.CSS1=0;//exclude AN1 for input scan
	  		AD1CSSLbits.CSS2=0;//exclude AN2 for input scan
   	    	AD1CSSLbits.CSS3=0;//exclude AN3 for input scan
   	    	AD1CSSLbits.CSS4=0;//exclude AN4 for input scan
   	    	
   	    	AD1CSSLbits.CSS5=1;//exclude AN5 for input scan
   		}
   		else if(G_anPinChangeFlag == 5)
  		{
	  		an5Val = ADC1BUF0;
	  	//	leftSide=an5Val;
	  		G_anPinChangeFlag =0;
	  		
	  		
	  		AD1CSSLbits.CSS1=0;//exclude AN1 for input scan
	  		AD1CSSLbits.CSS2=0;//exclude AN2 for input scan
   	    	AD1CSSLbits.CSS3=0;//exclude AN3 for input scan
   	    	AD1CSSLbits.CSS4=0;//exclude AN4 for input scan
   	    	AD1CSSLbits.CSS5=0;//exclude AN5 for input scan
   	    	
   	    	AD1CSSLbits.CSS0=1;
   		}               	
   	    	
		rightSide=(an0Val+an1Val+an2Val)/3;	 
	  	leftSide=(an3Val+an4Val+an5Val)/3;	 
	// 	rightSide = an0Val;
	// 	leftSide = an1Val;
   	    
	}
	 #ifdef SEND_DBG_MSG
	  	memset(buffer,0,sizeof(buffer));	
  	 	sprintf(buffer,
  	 		"\nAng:%d,%d,%d,%d,%d,%d,R:%d,L:%d UI:%d",
  	 		an0Val,an1Val,an2Val,an3Val,an4Val,an5Val,rightSide,leftSide,G_userInput );
	 	sendToUart(buffer);
	  #endif
	IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
}

