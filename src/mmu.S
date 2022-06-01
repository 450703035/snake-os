.equ MAIR_ATTR, (0x44 << 8)
.equ TCR_T0SZ,	(16)
.equ TCR_T1SZ, 	(16 << 16)
.equ TCR_TG0,	(0 << 14)
.equ TCR_TG1, 	(2 << 30)
.equ TCR_VALUE, (TCR_T0SZ | TCR_T1SZ | TCR_TG0 | TCR_TG1)
.equ PAGE_SIZE, (2*1024*1024)


.global enable_mmu
.global setup_vm

enable_mmu:
	adr x0, pgd_ttbr1
	msr ttbr1_el1, x0
	
	adr x0, pgd_ttbr0
	msr ttbr0_el1, x0
	
	ldr x0, =MAIR_ATTR
	msr mair_el1, x0
	
	ldr x0, =TCR_VALUE
	msr tcr_el1, x0
	
	mrs x0, sctlr_el1
	orr x0, x0, #1
	msr sctlr_el1, x0
	
	ret
	

setup_vm:

/*
					+---------------+
                    |               |
                    |               |\
                    |               |   \
                    |               |      \
					|				|         \
					|				|\           ->+---------------+ 0x100000000 4g
					|           	|   \          | Peripheral	   |
					|   kernel  	|\     \       |    Area  	   |
					|   Space   	|  \      \    |               |
					|           	|   \        ->|---------------| 0xFE000000  3G
					|           	|     \     
					|           	|	   \	 ->+---------------+ 1G
  0xFFFF000000000000|---------------|        \     |			   |
					| Non-canonical |\         \   |           	   |
					|    Addresses  | \         \  |               |
					|       		|  \          ->|---------------| 0x34000000(MEMORY_END) 832M
					|---------------|   \          | File system   |
					|       		|    \         |---------------| 0x30000000 768M
					|       		|     \        |           	   |
					|       		|      \       |			   |
					|   User Space  |       \      | Free Memory   |
					|       		|        \     |    		   |
					|     	  		|		  \    |       		   |
					|---------------|----------\-->|---------------| 2M
				 	|     2M page   |           \  |  OS kernel    |
				  0 +---------------+------------\>+---------------+ 0                                   
*/ 
setup_kvm:
	//gpd 512g  pud 1g pmd 2m             
	adr x0, pgd_ttbr1
	adr x1, pud_ttbr1
	orr x1, x1, #3
	str x1, [x0]

	adr x0, pud_ttbr1
	adr x1, pmd_ttbr1
	orr x1, x1, #3
	str x1, [x0]
	
	mov x2, #0x34000000
	adr x1, pmd_ttbr1
	mov x0, #(1 << 10 | 1 << 2 | 1 << 0) 
	
loop1:
	str x0, [x1], #8
	add x0, x0, #PAGE_SIZE
	cmp x0, x2
	blo loop1
	
	//Peripheral area 0xc0000000-0x100000000 4G 
	adr x0, pud_ttbr1
	add x0, x0, #(3*8)
	adr x1, pmd_3_ttbr1
	orr x1, x1, #3
	str x1, [x0]
	
	mov x2, #0x100000000
	mov x0, #0xf0000000
	
	adr x3, pmd_3_ttbr1
	mov x4, #(0xf0000000 - 0xc0000000)
	lsr x1, x4, #(21 - 3)
	add x1, x1, x3
	
	orr x0, x0, #1
	orr x0, x0, #(1 << 10)
	
loop2:
	str x0, [x1], #8
	add x0, x0, #PAGE_SIZE
	cmp x0, x2
	blo loop2
	
	

/*
	+---------------+ 
	|				|
	|           	|
	|   kernel  	|
	|   Space   	|
	|           	|
	|           	|
	|           	|			          +---------------+ 1G
	|---------------|                     |				  |
	| Non-canonical |                     |           	  |
	|    Addresses  |                     |               |
	|       		|                     |---------------|
	|---------------|                     | File system   |
	|       		|                     |---------------| 0x30000000
	|       		|                     |           	  |
	|       		|                     |				  |
	|   User Space  |                     | Free Memory   |
	|       		|                     |    			  |
	|     	  		|		              |       		  |
	|---------------|-------------------->|---------------| 2M
	|     2M page   | identical mapping   |  OS kernel    |
	+---------------+-------------------->+---------------+ 0                                   
*/                                                                                                                       
setup_uvm:                                
	// identical mapping 2m start 0       
	//gpd 512g  pud 1g pmd 2m             
	adr x0, pgd_ttbr0
	adr x1, pud_ttbr0
	orr x1, x1, #3
	str x1, [x0]
	
	adr x0, pud_ttbr0
	adr x1, pmd_ttbr0
	orr x1, x1, #3
	str x1, [x0]
	
	adr x1, pmd_ttbr0
	// bit10 access bit2:4 memory attribute
	mov x0, #(1 << 10 | 1 << 2 | 1 << 0)
	str x0, [x1]
	
	ret


.balign 4096
pgd_ttbr1:
	.space 4096
pud_ttbr1:
	.space 4096
pmd_ttbr1:
	.space 4096
pmd_3_ttbr1:
	.space 4096


pgd_ttbr0:
	.space 4096
pud_ttbr0:
	.space 4096
pmd_ttbr0:
	.space 4096




