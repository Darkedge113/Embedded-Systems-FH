// Robert Eres

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


int main() {

	DDRB |= (1<<2)+(1<<3)+(1<<4)+(1<<5); // Pin 2,3 und 4 von Port B sind Ausgang
	
	DDRD &= ~(1<<7); //Pin 7 von Port D ist ein Eingang
	
	PORTD |= (1<<7); //Pull-Up Widerstand an Port 7 ist aktiv, da mir kein 10k Ohm Resistor zur Verfügung stand
	
	uint8_t INPUT = 0;

//Init Phase

	uint8_t a = 0;
	
//Stable Program, running

	while(a<3) {
		
	PORTB |= (1<<2)+(1<<3)+(1<<4)+(1<<5); // Setze Pin 2,3 und 4 auf 1, anderes Verhalten als 0; hier voltage high
	_delay_ms(100);
	
	
	PORTB &= ~(1<<2)+~(1<<3)+~(1<<4)+~(1<<5); // Setze Pin 2,3 und 4 auf 0, durch UND Verknüpfung mit invertiertem Byte!	
	_delay_ms(100);
	
	a++;
}
	
	
	while (1) {
	
	if(PIND & (1<<7)) { //via DDR ist PIND input -> mit Maske abgleichen um nur den Pin zu checken -> alles != 0 funktioniert!
		
		PORTB &= ~(1<<2);
		PORTB |= (1<<5);
		_delay_ms(500);
		
		PORTB &= ~(1<<5);
		PORTB |= (1<<4);
		_delay_ms(500);
		
		PORTB &= ~(1<<4);
		PORTB |= (1<<3);
		_delay_ms(500);
		
		PORTB &= ~(1<<3);
		PORTB |= (1<<2);
		_delay_ms(500);
		
		}
		
		else {
			
		PORTB &= ~(1<<5);
		PORTB |= (1<<2);
		_delay_ms(500);
		
		PORTB &= ~(1<<2);
		PORTB |= (1<<3);
		_delay_ms(500);
		
		PORTB &= ~(1<<3);
		PORTB |= (1<<4);
		_delay_ms(500);
		
		PORTB &= ~(1<<4);
		PORTB |= (1<<5);
		_delay_ms(500);
			
		}
	}
}
