#include"header.h"
void adc_init()								   
{
PINSEL1|=0X15400000;
ADCR|=0X00200400;//sets bit 21(powers up) and 10(ADC channel 2)
}

#define DONE ((ADDR>>31)&1)
u32 adc_read(int ch_num)
{
int res;
ADCR|=(1<<ch_num);//select channel number
ADCR|=(1<<24);//start ADC
while(DONE==0);//wait for a/d conversion
ADCR&=~(1<<ch_num);//disselect adc
ADCR&=~(1<<24);//stop ADC
res=(ADDR>>6)&0X3FF;//Extract 10bit ADC result
return res;
}

