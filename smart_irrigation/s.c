#include <LPC21xx.H>
#include "display.h"
#include "uart.h"

void ext0_conf(void);
int temp=0,temp1=0;
int main()
{
		uart0_conf();
		lcd_init();
		IODIR0|=1<<4;
		lcd_cmd(0x80);
		lcd_str("sanjay");
		uart0_str("AT\r\n");
		delay_sec(1);
		uart0_str("AT+CMGF=1\r\n");
		delay_sec(1);
		
		while(1)
		{
		if(((IOPIN0>>5)&1)==1)
		{
			if(!temp)
			{
			lcd_cmd(0x01);
			uart0_str("at+cmgs=\"+916379763262\"\r\n");
			delay_ms(500);
			uart0_str(" motor is on");
			delay_ms(500);
			uart0_tx(0x1A);
			delay_sec(2);
			lcd_str("motor on");
			IOCLR0=1<<4;
			}
			temp=1;
			temp1=0;
		}
		else
		{
			if(!temp1)
			{
			lcd_cmd(0x01);
	   	 	lcd_str("motor off");
			uart0_str("at+cmgs=\"+916379763262\"\r\n");
			delay_ms(500);
			uart0_str(" motor is off");
			delay_ms(500);
			uart0_tx(0x1A);
			delay_sec(2);
			IOSET0=1<<4;
			}
			temp1=1;
			temp=0;
		}
		}
}	


