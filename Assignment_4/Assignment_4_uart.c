#include <avr/io.h>
#ifndef _F_CPU_
  #define F_CPU 16000000
#endif

void uart_init( uint32_t baud) {

	uint16_t BRR =  (F_CPU / (8 * baud)) -1;   // kann größer als 255 sein !

	UBRR0H = (BRR >> 8) ;     // get high byte and store it in UBRR0H
	UBRR0L = (BRR & 0xff);    // low byte

	UCSR0B |= (1<<TXEN0) + (1<<RXEN0);  // enable UART receiver and transmitter

	UCSR0A |= (1<< U2X0);     // activate double speed for UART timing
}

uint8_t uart_receive () {

	while (!(UCSR0A & (1<<RXC0))) ;
		return (UDR0);
}

void uart_transmit (uint8_t OUTPUT) {

	while (!(UCSR0A & (1<<UDRE0))) ;
			UDR0 = OUTPUT;
}

void uart_sendstr( char * str ) {

	while ( * str ) {
		uart_transmit (* str);
		str++;
	}
}

uint8_t uart_receive_nonblocking (uint8_t * received) {

  if ((UCSR0A & (1<<RXC0))) {

    *received = UDR0;
    return (1);
  }
  else {
    return(0);
    }
  }
