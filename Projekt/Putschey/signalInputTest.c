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
#define SENSORINPUT PB3 //externe Interrupt for timer 1 triggers on PB1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

volatile uint16_t globalSensorInputArray[MAXSIZE];
volatile static uint8_t arrayPosition = 0; //variable value remains after exiting function
volatile uint8_t arrayFull = 0;
volatile uint8_t overflowFlag = 0;

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
	TCCR1B |= (1 << CS12); // select timer1 prescaler of 1 (62.5 ns resolution)
	TIMSK1 |= (1 << TOIE1); // TIMSK0 |= (1<<TOIE0);
	//TCNT1 = 0; // to init with reload value
}
void reset_timer1() {
	TCNT1 = 0; // to init with reload value
}
void init_register() {
	DDRB  &= ~(1 << SENSORINPUT); //set PB0 as input
	PORTB |= (1 << SENSORINPUT);  // set PB0 pullup
}
void init_externalInterrupt() {
	//EICRA = external interrupt control register
	EIMSK |= (1 << INT1);     // Turns on INT0
	EICRA |= (1 << ISC10);    // set INT0 to trigger on ANY edge
}


void intToString(uint16_t val, char * target) { /* 2^16-1 =  5 digits + 1 for string terminator */
	int16_t index;
	for(index = 4; index >= 0; index--) {
		target [index] = val % 10 + '0';
		val /= 10;
	}
	target[5] = '\0';
}

ISR (INT1_vect) { //is called for ANY edge
	static uint8_t firstFlank = 1;

	if (firstFlank) {
		reset_timer1();
		firstFlank = 0;
		return;
	}
	else {
		if(arrayPosition >= MAXSIZE-1){
			arrayFull = 1;
			return;
		}
		else {
			globalSensorInputArray[arrayPosition] = TCNT1;
			reset_timer1();
			arrayPosition++;
		}
	}
}

ISR(TIMER1_OVF_vect){
	overflowFlag = 1;
}

int main() {
	uart_init(BAUDRATE);
	init_externalInterrupt();
	init_register();
	init_timer1();
	sei();

	while(1) {

	}
}
