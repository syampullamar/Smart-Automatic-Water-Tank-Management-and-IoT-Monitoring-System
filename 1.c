#include"header.h"
u32 mode=0;
int main()
{
u32 temp,t;
u32 water,distance=62;
u8 h,h1,m,s,d,mo,y;
u32 add=0,i,len;
char s1[20],s2[20];
 
IODIR0|=buz;
IODIR0|=RED_LED|YELLOW_LED|GREEN_LED;
IOSET0|=RED_LED|YELLOW_LED|GREEN_LED;
i2c_init();
uart_init(9600);
lcd_init();
config_eint0();
adc_init();
ultrasonic_init();
servo_init();
//can1_init();
//wifi_connect();
	 i2c_send(0xD0, 0x04, 0x12);
	 i2c_send(0xD0, 0x05, 0x10);
	 i2c_send(0xD0, 0x06, 0x26);
	 i2c_send(0xD0, 0x2, 0x16);//set hrs
	 i2c_send(0xD0, 0x1, 0x31);//set min
	 i2c_send(0xD0, 0x0, 0x55);//set secs
mode=0;
uart_string("===============================================\r\n");
uart_string("      SMART WATER TANK MANAGEMENT\r\n");
uart_string("===============================================\r\n");
uart_string("\r\ncontroller: LPC2129 ARM7\r\n");
uart_string("project status: running\r\n");
						  	  
while(1)
{

temp=temparature();
water=water_level();
distance=ultrasonic_read();	 //p0.10,p0.11(trig,echo	 
	d=i2c_receive(0XD1,0X04);
		mo=i2c_receive(0XD1,0X12);
		y=i2c_receive(0XD1,0X26);
		h=i2c_receive(0xD1,0x2);//read hrs	
		m=i2c_receive(0xD1,0x1);//read mins
		s=i2c_receive(0xD1,0x0);//read secs	
if(mode==1)
{
uart_string("\r\n MANUAL MODE\r\n");
	if(sw1==0)
	{
	while(sw1==0);
	uart_string("\r\n pump status  : ON\r\n");
    uart_string("\r\n relay status : ON\r\n");
    uart_string("\r\n valve status : OPEN\r\n");
	
	 servo_180deg();
	 delay_ms(200);
	}
	else if(sw2==0)
	{
	while(sw2==0);
	uart_string("\r\n pump status  : OFF\r\n");
    uart_string("\r\n relay status : OFF\r\n");
    uart_string("\r\n valve status : CLOSE\r\n");
	
	servo_0deg();
	delay_ms(200);
	}
	    if(water<30)
        {
        uart_string("\r\nLOW WATER LEVEL\r\n");
        IOSET0|=RED_LED|YELLOW_LED;
        IOCLR0|=GREEN_LED;
		}
		else if(water>=30 && water<=40)
        {
        uart_string("\r\n MEDIUM WATER LEVEL\r\n");
        IOSET0|=RED_LED|GREEN_LED;
        IOCLR0|=YELLOW_LED;  
        }
		else if(water>=40)
        {
        IOSET0|=buz;
        delay_ms(200);
        IOCLR0|=buz;
        uart_string("\r\nHIGH WATER LEVEL\r\n");
        IOSET0|=GREEN_LED|YELLOW_LED;
        IOCLR0|=RED_LED;
		}
}	  
else if(mode==0)
{
uart_string("\r\nAUTOMATIC MODE\r\n");
  if(water<30)
  {
   uart_string("\r\nLOW WATER LEVEL\r\n");
   IOSET0|=RED_LED|YELLOW_LED;
   IOCLR0|=GREEN_LED;

   servo_180deg();
   uart_string("\r\n pump status  : ON\r\n");
   uart_string("\r\n relay status : ON\r\n");
   uart_string("\r\n valve status : OPEN\r\n");
   delay_ms(200);   
  }
  else if(water>=30 && water<=40)
  {
   uart_string("\r\n MEDIUM WATER LEVEL\r\n");
   IOSET0|=RED_LED|GREEN_LED;
   IOCLR0|=YELLOW_LED;  
  }
  else if(water>=40)
  {
  IOSET0|=buz;
  delay_ms(200);
  IOCLR0|=buz;
  uart_string("\r\nHIGH WATER LEVEL\r\n");
  IOSET0|=GREEN_LED|YELLOW_LED;
  IOCLR0|=RED_LED;

  servo_0deg();
  uart_string("\r\n pump status  : OFF\r\n");
  uart_string("\r\n relay status : OFF\r\n");
  uart_string("\r\n valve status : CLOSE\r\n");
  delay_ms(500);
  }		
}
uart_string("\r\ntemparature is  ");
uart_float(temp);
uart_string("\r\n");

uart_string("water  is  ");
uart_int(water);
uart_string("\r\n");

uart_string("distance  is  ");
uart_int(distance);
uart_string("\r\n");

		 uart_string("\r\nRTC DATE:  ");
		 uart_tx((d/16)+48);
		 uart_tx((d%16)+48);
		 uart_tx(':');
		 uart_tx((mo/16)+48);
		 uart_tx((mo%16)+48);
		 uart_tx(':');
		 uart_string("20");
		 uart_tx((y/16)+48);
		 uart_tx((y%16)+48);
		 uart_tx(':');
		 uart_string("\r\n");

    	h1=h&0x1f;
		uart_tx((h1/16)+48);
		uart_tx((h1%16)+48);
		uart_tx(':');
		uart_tx((m/16)+48);
		uart_tx((m%16)+48);
		uart_tx(':');
		uart_tx((s/16)+48);
		uart_tx((s%16)+48);

		 if(h>>5&1)
		 uart_string("  PM");
		 else
		 uart_string("  AM");
		 uart_string("\r\n");

		sprintf(s1,"t=%d ,time:%d %d",temp,h1,mo);
 	len=strlen(s1);
		add=0;
for(i=0;i<=len;i++)
{
i2c_send(0xa0,add++,s1[i]);
delay_ms(20);
}
add=0;
for(i=0;i<=len;i++)
{
s2[i]=i2c_receive(0xa1,add++);
delay_ms(20);
}
uart_string(s1);
uart_string("\r\n");
 uart_string(s2);
 uart_string("\r\n");
 if(strncmp(s1,s2,len-1)==0)
 {
 uart_string("\r\nDATA SAVED\r\n");
 }
 else
 {
 uart_string("DATA NOT SAVED\r\n");
 }	  	  		
//			can_data[0]=(u32)water;								
		//	can_data[1]=(u32)temp;									
			//can_tx(0x100,can_data,2);
	 delay_ms(3000);
}
} 

	/* i2c_send(0xa0,add,temp);
		 delay_ms(30);
		 t=i2c_receive(0xa1,add++);
		  if(temp==t)
		  {
          uart_string("\r\nDATA SAVED\r\n");
           }
           else
           {
           uart_string("DATA NOT SAVED\r\n");
           }	*/