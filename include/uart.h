#ifndef	_MINI_UART_H_
#define	_MINI_UART_H_

void uart_init ( void );
char read_char ( void );
void write_char ( char c );
void write_string(char* str);
void uart_interrupt_handler(void);

#endif  /*_MINI_UART_H_ */
