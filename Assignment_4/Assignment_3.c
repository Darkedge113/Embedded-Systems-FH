#define F_CPU 16000000
#define BAUDRATE 115200
#define MAXSIZE 5
#define CHANNEL_ADC 0
#define POTENTIOMETER   PC0 // potentiometer
#define LED_INTERN PB5 /* interne led*/

#include <util/delay.h>
#include <avr/io.h>
#include "Assignment_3_uart.h"
#include "Assignment_3_adc.h"
#include <avr/interrupt.h>

/*void register_setup() {

	DDRB  |= ((1 << LED_INTERN) | (1 << LED_EXTERN));
	DDRC  &= ~(1 << POTENTIOMETER); // set pot to input
	PORTC |= (1 << POTENTIOMETER);  // set potentiometer pullup
}*/

ISR (TIMER0_OVF_vect) { //is called with 1 kHz frequency

	static uint16_t count = 0;
	TCNT0 = 6; // reload value 6: next interrupt after 250 ticks (1ms)
	PORTB ^= LED_INTERN; //toggle interne led

	count++;
	if (count == 500) {
		count = 0;
		PORTB ^= (1<<LED_INTERN);
	}
}


void init_timer0() {
	TCCR0B = 3; //select timer0 prescaler of 64 (250 kHz resolution)
	TIMSK0 = 1; //	TIMSK0 |= (1<<TOIE0);
}

int main() {

	char stringmem[5];

	DDRB |= (1<<LED_INTERN);

	uart_init(BAUDRATE);
	uart_sendstr("timer ready");
	init_timer0();
	sei(); //enable all interrupts


	while (1) {


	}
}
