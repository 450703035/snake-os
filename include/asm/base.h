#ifndef	_P_BASE_H
#define	_P_BASE_H

#define KERNEL_BASE 0xffff000000000000

#ifdef CONFIG_BOARD_PI3B
#define PBASE 0x3F000000
#else
#define PBASE 0xFE000000
#endif

#endif  /*_P_BASE_H */
