.global el1_vectors

.section .text
.align 11

//
// Current EL with SP0
//
el1_vectors:
current_el_sp0_sync:
	b error

.balign 0x80
current_el_sp0_irq:
	b error

.balign 0x80
current_el_sp0_fiq:
	b error

.balign 0x80
current_el_sp0_serror:
	b error
	
//
// Current EL with SPx
//	
.balign 0x80
current_el_spn_sync:
	b sync_handler

.balign 0x80
current_el_spn_irq:
	b irq_handler

.balign 0x80
current_el_spn_fiq:
	b error

.balign 0x80
current_el_spn_serror:
	b error

//
// Lower EL using AArch64
//
.balign 0x80
lower_el_aarch64_sync:
	b sync_handler

.balign 0x80
lower_el_aarch64_irq:
	b error

.balign 0x80
lower_el_aarch64_fiq:
	b error

.balign 0x80
lower_el_aarch64_serror:
	b error
	
//
// Lower EL using AArch32
//
.balign 0x80
lower_el_aarch32_sync:
	b error

.balign 0x80
lower_el_aarch32_irq:
	b error

.balign 0x80
lower_el_aarch32_fiq:
	b error

.balign 0x80
lower_el_aarch32_serror:
	b error
	

sync_handler:
	sub sp, sp, #(32 * 8)
	
	stp x29, x30, [sp, #-16]!
	stp x18, x19, [sp, #-16]!
	stp x16, x17, [sp, #-16]!
	stp x14, x15, [sp, #-16]!
	stp x12, x13, [sp, #-16]!
	stp x10, x11, [sp, #-16]!
	stp x8, x9, [sp, #-16]!
	stp x6, x7, [sp, #-16]!
	stp x4, x5, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x0, x1, [sp, #-16]!
	
	mov x0, #1
	mrs x1, esr_el1
	mrs x2, elr_el1
	bl handler
	
	ldp x0, x1, [sp], #16
	ldp x2, x3, [sp], #16
	ldp x4, x5, [sp], #16
	ldp x6, x7, [sp], #16
	ldp x8, x9, [sp], #16
	ldp x10, x11, [sp], #16
	ldp x12, x13, [sp], #16
	ldp x14, x15, [sp], #16
	ldp x16, x17, [sp], #16
	ldp x18, x19, [sp], #16
	ldp x29, x30, [sp], #16
	
	add sp, sp, #(32 * 8)
	eret

irq_handler:
	sub sp, sp, #(32 * 8)
	
	stp x29, x30, [sp, #-16]!
	stp x18, x19, [sp, #-16]!
	stp x16, x17, [sp, #-16]!
	stp x14, x15, [sp, #-16]!
	stp x12, x13, [sp, #-16]!
	stp x10, x11, [sp, #-16]!
	stp x8, x9, [sp, #-16]!
	stp x6, x7, [sp, #-16]!
	stp x4, x5, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x0, x1, [sp, #-16]!
	
	mov x0, #2
	mrs x1, esr_el1
	mrs x2, elr_el1
	bl handler
	
	ldp x0, x1, [sp], #16
	ldp x2, x3, [sp], #16
	ldp x4, x5, [sp], #16
	ldp x6, x7, [sp], #16
	ldp x8, x9, [sp], #16
	ldp x10, x11, [sp], #16
	ldp x12, x13, [sp], #16
	ldp x14, x15, [sp], #16
	ldp x16, x17, [sp], #16
	ldp x18, x19, [sp], #16
	ldp x29, x30, [sp], #16
	
	add sp, sp, #(32 * 8)
	eret

error:
	sub sp, sp, #(32 * 8)
	
	stp x29, x30, [sp, #-16]!
	stp x18, x19, [sp, #-16]!
	stp x16, x17, [sp, #-16]!
	stp x14, x15, [sp, #-16]!
	stp x12, x13, [sp, #-16]!
	stp x10, x11, [sp, #-16]!
	stp x8, x9, [sp, #-16]!
	stp x6, x7, [sp, #-16]!
	stp x4, x5, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x0, x1, [sp, #-16]!

	mov x0, #1
	bl handler
	
	ldp x0, x1, [sp], #16
	ldp x2, x3, [sp], #16
	ldp x4, x5, [sp], #16
	ldp x6, x7, [sp], #16
	ldp x8, x9, [sp], #16
	ldp x10, x11, [sp], #16
	ldp x12, x13, [sp], #16
	ldp x14, x15, [sp], #16
	ldp x16, x17, [sp], #16
	ldp x18, x19, [sp], #16
	ldp x29, x30, [sp], #16
	
	add sp, sp, #(32 * 8)
	eret
