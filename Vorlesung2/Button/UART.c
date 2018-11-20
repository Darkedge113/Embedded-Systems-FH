// Robert Eres

#define F_CPU 16000000
#define BAUDRATE 115200

#include <avr/io.h>

uint8_t uart_receive() {
	
	while (!UCSR0A & (1<<RXC0)) {
	
	return(UDR0);
		
	}
}

void uart_transmit(uint8_t c) {
	
	while (!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = c;
	
}

void uart_sendstr(char * str) {
	
	while (* str) {
		
		uart_transmit(* str);
		str++;
	}
}

void uart_init(uint32_t baud) {
	
	uint16_t BRR = (F_CPU / (baud*8)) - 1; // kann größer als 255 sein ! -> auf geteilt in 0H und 0L
	
	UBRR0H = BRR >> 8; // get high byte and stsore it in UBRR0H; es wird durch 8 dividiert, das entspricht einer Verschiebung von 8
	UBRR0L = (BRR & 0xFF); //get low byte, untere 8 Bit, maskiere alles darüber mit 0!
	
	UCSR0B |= (1<<TXEN0) + (1<<RXEN0); // enable UART receiver and transmitter
	
	UCSR0A |= (1<<U2X0); // activate double speed for UART timing 
	
}


int main() {
	
	uart_init(BAUDRATE);
		
	uart_sendstr("Hallo ich versende irgendwas!");
					
}
