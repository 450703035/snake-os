#ifndef _MEMORY_H
#define _MEMORY_H

#include "stdint.h"

struct Page {
    struct Page* next;
};

#define KERNEL_BASE 0xffff000000000000
#define P2V(p) ((uint64_t)(p) + KERNEL_BASE)
#define V2P(v) ((uint64_t)(v) - KERNEL_BASE)

#define MEMORY_END  P2V(0x30000000)
#define PAGE_SIZE   (2*1024*1024)

#define PA_UP(v)    ((((uint64_t)v + PAGE_SIZE - 1) >> 21) << 21)
#define PA_DOWN(v)  (((uint64_t)v >> 21) << 21)

void* kalloc(void);
void kfree(uint64_t v);
void init_memory(void);


#endif
