/* ERES Robert - Assignment 4 - LED PWM*/

#define F_CPU 16000000
#define BAUDRATE 115200
#define MAXSIZE 5
#define CHANNEL_ADC 0
#define POTENTIOMETER  (1<<PC0) /* potentiometer */
#define LED_INTERN (1<<PB5) //*interne led */
#define LED_EXTERN (1<<PD3) /* externe led */

#include <avr/io.h>
#include "Assignment_4_uart.h"
#include "Assignment_4_adc.h"
#include <avr/interrupt.h>

volatile uint8_t brightness = 0; //global variable, volatile = not touched by compiler

ISR (TIMER0_OVF_vect) { //is called with 1 kHz frequency

	static uint8_t timerCounter = 0; //variable value remains after exiting function

	if(timerCounter == 10 ) { // divides cycle into 10 regions
		timerCounter = 0;
		}

	TCNT0 = 256-25; // reload value 231: next interrupt after 25 ticks (0,1ms period = 10kHz)
	PORTD ^= LED_EXTERN; //toggle interne led,not sure why??

	if (brightness > timerCounter){ // on time of PWM cycle, if >= used its not 10% but 20% when input = 1
		PORTD |= LED_EXTERN;
	}
	else {
		PORTD &= ~(LED_EXTERN); // off time of PWM cycle
	}

	timerCounter++; // important to increment before reset, else reset is 1 not 0
}

void init_timer0() {
	TCCR0B = 3; // select timer0 prescaler of 64 (250 kHz resolution)
	TIMSK0 = 1; // TIMSK0 |= (1<<TOIE0);
	TCNT0 = 256-25; // to init with reload value
}

void register_setup() {
	DDRD |= (1<<LED_EXTERN);
}

int main() {

	register_setup(); // sets in-out registers
	uart_init(BAUDRATE); // sets up UART with baudrate
	init_timer0(); // sets up timer functionality
	sei(); //enable all interrupts#
	uart_sendstr("SLIP - Sexy LED Input PWM  \r\n");
	uart_sendstr("SLIP initiated \r\n");

	char inputUart = 0;
	char inputReceived = 0;

	while (1) {
	 	inputReceived =	uart_receive_nonblocking(&inputUart); // & gives the address of variable
		inputUart -= '0'; // to convert from ASCII to integer

		if(inputReceived && inputUart < 10 && inputUart >= 0) { // if something is received AND between 0 and 10 including 0
			brightness = inputUart;
			uart_sendstr(" was entered.\r\n");
		}
	}
}
