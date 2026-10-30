#include"header.h"
#define TRIG (1<<12)
#define ECHO (1<<13)
void ultrasonic_init(void)
{
IODIR0|=TRIG;
IODIR0&=~ECHO;
IOCLR0=TRIG;
}

u32 ultrasonic_read(void)
{
 u32 count=0,distance;	  
  IOCLR0=TRIG;
 delay_us(2);
 IOSET0=TRIG;
 delay_us(10);
IOCLR0=TRIG;

while(!(IOPIN0 & ECHO));

while(IOPIN0 & ECHO)
{
count++;
delay_us(1);
if(count>30000)
{
uart_string("timeout\r\n");
return 0;
}
}
distance=count/58;
return distance;
}
			




