#include <avr/io.h>
#ifndef _F_CPU_
  #define F_CPU 16000000
#endif

void adc_init() {

	ADCSRA = (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); //select prescaler for ADC clock 125kHz
	ADCSRA |= (1<<ADEN); //enable the ADC
  ADMUX = (1<<REFS0); //select internalt 5V reference voltage; = funktioniert, weil die anderen bits 0 sind
}

void intToString(uint16_t val, char * target) {

  int8_t index;
  for(index = 3; index >= 0; index--) {

	  target [index] = val % 10 + '0';
	  val /= 10;
	}
	target[4] = 0;
}

uint16_t adc_read(uint8_t channel) { //damit man einen input hat welche channel eingelesen wird

	uint16_t result;

	ADMUX &= 0xf0; //clear lower 4 bits in ADMUX
	ADMUX |= (channel); //select channel for conversion
	ADCSRA |= (1<<ADSC); //start conversion

	while (ADCSRA & (1<<ADSC)) ; //wait until conversion is finished

	result = ADCL; //read low byte
	result += (ADCH << 8); //add high byte

	return (result);
}
