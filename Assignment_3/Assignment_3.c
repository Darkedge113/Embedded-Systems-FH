#define F_CPU 16000000
#define BAUDRATE 115200
#define MAXSIZE 5
#define CHANNEL_ADC 0
#define POTENTIOMETER   PC0 // potentiometer
#define LED_INTERN PB5 // interne led
#define LED_EXTERN PB0 // externe led

#include <util/delay.h>
#include <avr/io.h>
#include "Assignment_3_uart.h"
#include "Assignment_3_adc.h"

void register_setup() {

	DDRB  |= ((1 << LED_INTERN) | (1 << LED_EXTERN));
	DDRC  &= ~(1 << POTENTIOMETER); // set pot to input
	PORTC |= (1 << POTENTIOMETER);  // set potentiometer pullup
}

int main() {

	char stringMemory[MAXSIZE]; //da der string 1023 aus 4 Zeichen besteht; 5tes Zeichen ist \0 der das Ende vom String anzeigt

  uart_init (BAUDRATE);
  adc_init();
	register_setup();

  uint16_t valuePotentiometer = 0; // der dritte/vierte? channel wird eingelesen
	uint8_t inputYesNo = 0; // ob input braucbar, veraltet
	uint8_t * inputChar; //actual input

	uint8_t running=0;

	uint8_t delayTimer = 0;

	char array[] = "Starte Programm Assignment_3\n\r";
	uart_sendstr(array);

	while(1) {

		inputYesNo = uart_receive_nonblocking(inputChar);

		if(inputYesNo) {

			switch(*inputChar) {
				case 'r':
				case 'R':
				running = 1;
				uart_sendstr("\n\r");
					break;

				case 's':
				case 'S':
				running = 0;
				uart_sendstr("\n\r");
					break;
		}
	}

		if(running) {

			valuePotentiometer = adc_read(CHANNEL_ADC);

			PINB |= (1<<LED_EXTERN); //toggles LED
			PINB |= (1<<LED_INTERN);

			intToString(valuePotentiometer, stringMemory);
			uart_sendstr (stringMemory);
			uart_sendstr("\n\r");

			delayTimer = valuePotentiometer / 102; //um auf einen Wert zwischen 1 und 10 zu kommen

			uint8_t i;
			for (i = 0; i <= delayTimer; i++) {
			_delay_ms(50); //delayed die externe und interne LED

			//Ohne Timer ist ein separates Blinken nicht realisierbar
			}
		}
	}
}
