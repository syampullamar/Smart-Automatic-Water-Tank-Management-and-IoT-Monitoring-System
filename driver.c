#include"header.h"
unsigned int res,pclk;
void uart_init(unsigned int baud)
{
if(VPBDIV==0X0)
pclk=15000000;
else if(VPBDIV==0X01)
pclk=60000000;
else if(VPBDIV==0X02)
pclk=30000000;

res=pclk/(16*baud);
PINSEL0|=0X05;
U0LCR=0X83;
U0DLL=res&0XFF;
U0DLM=((res>>8)&0XFF);
U0LCR=0X03;
}
#define THRE ((U0LSR>>5)&1)
void uart_tx(unsigned char data)
{
U0THR=data;
 while(THRE==0);
}

#define RDR (U0LSR&1)
unsigned char uart_rx()
{
while(RDR==0);
return U0RBR;
}

void uart_string(char *ptr)
{
while(*ptr!=0)
{
uart_tx(*ptr);
ptr++;
}
}
void uart_int(int num)
{
int a[20],i;
if(num<0)
{
num=-num;
uart_tx('-');
return;
}
if(num==0)
{
uart_tx('0');
return;
}
for(i=0;num;num/=10,i++)
{
a[i]=num%10+48;
}
for(i=i-1;i>=0;i--)
{
uart_tx(a[i]);
}
}
void uart_float(float f)
{
int num,n1;
if(f==0)
{
uart_tx(0);
return;
}
if(f<0)
{
f=-f;
uart_tx('-');
}
num=(int)f;
uart_int(num);
uart_tx('.');
n1=(f-num)*100;
uart_int(n1);
}









