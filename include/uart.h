#ifndef	_MINI_UART_H_
#define	_MINI_UART_H_

#include "memory.h"


#define PBASE_ADDR  P2V(0xFE000000)

#define GPFSEL1         (PBASE_ADDR+0x00200004)
#define GPSET0          (PBASE_ADDR+0x0020001C)
#define GPCLR0          (PBASE_ADDR+0x00200028)
#define GPPUD           (PBASE_ADDR+0x00200094)
#define GPPUDCLK0       (PBASE_ADDR+0x00200098)
#define GPIO_PUP_PDN_CNTRL_REG0 (PBASE_ADDR+0x002000E4)

#define IO_BASE_ADDR    P2V(0xfe200000)

#define UART0_DR        IO_BASE_ADDR + 0x1000
#define UART0_FR        IO_BASE_ADDR + 0x1018
#define UART0_CR        IO_BASE_ADDR + 0x1030
#define UART0_LCRH      IO_BASE_ADDR + 0x102c
#define UART0_FBRD      IO_BASE_ADDR + 0x1028
#define UART0_IBRD      IO_BASE_ADDR + 0x1024
#define UART0_IMSC      IO_BASE_ADDR + 0x1038
#define UART0_MIS       IO_BASE_ADDR + 0x1040
#define UART0_ICR       IO_BASE_ADDR + 0x1044



unsigned char read_char(void);
void write_char(unsigned char c);
void write_string(const char* str);
void uart_init(void);
void uart_interrupt_handler(void);

#endif  /*_MINI_UART_H_ */
