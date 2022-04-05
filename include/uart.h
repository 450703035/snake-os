#ifndef	_MINI_UART_H
#define	_MINI_UART_H

void uart_init ( void );
char read_char ( void );
void write_char ( char c );
void write_string(char* str);

#endif  /*_MINI_UART_H */
