#include "memory.h"
#include "debug.h"
#include "print.h"
#include "stddef.h"

extern char end;  // end of the kernel

static struct Page free_memory;

void* kalloc(void)
{
	struct Page *page_addres = free_memory.next;
	
	if (page_addres != NULL)
	{
		ASSERT((uint64_t)page_addres % PAGE_SIZE == 0); 		 // virtual address is page aligned.
		ASSERT((uint64_t)page_addres >= (uint64_t)&end);		 // virtual address is not within the kernel
		ASSERT((uint64_t)page_addres + PAGE_SIZE <= MEMORY_END); // free memory limits
		
		free_memory.next = page_addres->next;
	}
	
	return page_addres;
}

void kfree(uint64_t v)
{
	ASSERT(v % PAGE_SIZE == 0); 		 // virtual address is page aligned.
	ASSERT(v >= (uint64_t)&end);		 // virtual address is not within the kernel
	ASSERT(v + PAGE_SIZE <= MEMORY_END); // free memory limits
	
	struct Page *page_address = (struct Page*)v;
	
	page_address->next = free_memory.next;
	free_memory.next = page_address;
}

static void free_region(uint64_t v, uint64_t e)
{
	// PAGE aligned
	for (uint64_t start = PA_UP(v); start + PAGE_SIZE <= e; start += PAGE_SIZE)
	{
		if (start + PAGE_SIZE <= MEMORY_END)
		{
			kfree(start);
		}
	}
}

void check_mm(void)
{
	struct Page *v = free_memory.next;
	uint64_t size = 0;
	uint64_t i = 0;
	
	while (v != NULL)
	{
		size += PAGE_SIZE;
		printk("%d base is 0x%x\n", i++, v);
		v = v->next;
	}
	
	printk("memory size is %u\n", size/1024/1024);
}


void init_memory(void)
{
	free_region((uint64_t)&(end), MEMORY_END);
	check_mm();
}