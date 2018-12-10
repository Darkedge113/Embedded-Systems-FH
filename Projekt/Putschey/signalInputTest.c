/*
10.12.2018
Author: Eres Robert
Technikum-ID: 1710768026
*/

#define F_CPU 16000000
#define BAUDRATE 115200
#define MAXSIZE 1000 //Maximal size for the incoming IR signal
#define SENSORINPUT PD3 //External Interrupt for Timer 1 only trigger on pin PD3
#define TIMER0_OFFSET 256-52 //Reload value of 204 with 0,5µs steps = 26µs = T -> f = 38kHz
#define IRLED PB0 // Pin for IR led

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t globalSensorInputArray[MAXSIZE]; //Global array for the incoming signal
volatile uint8_t arrayFull = 0; //Flag shows that the array is full
volatile uint8_t overflowFlag = 0; //Timer Overflow Flag
volatile uint8_t signalmode = 1; //To indicate the current height of the signal (low/high)

void uart_init( uint32_t baud) {

	uint16_t BRR =  (F_CPU / (8 * baud)) -1;   // 16 bit necessary since it can exceed 255.

	UBRR0H = (BRR >> 8) ;     // Get high byte and store it in UBRR0H
	UBRR0L = (BRR & 0xff);    // Same of the low byte

	UCSR0B |= (1<<TXEN0) + (1<<RXEN0);  // Enable UART receiver and transmitter

	UCSR0A |= (1<< U2X0);     // Activate double speed for UART timing
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

void init_timer0() {
	TCCR0B |= (1 << CS01); // Enable Timer 0 - 8 prescale
	TIMSK0 |= (1 << TOIE0); //Enbable interrupts
	TCNT0 = TIMER0_OFFSET; //Reload value of 52 with 0,5µs steps = 26µs = T -> f = 38kHz
}
void clear_timer0(){
	TCCR0B &= ~(1 << CS01); // Disable Timer0
	TIMSK0 &= ~(1 << TOIE0); // Disable Interrupts
	TCNT0 = TIMER0_OFFSET;
}
void init_timer1() {
	TCCR1B |= (1 << CS12); // Select timer1 prescaler of 1 (62.5 ns resolution)
	TIMSK1 |= (1 << TOIE1);
}
void reset_timer1() {
	TCNT1 = 0; // To init with reload value of 0
}
void init_register() {
	DDRB |= (1 << IRLED); // Set PB0 as output
	DDRD  &= ~(1 << SENSORINPUT); // Set PD3 as input
	PORTD |= (1 << SENSORINPUT);  // Set PD3 pullup
}
void init_externalInterrupt() {
	//EICRA = external interrupt control register
	EIMSK |= (1 << INT1);     // Turns on INT0
	EICRA |= (1 << ISC10);    // set INT0 to trigger on ANY edge
}
void intToString(uint16_t val, char * target) { // 2^16-1 =  5 digits + 1 for string terminator
	int16_t index;
	for(index = 4; index >= 0; index--) {
		target [index] = val % 10 + '0';
		val /= 10;
	}
	target[5] = '\0';
}

ISR (INT1_vect) { // Is called for ANY edge
	static uint8_t firstFlank = 1;
	static uint8_t arrayPosition = 0; // Variable value remains after exiting function

	if (firstFlank) { // To ignore the time before the first flank
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
			globalSensorInputArray[arrayPosition] = TCNT1; // Saves current timer value in global array
			reset_timer1();
			arrayPosition++;
		}
	}
}
ISR(TIMER0_OVF_vect) {

	//PORTB |= (1 << IRLED); //LED leuchtet NICHT!

	PORTB ^= (1 << IRLED); // Toggles LED
	TCNT0 = TIMER0_OFFSET; // ISR is called with 38kHz -> Toggles LED with 38kHz
}

ISR(TIMER1_OVF_vect){ // ISR called when Timer1 overflows
	//PORTB |= (1 << IRLED);  //LED leuchtet NICHT!
	overflowFlag = 1;
	if (signalmode) {
		init_timer0(); // Starts timer 0 -> Toggles LED with 38kHz, is 1 in RC5
	}
	else {
		clear_timer0(); // To stop the toggling -> Is 0 in RC5
	}
}

void outputCommand() { // Short function to output the contente of the global array
	uart_sendstr("Ausgabe des Arrays\n\r");
	uint16_t index;
	char convertedString[6];
	for (index = 0; index < MAXSIZE; index++){
		intToString(globalSensorInputArray[index], convertedString);
		uart_sendstr(convertedString);
		uart_sendstr("\r\n");

		if(globalSensorInputArray[index] == 0) {
			_delay_ms(300);
			uart_sendstr("Ende des Arrays\n\r");
			return;
		}
	}
}
void sendCommand(uint16_t * sendArray) { //Sends the command via IR LED
	uint16_t index;
	while (overflowFlag) {
		TCNT1 = 65535 - globalSensorInputArray[index];
		signalmode = !signalmode;
		index++;
		while (!overflowFlag) {}
		overflowFlag = 0;
	}
}

int main() {
	uart_init(BAUDRATE);
	init_externalInterrupt();
	init_register();
	init_timer1();
	sei();

	_delay_ms(500);

	sendCommand(globalSensorInputArray);
	outputCommand();

}
