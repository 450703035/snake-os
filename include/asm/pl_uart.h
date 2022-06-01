#ifndef	_P_UART_H
#define	_P_UART_H

#include "base.h"

#define U_BASE       (PBASE+0x00201000)

#define U_DATA_REG   (U_BASE)
#define U_FR_REG     (U_BASE+0x18)
#define U_IBRD_REG   (U_BASE+0x24)
#define U_FBRD_REG   (U_BASE+0x28)
#define U_LCRH_REG   (U_BASE+0x2C)
#define U_CR_REG     (U_BASE+0x30)
#define U_IMSC_REG   (U_BASE+0x38)


/*
#define IO_BASE_ADDR    0xfe200000

#define UART0_DR        IO_BASE_ADDR + 0x1000
#define UART0_FR        IO_BASE_ADDR + 0x1018
#define UART0_CR        IO_BASE_ADDR + 0x1030
#define UART0_LCRH      IO_BASE_ADDR + 0x102c
#define UART0_FBRD      IO_BASE_ADDR + 0x1028
#define UART0_IBRD      IO_BASE_ADDR + 0x1024
#define UART0_IMSC      IO_BASE_ADDR + 0x1038
#define UART0_MIS       IO_BASE_ADDR + 0x1040
#define UART0_ICR       IO_BASE_ADDR + 0x1044
*/

#endif  /*_P_UART_H */
