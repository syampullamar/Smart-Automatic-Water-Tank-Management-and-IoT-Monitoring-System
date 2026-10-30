#include <LPC21xx.H>

#include"header.h"
extern u32 mode;

void EINT0_HANDLER(void) __irq
{
mode^=1;//toggle
EXTINT=1;//clears the einto interrupt
VICVectAddr=0;//signals the vic that the interrupt service routine has finished
}

void config_eint0(void)
{
PINSEL1|=1;//Selects an alternate pin function through PINSEL1
EXTMODE=1;//configure EINT0 as edge-sensitive
EXTPOLAR=0;//Selects falling edge detection for EINTO
VICIntSelect=0;//Cionfigure all VIC interrupt sorce as IRQ rather than FIQ
VICVectCntl0=14|(1<<5);
VICVectAddr0=(unsigned int)EINT0_HANDLER;
VICIntEnable=(1<<14);
}


