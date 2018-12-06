#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "def.h"

char string[5];

void spi_init();
void lcd_init();
void write_string(char* string);
void clear_display();
void display_off();
void gotoxy(uint8_t y, uint8_t x);
void TWIInit(void);
void uart_init (uint32_t baudrate);
uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data);
uint8_t EEReadByte(uint16_t u16addr, uint8_t *u8data);
void OutputData(uint16_t u16eaddres);
void piezo(int k);
void display_off();
char uart_receive();
void uart_sendstring(char *str);
void uart_transmit(char c);
void write_char(char instruction);
char line[32];
char c;
int e = 0;
int volatile received;

ISR(USART_RX_vect){
  c = UDR0;

  if(c != '\n'){
    line[e] = c;
    e++;
  }else{
    line[e] = '\0';
    write_string(line);
    received = 1;
    e = 0;
  }
}

int main(void){
  uint8_t pressed = 0;
  uint16_t u16eaddress=0;
  uint8_t data=0;
  int t = 0;

  DDRD &= ~(1<<2);	// Button
  PORTD |= (1<<2);

  DDRD &= ~(1<<3);	// Button
  PORTD |= (1<<3);

  spi_init();
  lcd_init();
  uart_init(115200);
  TWIInit();

  sei();

  while (1){
    if(received == 1){
      _delay_ms(5000);
      // dort kommt rein
      clear_display();
      received = 0;
    }

    if(t == 1){							// Wenn Display ausgeschalten ist soll diese Funktion ausgeführt werden, t wird unten gesetzt
      _delay_ms(3000);
      lcd_init();
      write_string("Display OK");
      _delay_ms(3000);
      clear_display();
      _delay_ms(20);
      write_string("After vanish enter String");
      _delay_ms(3000);
      clear_display();
      t = 0;
    }

    if (u16eaddress<5){
      if((PIND & (1<<2)) == 0||(PIND & (1<<3)) ==0){
        _delay_ms(50);
        if (pressed==0){						//Zweg Button bouncing
          if((PIND & (1<<2)) == 0){
            data = 7;
          }
          EEWriteByte(u16eaddress, data);
          u16eaddress++;
          pressed = 1;
          _delay_ms(100);
        }
      }else{
        pressed = 0;
      }
    }else{
      u16eaddress = 0;
    }

    if((PIND & (1<<3)) == 0){						// Wenn der Button gedrückt worden ist, dann soll das Display clearen und auslesen.
      clear_display();
      _delay_ms(10);
      int i = 0;
      while(i < 3){
        if(i == 0){								// Erster Auslesevorgang
          piezo(1);							// Piezo Buzzer
          _delay_ms(200);
          OutputData(u16eaddress);
          //for(int i = 0; i < 2000: i++){
          //	_delay_ms(1);
          //	if(PIND & (1<<2)) == 0){ Button
          //	}
          //}
          clear_display();
        }
        if(i == 1){								// Zweiter Auslesevorgang
          int k = 0;
          while(k < 2){
            piezo(1);
            _delay_ms(200);
            k++;
          }
          OutputData(u16eaddress);
          //for(int i = 0; i < 2000: i++){
          //	_delay_ms(1);
          //	if(PIND & (1<<2)) == 0){ Button
          //	}
          //}
          clear_display();
        }
        if(i == 2){								// Dritter Auslesevorgang
          int j = 0;
          while(j < 3){
            piezo(1);
            _delay_ms(200);
            j++;
          }
          OutputData(u16eaddress);
          //for(int i = 0; i < 2000: i++){
          //	_delay_ms(1);
          //	if(PIND & (1<<2)) == 0){ Button
          //	}
          //}
          clear_display();					// Nachdem 3 Durchlauf wird das Display abgeschaltet und oben wieder ein geschaltet (unötig)
          _delay_ms(3000);
          display_off();
          _delay_ms(2000);
          t = 1;
        }
        i++;
      }
    }





  }
}
