#include "stdint.h"
#include "asm/gpio.h"
#include "lib.h"
#include "print.h"
#include "uart.h"

void write_char(unsigned char c)
{
	/* wait for transmit FIFO to have an available slot*/
	while (in_word(UART0_FR) & (1 << 3)) { }
	out_word(UART0_DR, c);
}

unsigned char read_char(void)
{
	/* wait for receive FIFO to have data to read */
	/*while (in_word(UART0_FR) & (1<<4));*/

	return(in_word(UART0_DR) & 0xFF);
}

void write_string(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		write_char((char) str[i]);
}

void uart_interrupt_handler(void)
{
	uint32_t status = in_word(UART0_IMSC);
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
		
		out_word(UART0_ICR, (1 << 4));
	}
	
}

void uart_init(void)
{
	unsigned int selector;

	/* clean gpio14 */
	selector = in_word(GPFSEL1);
	selector &= ~(7<<12);
	/* set alt0 for gpio14 */
	selector |= 4<<12;
	/* clean gpio15 */
	selector &= ~(7<<15);
	/* set alt0 for gpio15 */
	selector |= 4<<15;
	out_word(GPFSEL1, selector);

#ifdef CONFIG_BOARD_PI3B
	out_word(GPPUD, 0);
	delay(150);
	out_word(GPPUDCLK0, (1<<14) | (1<<15));
	delay(150);
	out_word(GPPUDCLK0, 0);
#else
	/*set gpio14/15 pull down state*/
	selector = in_word(GPIO_PUP_PDN_CNTRL_REG0);
	selector |= (0x2 << 30) | (0x2 << 28);
	out_word(GPIO_PUP_PDN_CNTRL_REG0, selector);	
#endif

	/* disable UART until configuration is done */
	out_word(UART0_CR, 0);

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
	out_word(UART0_IBRD, 26);
	/* baud rate divisor, fractional part */
	out_word(UART0_FBRD, 3);

	/* disable FIFOs and 8 bits frames */
	out_word(UART0_LCRH, (3<<5));

	/* mask interupts */
	out_word(UART0_IMSC, 1<<4);
	/* enable UART, receive and transmit */
	out_word(UART0_CR, (1<<0) | (1<<8) | (1<<9));
}
