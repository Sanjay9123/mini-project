#include <lpc21xx.h>
void uart0_tx(char c);
void uart0_str(char *s);

void uart0_isr()__irq
{
	  char in_temp=U0IIR;
						
	  
      VICVectAddr=0;
}


void uart0_conf()
{
	PINSEL0|=0X05;
	U0LCR=0X83;
    U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}


void uart0_interrupt()
{
     VICVectCntl0=0x20|6;
	 VICVectAddr0=(int)uart0_isr;
	 U0IER=1;
 	 
}
void uart0_str(char *s)
{
		while(*s)
		uart0_tx(*s++);
}


void uart0_tx(char c)
{
		U0THR=c;
	    while(((U0LSR>>5)&1)==0);
}

