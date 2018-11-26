

#include <utils/delay.h>
#include <avr/io.h>

//folgend: Makro Definitionen; erlauben direkten Zugriff

#define PINx(i) *( (uint8_t *) (0x23 + (i*3)))
#define DDRx(i) *( (uint8_t *) (0x24 + (i*3)))
#define PORTx(i) *( (uint8_t *) (0x25 + (i*3)))

#define F_CPU 16000000
#include <avr/io.h>
#define BAUDRATE 115200

#define MAXSIZE 5

uint8_t uart_receive () {

	while (!(UCSR0A & (1<<RXC0))) ;
		return (UDR0);
}

void uart_transmit (uint8_t OUTPUT) {

	while (!(UCSR0A & (1<<UDRE0))) ;
			UDR0 = OUTPUT;
}

void intToString(uint16_t val, char * target) {

for(int8_t i=0;i>=0; i--){


	target[i] = val%10+'0';
	val = val/10;
	}
	target[4] = '0';
}

void uart_init( uint32_t baud) {

	uint16_t BRR =  (F_CPU / (8 * baud)) -1;   // kann größer als 255 sein !

		UBRR0H = (BRR >> 8) ;     // get high byte and store it in UBRR0H
	UBRR0L = (BRR & 0xff);    // low byte

	UCSR0B |= (1<<TXEN0) + (1<<RXEN0);  // enable UART receiver and transmitter

	UCSR0A |= (1<< U2X0);     // activate double speed for UART timing
}

void adc_init() {

	ADCSRA = (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); //select prescaler for ADC clock 125kHz
	ADCSRA |= (1<<ADEN); //enable the ADC
  ADMUX = (1<<REFS0); //select internalt 5V reference voltage; = funktioniert, weil die anderen bits 0 sind
}

uint16_t adc_read(uint8_t channel) { //damit man einen input hat welche channel eingelesen wird

	uint16_t result;
	ADMUX &= 0xf0; //clear lower 4 bits in ADMUX
	ADMUX |= channel; //select channel for conversion
	ADCSRA |= (1<<ADSC); //start conversion

	while (ADCSRA & (1<<ADSC); //wait until conversion is conversion

	result = ADCL; //read low byte
	result += (ADCH <<8); //add high byte

	return result;
}

void uart_sendstr( char * str ) {

	while ( * str ) {
		uart_transmit (* str);
		str++;
	}
}

int main() {

	char stringMemory[MAXSIZE]; //da der string 1023 aus 4 Zeichen besteht; 5tes Zeichen ist \0 der das Ende vom String anzeigt

  adc_init;
	uart_init (BAUDRATE);

  uint16_t value = adc_read(3); // der dritte/vierte? channel wird eingelesen

	char array[] = "Starte Programm\n\r";
	uart_sendstr(array);

	while(1) {
		value = adc_read(0);
		intToString(value, stringMemory);
		uart_sendstr (stringMemory);
		uart_sendstr("\n\r");
		_delay_ms(100);

	}
}
