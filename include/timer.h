#ifndef _TIMER_H_
#define _TIMER_H_
#include "memory.h"

#define BASE_ADDR 			P2V(0xfe000000)
//#define BASE_ADDR 			(0xfe000000)


#define TIMER_LOAD          (BASE_ADDR + 0xB400)
#define TIMER_CTL           (BASE_ADDR + 0xB408)
#define TIMER_ACK           (BASE_ADDR + 0xB40C)
#define TIMER_MSKIRQ        (BASE_ADDR + 0xB414)
#define TIMER_PREDIV        (BASE_ADDR + 0xB41c)
 
 
 void init_timer(void);
 void timer_interrupt_handler(void);
 
 #endif