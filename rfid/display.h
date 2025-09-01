#include <LPC21xx.H>
#include "delay.h"

#define rs 1<<8
#define en 1<<9
#define pin 0xff<<10


typedef	unsigned char uc   ;

void lcd_init(void);
void lcd_cmd(uc);
void lcd_data(uc);
void lcd_str(char*);
void lcd_int(int);

void lcd_init(void)
{
 IODIR0|=pin|en|rs;
 lcd_cmd(0x01);
 lcd_cmd(0x02);
 lcd_cmd(0x0c);
 lcd_cmd(0x38);
}

void lcd_cmd(uc data)
{
  IOCLR0=pin;
  IOSET0=data<<10;
  IOCLR0=rs;
  IOSET0=en;
  delay_ms(2);
  IOCLR0=en;
}

void lcd_data(uc data)
{
  IOCLR0=pin;
  IOSET0=data<<10;
  IOSET0=rs;
  IOSET0=en;
  delay_ms(2);
  IOCLR0=en;
}

void lcd_str(char *s)
{	 int i;
 for(i=0;s[i];i++)
 lcd_data(s[i]);
}
void lcd_int(int n)
{ char num[20];
int i;
  if(n<0){
  lcd_data('-');
  n=-n;
  }
  for(i=0;n;n/=10,i++)
	 num[i]=n%10;
  for(i--;i>=0;i--)
  lcd_data(num[i]+48);
}


void lcd_float(float n)
{
	 int i=n;
	 lcd_int(i);
	 n=n-i;
	 lcd_data('.');
	 lcd_int(n*100)	;
}



