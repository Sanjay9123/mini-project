#include <LPC21xx.H>
#include "display.h"
#include "uart.h"


int main()
{

lcd_init();
uart0_conf();
uart0_interrupt();
lcd_cmd(0x80);

while(1)
{
	lcd_str(store);
	delay_ms(2000);
	lcd_cmd(0x01);
}



}
