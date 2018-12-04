/*
Read in the InfraRed Signal via Sensor

Sensor standy-by output = logical high
Sensor receives -> output = logical low

First falling edge -> Timer 1 starts

Rising edge -> Save time in array and reset Timer 1
Falling edge -> Save time in array and reset Timer 1
Repeat until Array full, or Signal ends
Signal end = Output of Sensor is logical high
*/

#define F_CPU 16000000
#define BAUDRATE 115200
#define MAXSIZE 1000
#define SENSORINPUT PD7

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>


void uart_init( uint32_t baud) {

	uint16_t BRR =  (F_CPU / (8 * baud)) -1;   // kann größer als 255 sein !

	UBRR0H = (BRR >> 8) ;     // get high byte and store it in UBRR0H
	UBRR0L = (BRR & 0xff);    // low byte

	UCSR0B |= (1<<TXEN0) + (1<<RXEN0);  // enable UART receiver and transmitter

	UCSR0A |= (1<< U2X0);     // activate double speed for UART timing
}

void uart_transmit (uint8_t output) {

	while (!(UCSR0A & (1<<UDRE0))) ;
	UDR0 = output;
}

void uart_sendstr( char * str ) {

	while ( * str ) {
		uart_transmit (* str);
		str++;
	}
}

ISR (INT0_vect) { //is called for rising edge


}

ISR (INT1_vect) { //is called for falling edge


}

void init_timer0() {
	TCCR0B = 1; // select timer0 prescaler of 1 (62.5 ns resolution)
	TIMSK0 = 1; // TIMSK0 |= (1<<TOIE0);
	TCNT0 = 0; // to init with reload value
}

void init_register() {
	DDRD  &= ~(1 << SENSORINPUT); //set PD7 as input
	PORTD |= (1 << SENSORINPUT);  // set PD7 pullup
}

void init_externalInterrupt() {
	//EICRA = external interrupt control register
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY edge
	EIMSK |= (1 << INT0);     // Turns on INT0

}

int main() {

	uart_init(BAUDRATE);
	uart_sendstr("Test1.\n\r");
	init_externalInterrupt();

	uart_sendstr("Test2.\n\r");
	init_register();
	init_timer0();


	uint16_t sensorInputArray[MAXSIZE];


	while(1) {


	}
}
