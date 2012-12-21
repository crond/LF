#include <p33FJ64MC802.h>
#include <stdio.h>
#include <string.h>
// #include <htc.h>
#define  TMR1_PERIOD 0Xffff
//#define TEST_UART 1 

//CUstom Macros
#define RUN_FOREVER			1

#define	PORTFORPWM			PORTA
#define	TOT_TME_PRD			20

#define SET_LOW				0x0000
#define	SET_HIGH			0xFFFF
#define	DEFAULT_DELAY		30000
#define DEFAULT_LONG_DELAY	500000L
#define	MAX_IO				4

#define	A				0x01
#define	B				0x02

#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4		4

#define	TIMER_1			1
#define	TIMER_2			2
#define	TIMER_3			3
#define	TIMER_4			4

#define	PIN0_DTYCLE		10
#define	PIN1_DTYCLE		10
#define	PIN2_DTYCLE		10
#define	PIN3_DTYCLE		10
#define	PIN4_DTYCLE		10
#define	PIN5_DTYCLE		10
#define	PIN6_DTYCLE		10
#define	PIN7_DTYCLE		10

//#define BLINK_LED 1
 #define MAX_BUFF_SIZE 8
#define EN_MOTORS		0x10
#define DIS_MOTORS		0x01

//SPeed
#define FULL_SPEED	9211
#define LOW_SPEED FULL_SPEED/4
#define MEDIUM_SPEED FULL_SPEED/3
#define HIGH_SPEED FULL_SPEED/2
   
#define STOP_SPEED 0
    
 #define RIGHT_MOTOR 1
 #define LEFT_MOTOR  2
 #define ALL_MOTORS  100
//Robot Direction Values. for , dsPIC33FJ64MC802 .
/* 
#define IN_TRACK_LOW_RANGE		100  
#define IN_TRACK_HIGH_RANGE 	130 //0.35v
#define OUT_TRACK_LOW_RANGE 	40
#define OUT_TRACK_HIGH_RANGE	60
#define NO_TRACK_LOW_RANGE		140
#define NO_TRACK_HIGH_RANGE     1023
*/
#define IN_TRACK_LOW_RANGE		100  
#define IN_TRACK_HIGH_RANGE 	130 //0.35v
#define OUT_TRACK_LOW_RANGE 	30
#define OUT_TRACK_HIGH_RANGE	80
#define NO_TRACK_LOW_RANGE		140
#define NO_TRACK_HIGH_RANGE     1023

#define SEND_DBG_MSG		1

//Function Prototypes
void toggle_port(char port,long int delay);
int init_Timer( char tmrNum );
int init_io_port_time();

//Function Prototypes
 
int	init_mc(void);
int delay(long int period);
int generate_primary_pwm(int channel,long int dutyCycle);
int init_pwm_reg(void);
int generate_secondary_pwm(long int,float);
int init_port_val(void);
int init_Timer( char tmrNum );
int init_def_angle_io(int pinNum,long int dtyCyle);
int set_angle(int motorNum,float angle);
int pwm_test();
int test_uart(char);
void	InitUART1();
void InitUART2() ;
int	sendToUart(char* ch);
int long_delay(int count);
int generate_primary_pwm(int channel,long int dutyCycle);
void initPwm(void);
void initTmr(int id) ;
int motorControl(char function); 
int 	recvFromUart1(void);
int 	recvFromUart2(void);
int    initAnalog(void);
void tglePort(void);
