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
#define SENSORINPUT PB0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

volatile uint16_t globalSensorInputArray[MAXSIZE];
volatile static uint8_t arrayPosition = 0; //variable value remains after exiting function

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

void init_timer1() {
	//TCCR1B &= ~(1 << COM1B1) & ~(1 << COM1B0);
	TCCR1B |= (1 << CS10); // select timer0 prescaler of 1 (62.5 ns resolution)
	TIMSK1 |= (1 << TOIE1); // TIMSK0 |= (1<<TOIE0);
	//TCNT1 = 0; // to init with reload value
}
void reset_timer0() {
	TCNT1 = 0; // to init with reload value
}
void init_register() {
	DDRB  &= ~(1 << SENSORINPUT); //set PB0 as input
	PORTB |= (1 << SENSORINPUT);  // set PB0 pullup
}
void init_externalInterrupt() {
	//EICRA = external interrupt control register
	EIMSK |= (1 << INT0);     // Turns on INT0
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY edge
}

void intToString(uint16_t val, char * target) {
	int16_t index;
	for(index = MAXSIZE; index >= 0; index--) {
		target [index] = val + '0';
	}
	target[MAXSIZE] = 0;
}

ISR (INT1_vect) { //is called for ANY edge
	cli();
	if(PINB & (1<<PB0)) {
		globalSensorInputArray[arrayPosition] = TCNT1;
		reset_timer0();
	}
	else {
		globalSensorInputArray[arrayPosition] = TCNT1;
		reset_timer0();
	}
	arrayPosition++;
	sei();
}

ISR(TIMER1_OVF_vect){

}

int main() {
	uart_init(BAUDRATE);
	init_externalInterrupt();
	init_register();
	init_timer1();

	sei();

	char outPutArrayTest[MAXSIZE];

	while(1) {
		uart_sendstr("WHILE.\n\r");
		_delay_ms(1000);
		


	}
}
