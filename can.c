#include<lpc21xx.h>
#include"header.h"
void can1_init(void)
{
VPBDIV=1;
PINSEL1|=0X4000;
C1MOD=1;
C1BTR=0X001C001D;
AFMR=2;
C1MOD=0;
}

#define TCS ((C1GSR>>3)&1)
void can1_tx(CAN1 v)
{
C1TID1=v.id;
C1TFI1=v.dlc<<16;
if(v.rtr==0)
{
C1TDA1=v.byteA;
C1TDB1=v.byteB;
}
else
C1TFI1=(1<<30);
C1CMR=0X21;
while(TCS==0);
}
void can1_parameter(u8 t,u8 w,u8 d)
{
CAN1 MSG;
MSG.id=0X301;
MSG.rtr=0;
MSG.dlc=8;
MSG.byteA=0;
MSG.byteA|=t;
MSG.byteA|=w<<8;
MSG.byteA|=d<<16;
can1_tx(MSG);
}
