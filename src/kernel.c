#include "uart.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "gic400.h"
#include "lib.h"

void kernel_main(void)
{
	uart_init();
	
	printk("************\r\n");
	printk("           *****>\r\n");
	printk("Welcome Snake OS!\r\n");
	printk("Welcome Snake OS!\r\n");
	printk("Welcome Snake OS!\r\n");
	
	init_timer();
	init_interrupt_controller();
	enable_irq();

	ASSERT(0);
	 
	while(1)
	{		
		;
	}
	
}
