#include <LPC21xx.H>
#include "uart.h"
#include "display.h"
int main()
{
  uart0_conf();
	lcd_init();
	lcd_cmd(0x83);
	lcd_str("sanjay b");
	lcd_cmd(0xc3);
	lcd_str("V24CE9S8");
	uart0_str("sanjay");
	delay_ms(2000);
	uart0_interrupt();
	
	
	while(1)
	{
			
			switch(store-48)
			{
				case 1 :
					U0THR=store;
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("moving forward");
				  store=0;
				  break;
					
				case 2 :
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("moving backward");
				  store=0;
				  break;	
			
			case 3 :
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("moving right");
				  store=0;
			    break;
			
			case 4 :
					lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("moving left");
			    store=0;
				  break;
			
			}
			
	}
}

