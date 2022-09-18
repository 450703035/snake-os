#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "asm/base.h"

#define GPFSEL1_BL         (PBASE+0x00200004)
#define GPSET0_BL        (PBASE+0x0020001C)
#define GPCLR0_BL          (PBASE+0x00200028)
#define GPPUD_BL           (PBASE+0x00200094)
#define GPPUDCLK0_BL       (PBASE+0x00200098)
#define GPIO_PUP_PDN_CNTRL_REG0_BL (PBASE+0x002000E4)

#endif  /*_P_GPIO_H */
