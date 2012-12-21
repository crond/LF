#include <stdio.h>
#include "htc.h"
#include "string.h"

#define ASYNC_MODE 			0
#define SYNC_MASTER_MODE 	1
#define SYNC_SLAVE_MODE		2

#define TX_8_BIT	0
#define TX_9_BIT	1


int init(void);
int delay(int cnt);
int toggleLed(void);
void eusart_init(unsigned char usart_mode, char tx_mode, unsigned long fosc, unsigned int baud);
void uart_send_byte(char byte);
unsigned char uart_recv_byte(void);
void uart_send_pkt(unsigned char *pkt, int size);
unsigned char uart_recv_pkt(unsigned char *pkt, int size);