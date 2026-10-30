#include<lpc21xx.h>
#include<string.h>
#include<stdio.h>

#define RED_LED (1<<17)
#define YELLOW_LED (1<<18)
#define GREEN_LED (1<<19)
#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define buz (1<<21)

typedef unsigned int u32;
typedef unsigned char u8;

void delay_sec(unsigned int );
void delay_ms(unsigned int);

void uart_init(unsigned int);
void uart_tx(unsigned char);
unsigned char uart_rx(void);
void uart_string(char *);
void uart_float(float);
void uart_int(int );

void lcd_init(void);
void lcd_cmd(unsigned int);
void lcd_data(unsigned int);
void lcd_string(unsigned char *);

void EINT0_HANDLER(void) __irq;
void config_eint0(void);
void adc_init(void);
u32 adc_read(int);

void ultrasonic_init(void);
u32 ultrasonic_read(void);
float temparature(void);
int water_level(void);

void i2c_init(void);
void i2c_send(u8 ,u8,u8);
u8 i2c_receive(u8 ,u8);

void servo_init(void);
void servo_0deg(void);
void servo_90deg(void);
void servo_180deg(void);
void wifi_connect(void);
void can1_init(void);
typedef struct
{
unsigned int id;
unsigned int rtr;
unsigned int  dlc;
unsigned int  byteA;
unsigned int  byteB;
unsigned int ff;
}CAN1; 






