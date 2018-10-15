
#ifndef Assignment_3_uart_h_
#define Assignment_3_uart_h_

void uart_init( uint32_t baud);
void uart_transmit (uint8_t OUTPUT);
void uart_sendstr( char * str );
uint8_t uart_receive_nonblocking (uint8_t * received);
uint8_t uart_receive ();

#endif
