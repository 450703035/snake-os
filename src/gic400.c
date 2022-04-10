#include "stdint.h"
#include "print.h"
#include "lib.h"
#include "gic400.h"

void init_interrupt_controller(void)
{
	// 1.0 disable distributor and cpu interface
	out_word(DIST, 0);
	out_word(CPU_INTERFACE, 0);
	
	// 2.0 set the interrupt priority in cpu interface; support 0-255
	// higher the number, the lower priority, all interrupt can processed by interface
	out_word(ICC_PR, 0xff); 
	
	// 3.0 configure the distributor
	// priority in cpu distributor  31:24	23:16	15:8	7:0; 4 interruptpriority 
	out_word(ICD_PR + 64, 0);
	//uart irq number=(96+57)/4=38 offset=38*4
	out_word(ICD_PR + 38*4, 0);
	
	// processor target interrupt which indicates which cpu interface the interrupt will be forwarded toascii
	out_word(ICD_PTR + 64, 1); //only cpu0
	out_word(ICD_PTR + 38*4, 0x100); //only cpu0
	
	// set sensitivity of the timer interrupt 2bit 1bit-edge trigered 0-level trigered
	out_word(ICD_ICFGR + 16, 2); 
	// uart irq number(96+57)/16=9  (96+57)%16=9 offset=9*4=36  9*2=18
	out_word(ICD_ICFGR + 36, 0x80000);
	
	// 4.0 enable register
	// timer irq number 64/32 = 2  second register
	// timer irq number 64 offset = 2*4bytes=8  add+8 byte
	out_word(ICD_ISENABLE + 8, 1);
	// uart irq number (96+57)/32 = 4  offset4*4=16  (96+57)%32=25
	out_word(ICD_ISENABLE + 16, (1 << 25));
	
	// 5.0 enable cpu interface and distrubutor
	out_word(DIST, 1);
	out_word(CPU_INTERFACE, 1);
}