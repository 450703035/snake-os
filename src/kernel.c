#include "uart.h"

void kernel_main(void)
{
	uart_init();
	
	uart_send_string("************\r\n");
	uart_send_string("           *****>\r\n");
	uart_send_string("Welcome Snake OS!\r\n");
	uart_send_string("Welcome Snake OS!\r\n");
	uart_send_string("Welcome Snake OS!\r\n");
	
	while(1)
	{		
		;
	}
	
}