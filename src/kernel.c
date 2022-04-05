#include "uart.h"
#include "print.h"
#include "debug.h"

void kernel_main(void)
{
	uart_init();
	
	printk("************\r\n");
	printk("           *****>\r\n");
	printk("Welcome Snake OS!\r\n");
	printk("Welcome Snake OS!\r\n");
	printk("Welcome Snake OS!\r\n");
	
	ASSERT(0);
	 
	while(1)
	{		
		;
	}
	
}