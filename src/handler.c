#include "stdint.h"
#include "print.h"
#include "timer.h"
#include "gic400.h"

static uint32_t get_irq_number(void)
{
	return in_word(ICC_ACK);
}

void handler(uint64_t numid, uint64_t esr, uint64_t elr)
{
	uint32_t irq = 0;
	
	switch (numid)
	{
		case 1:
			printk("sync error at %x: %x\r\n", elr, esr);
			while(1){}
			break;
			
		case 2:
			irq = get_irq_number();
			if (irq == 64)
			{
				timer_interrupt_handler();
			}
			else
			{
				printk("unknow irq\r\n");
				while(1){}
			}
			
			out_word(ICC_EOI, irq);
			break;
			
		default:
			printk("unknown exception\r\n");
			while(1){}
			break;
		
	}
	
}
