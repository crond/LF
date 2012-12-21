#include "linefollower_header.h"

void eusart_init(unsigned char usart_mode, char tx_mode, 
	unsigned long fosc, unsigned int baud)
{
	float baud1=2.4;
	TRISC = 0xC0;    //TX-RX Enable
	switch(usart_mode)
	{
		case ASYNC_MODE:
		{
			BAUDCTL	= 0x08;
			SPBRG 	= 0x33; //2.4; //(int)(8000000/(16UL * 9600) -1); //0x0C//but o/p is coming in 38400 
			RCSTA 	= 0x90;	// Enable serial comm, 8-Bit mode, Enables continous RX
			TXSTA 	= 0x24;	// 8-Bit mode, Enable TX
           	break;
		}
		case SYNC_MASTER_MODE:
		{
			break;
		}
		case SYNC_SLAVE_MODE:
		{
			break;
		}		
	}
}

void uart_send_byte(unsigned char byte)
{
	while(!TXIF)
	{
		continue;
	}
	
	TXREG = byte;
}

unsigned char uart_recv_byte(void)
{
	while(!RCIF)
	{
		continue;
	}
	return RCREG;
}

void uart_send_pkt(unsigned char *pkt, int size)
{
	int i,j=0;
	for(i = 0; i < size; i++)
	{
		uart_send_byte(pkt[i]);
	}
     
}

unsigned char uart_recv_pkt(unsigned char *pkt, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		pkt[i] = uart_recv_byte();
	}
	return size;
}
