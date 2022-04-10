#include "stdint.h"
#include "print.h"
#include "timer.h"

static uint64_t ticks = 0;

void init_timer(void)
{
	// timer_clock=apb_clock/(pre_divider+1) 250000000/(0x7d+1)=1984126
	out_word(TIMER_PREDIV, 0x7d);
	
	// clock 2mhz, 1 second include 100 10ms;  1984126/100
	out_word(TIMER_LOAD, 19841);
		
	// bit5-enable interrupt  bit1-32bit counter  bit7-enable tiemr
	out_word(TIMER_CTL, 0b10100010);
}

void timer_interrupt_handler(void)
{
	uint32_t mask = in_word(TIMER_MSKIRQ);

	if (mask & 1)
	{
		if (ticks % 100 == 0)
		{
			printk("tiemr %u\r\n", ticks);
		}
		
		ticks++;
		out_word(TIMER_ACK, 1);
	}
}