#define F_CPU 16000000
#include <avr/io.h>
#define BAUDRATE 115200

uint8_t uart_receive () {	
	
	while (!(UCSR0A & (1<<RXC0))) ;
		return (UDR0);
}

void uart_transmit (uint8_t OUTPUT) {
	
	while (!(UCSR0A & (1<<UDRE0))) ;
			UDR0 = OUTPUT;
}

void uart_init( uint32_t baud) {
	
	uint16_t BRR =  (F_CPU / (8 * baud)) -1;   // kann größer als 255 sein !
	
	UBRR0H = (BRR >> 8) ;     // get high byte and store it in UBRR0H
	UBRR0L = (BRR & 0xff);    // low byte
	
	UCSR0B |= (1<<TXEN0) + (1<<RXEN0);  // enable UART receiver and transmitter
	
	UCSR0A |= (1<< U2X0);     // activate double speed for UART timing
}

void uart_sendstr( char * str ) {
	
	while ( * str ) {
		uart_transmit (* str);
		str++;
	}
}

int main() {
	
	uart_init (BAUDRATE);

	char array[] = "Starte Programm\n\r";
	uart_sendstr(array);

	while(1) {
		
		uint8_t input;
		uint8_t port;
		uint8_t pin;
	
		input = uart_receive();
			
			switch(input){
				case 'E':
				port = uart_receive();
				pin = uart_receive()-'0'; // Charakter-Wert von 0 wird abgezogen um auf die echte Zahl zu kommen
			
				switch(port) {
					case 'B':
					uart_sendstr("\r\nEinschalten\r\n");
					DDRB |= (1<<pin);
					PORTB |= (1<<pin);					
					break;
					
					case 'C':
					uart_sendstr("\r\nEinschalten\r\n");
					DDRC |= (1<<pin);
					PORTC |=  (1<<pin);
					break;
					
					case 'D':
					uart_sendstr("\r\nEinschalten\r\n");
					DDRD |= (1<<pin);
					PORTD |=  (1<<pin);					
					break;
					
					default:
					uart_sendstr("\r\nPort nicht gefunden!\r\n");
					break;					
				}
				break;				
							
				case 'A':
				port = uart_receive();
				pin = uart_receive()-'0'; // Charakter-Wert von 0 wird abgezogen um auf die echte Zahl zu kommen
					
				switch(port) {
					case 'B':
					uart_sendstr("\r\nAusschalten\r\n");
					DDRB |= (1<<pin);
					PORTB &=  ~(1<<pin);					
					break;
					
					case 'C':
					uart_sendstr("\r\nAusschalten\r\n");
					DDRC |= (1<<pin);
					PORTC &=  ~(1<<pin);
					break;
					
					case 'D':
					uart_sendstr("\r\nAusschalten\r\n");
					DDRD |= (1<<pin);
					PORTD &=  ~(1<<pin);					
					break;
					
					default:
					uart_sendstr("\r\nPort nicht gefunden!\r\n");
					break;					
				}
				break;		
				
						
				case'L':
				
				port = uart_receive();
				pin = uart_receive()-'0'; // Charakter-Wert von 0 wird abgezogen um auf die echte Zahl zu kommen
					
				switch(port) {
					case 'B':
					
					DDRB &= ~(1<<pin); //Eingegebener Pin von Port B ist ein Eingang
					PORTB |= (1<<pin); //Aktiviert internen Pull-Up auf eingegebenen Pin	
					
					if (!(PINB & (1<<pin))) {			
						uart_sendstr("\r\nGeschlossen\r\n");
					}
			
					else  {			
						uart_sendstr("\r\nOffen\r\n");	
					}
								
					break;
					
					case 'C':
					
					DDRC &= ~(1<<pin); //Eingegebener Pin von Port B ist ein Eingang
					PORTC |= (1<<pin); //Aktiviert internen Pull-Up auf eingegebenen Pin
					
					if (!(PINC & (1<<pin))) {			
						uart_sendstr("\r\nGeschlossen\r\n");
					}
			
					else  {			
						uart_sendstr("\r\nOffen\r\n");	
					}
					break;
					
					case 'D':
					
					DDRD &= ~(1<<pin); //Eingegebener Pin von Port B ist ein Eingang
					PORTD |= (1<<pin); //Aktiviert internen Pull-Up auf eingegebenen Pin	
					
					if (!(PIND & (1<<pin))) {			
						uart_sendstr("\r\nGeschlossen\r\n");
					}
			
					else  {			
						uart_sendstr("\r\nOffen\r\n");	
					}				
					break;
					
					default:
					uart_sendstr("\r\nPort nicht gefunden!\r\n");
					break;					
				}
				break;
				
				
				default:
				uart_sendstr("\r\nwIe bItTe?!\r\n");
				break;
				
		}	
	}
}
