#include"header.h"

float temparature()
{
float adc1,vout1,temp;
adc1=adc_read(0);		 //p0.27
vout1=(adc1*3.3)/1023;
temp=vout1/0.01;
return temp;
}

int water_level()
{
int adc2,w;
adc2=adc_read(1);		 //p0.28
w=(adc2*100)/1023;
return w;
}

