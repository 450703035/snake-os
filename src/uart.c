#include "asm/pl_uart.h"
#include "asm/gpio.h"
#include "io.h"
#include "stdint.h"
#include "print.h"

void write_char(char c)
{
	/* wait for transmit FIFO to have an available slot*/
	while (readl(UART0_FR) & (1 << 3))
		;

	writel(c, UART0_DR);
}

char read_char(void)
{
	/* wait for receive FIFO to have data to read */
	/*while (readl(UART0_FR) & (1<<4));*/

	return(readl(UART0_DR) & 0xFF);
}

void write_string(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		write_char((char) str[i]);
}

void uart_interrupt_handler(void)
{
	uint32_t status = readl(UART0_IMSC);
	char ch;
	
	if (status & (1 << 4))
	{
		ch = read_char();
		if (ch == '\r')
		{
			write_string("\r\n");
		}
		else
		{
			write_char(ch);
		}
		
		writel(UART0_ICR, (1 << 4));
	}
	
}

void uart_init(void)
{
	unsigned int selector;

	/* clean gpio14 */
	selector = readl(GPFSEL1);
	selector &= ~(7<<12);
	/* set alt0 for gpio14 */
	selector |= 4<<12;
	/* clean gpio15 */
	selector &= ~(7<<15);
	/* set alt0 for gpio15 */
	selector |= 4<<15;
	writel(selector, GPFSEL1);

#ifdef CONFIG_BOARD_PI3B
	writel(0, GPPUD);
	delay(150);
	writel((1<<14) | (1<<15), GPPUDCLK0);
	delay(150);
	writel(0, GPPUDCLK0);
#else
	/*set gpio14/15 pull down state*/
	selector = readl(GPIO_PUP_PDN_CNTRL_REG0);
	selector |= (0x2 << 30) | (0x2 << 28);
	writel(selector, GPIO_PUP_PDN_CNTRL_REG0);	
#endif

	/* disable UART until configuration is done */
	writel(0, UART0_CR);

	/*
	 * baud divisor = UARTCLK / (16 * baud_rate)
	= 48 * 10^6 / (16 * 115200) = 26.0416666667
	integer part = 26
	fractional part = (int) ((0.0416666667 * 64) + 0.5) = 3
	generated baud rate divisor = 26 + (3 / 64) = 26.046875
	generated baud rate = (48 * 10^6) / (16 * 26.046875) = 115177
	error = |(115177 - 115200) / 115200 * 100| = 0.02%
	*/

	/* baud rate divisor, integer part */
	writel(26, UART0_IBRD);
	/* baud rate divisor, fractional part */
	writel(3, UART0_FBRD);

	/* disable FIFOs and 8 bits frames */
	writel((3<<5), UART0_LCRH);

	/* mask interupts */
	writel(1<<4, UART0_IMSC);
	/* enable UART, receive and transmit */
	writel(1 | (1<<8) | (1<<9), UART0_CR);
}
