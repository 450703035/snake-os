#include "asm/pl_uart.h"
#include "asm/gpio.h"

.align 2
.globl __init_uart
.globl put_uart
__init_uart:
	/* GPIO */
	ldr x1, =GPFSEL1_BL
	ldr w0, [x1]
	and w0, w0, #0xffff8fff /* selector &= ~(7<<12) */
	orr w0, w0, #0x4000 /* selector |= 4<<12; */
	and w0, w0, #0xfffc7fff  /* selector &= ~(7<<15);*/
	orr w0, w0, #0x20000 /* selector |= 4<<15;*/
	str w0, [x1]

#ifdef CONFIG_BOARD_PI3B
	ldr x1, =GPPUD_BL
	str wzr,[x1]

	/* delay */
	mov x0, #150
1:
	sub x0, x0, #1
	cmp x0, #0
	bne 1b

	ldr x1, =GPPUDCLK0_BL
	ldr w2, #0xc000
	str w2, [x1]

	/* delay */
	mov x0, #150
2:
	sub x0, x0, #1
	cmp x0, #0
	bne 2b

	ldr x1, =GPPUDCLK0_BL
	str wzr, [x1]

	isb
#endif

	/* Disable UART */
	ldr x1, =U_CR_REG
	str wzr, [x1]

	/* set BRD */
	ldr x1, =U_IBRD_REG
	mov w2, #26
	str w2, [x1]

	ldr x1, =U_FBRD_REG
	mov w2, #3
	str w2, [x1]

	ldr x1, =U_LCRH_REG
	mov w2, #0x70  //(1<<4) | (3<<5)
	str w2, [x1]

	ldr x1, =U_IMSC_REG
	str wzr, [x1]

	ldr x1, =U_CR_REG
	mov w2, #0x301 //1 | (1<<8) | (1<<9)
	str w2, [x1]

	isb
	ret

put_uart:
	ldr x1, =U_FR_REG
1:
	ldr w2, [x1]
	and w2, w2, #0x20
	cmp w2, #0x0
	b.ne 1b

	ldr x1, =U_DATA_REG
	str w0, [x1]
	ret

.globl put_string_uart
put_string_uart:
	mov x4, x0
	/* save lr register */
	mov x6, x30
1:
	ldrb w0, [x4]
	bl put_uart
	add x4, x4, 1
	cmp w0, #0
	bne 1b

	/* restore lr and return*/
	mov x30, x6
	ret

