#include <LPC21xx.H>
#include "display.h"
#include"string.h"
int cap1=0,cap2=0;
float sec=0,dis=10.0,speed;
char str[100];
void uart_conf(void);
void u0_str(char *s) ;
void timer1_isr(void)__irq
{
   if((T1IR>>6)&1)
   {  T1IR=1<<6;
	   cap1=T1CR2;
	}
	if((T1IR>>7)&1)
   {  T1IR=1<<7;
	   cap2=T1CR3;
	}
	VICVectAddr=0;
}
void cap_conf(void);

int main()
{ 
lcd_init();
lcd_cmd(0x83);
lcd_str("V24CE9S8");
lcd_cmd(0xc3);
lcd_str("sanjay b");
delay_sec(2);
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("speed");
cap_conf();
uart_conf();
 while(1)
{
  if((cap1!=0)&(cap2!=0))
  {
   VICIntEnable=0;
  	sec=(cap2-cap1)/15000000.0;
  	speed=(dis/sec);
	lcd_cmd(0x80);
	lcd_cmd(0x01);
	lcd_float(speed);
	delay_sec(2);
	cap1=0;
    cap2=0;
	speed=0;
  }
  lcd_cmd(0x01);
  VICIntEnable|=1<<5;
  
   
}
}



void cap_conf(void)
{
 PINSEL1|=0XD0;
 VICVectCntl0=0x20|5;
 VICVectAddr0=(int)timer1_isr;
 VICIntEnable|=1<<5;
 T1TCR=3;
 T1CCR=	0XD80;
 T1PR=0;
 T1TCR=1;

}
  void uart_conf(void)
{
  PINSEL0=5;
  U0LCR=0X83;
  U0DLM=0;
  U0DLL=97;
  U0LCR=0X03;
}

void u0_str(char *s)
{	 int i;
 for(i=0;s[i];i++){
 U0THR=(s[i]);
 while(((U0LSR>>5)&1)==0);
 }
}