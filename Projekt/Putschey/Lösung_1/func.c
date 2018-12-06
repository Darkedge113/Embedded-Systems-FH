#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#define ERROR 0
#define SUCCESS 1
#define EEDEVADR 0b10100000
#include "def.h"


void uart_init (uint32_t baudrate){
  // Set baud rate
  uint16_t ubrr = (F_CPU/8/baudrate)-1;
  UBRR0H = (uint8_t)(ubrr>>8); // get higher 8 bits
  UBRR0L = (uint8_t)(ubrr&0xff); // get lower 8 bits
  //Use double speed
  UCSR0A |= (1<<U2X0);
  // Enable receiver and transmitter
  UCSR0B = (1<<TXEN0 | 1<<RXEN0 | 1<<RXCIE0 );
}

char uart_receive(){
  while (!(UCSR0A & (1<<7))); //1<<7 = RXC0
  return (UDR0);
}

void uart_transmit(char c){
  while (!(UCSR0A	& (1<<UDRE0)));
  UDR0=c;
}

void uart_sendstring(char *str){
  uint8_t i = 0;
  while (str[i]) {
    uart_transmit(str[i]);
    i++;
  }
}

void spi_init(void){
  DDRB = (1<<PIN_CLK)|(1<<PIN_MOSI)|(1<<PIN_CSB)|(1<<PIN_RS);		// Ausgang setzen RS auf pin 1 und CSB auf pin 2
  PORTB |= (1<<PIN_CSB);											// Auf 1 setzen sodass er nichts macht
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);							// Enable SPI, Master, set clock rate fck/64
}

void transmit(char cData){
  SPDR = cData;													// Start Transmission
  while(!(SPSR & (1<<SPIF)));										// Warten bis sie fertig ist
}

void clear_display(){
  PORTB &= ~(1<<PIN_RS);
  PORTB &= ~(1<<PIN_CSB);

  transmit(CLEAR_DISPLAY);
  PORTB |= (1<<PIN_CSB);
}

void write_char(char instruction){									// Schreibt ein char
  PORTB |= (1 << PIN_RS);											//RS high = data
  PORTB &= ~(1<<PIN_CSB);											// Wieder auf 0 Setzen

  transmit(instruction);											// Char schicken
  _delay_ms(2);

  PORTB |= (1<<PIN_CSB);											// Wieder auf 1 setzen
}

void gotoxy(uint8_t y, uint8_t x){									// Geht auf die Position die man will
  uint8_t addr;
  PORTB &= ~(1 << PIN_RS);
  PORTB &= ~(1<<PIN_CSB);

  addr = (y * 0x40) + x -1;										// Adresse wird berechnet

  transmit(0x80 | addr);											// gesendet 0x80 wird gebraucht

  PORTB |= (1<<PIN_CSB);
}

void write_string(char *str){										// Schreibt einen String
  int count = 0;
  int i = 1;
  while (*str){
    if(count < 16){
      write_char(*str);
    }
    if(count >= 16){
      gotoxy(1,i);
      write_char(*str);
      i++;
    }
    str++;
    count++;
  }
}

void lcd_init(void) {
  _delay_ms(50);													// Warten bis die Spannungsversorgung stabil ist
  PORTB &= ~(1<<PIN_RS);											// Ist ein Command
  PORTB &= ~(1<<PIN_CSB);											// Wenn auf 0 kann senden
  transmit(FUNCTION_SET_1);
  _delay_us(30);
  transmit(FUNCTION_SET_2);										//FUNCTION Set
  _delay_us(30);
  transmit(BIAS_SET);												//BIAS, 1D Starkes nachleuchten
  _delay_us(30);;
  transmit(CONTRAST_SET);											//CONTRAST
  _delay_us(30);
  transmit(POWER_CONTRAST_SET);									//Power,Contrast
  _delay_us(30);
  transmit(FOLLOWER_SET);											//Spannungsfolger

  _delay_ms(250);
  transmit(DISPLAY_ON);											//DISPLAY ON
  _delay_ms(1);
  transmit(ENTRY_MODE);											//Enty Mode
  _delay_ms(1);
  PORTB |= (1<<PIN_CSB);											//CS auf high -> momentan aus

  _delay_ms(100);
  write_string("Display OK");
  _delay_ms(3000);
  clear_display();
  _delay_ms(20);
  write_string("After vanish Enter String");
  _delay_ms(3000);
  clear_display();
  _delay_ms(20);
}

void display_off(){
  PORTB &= ~(1<<PIN_RS);
  PORTB &= ~(1<<PIN_CSB);

  transmit(DISPLAY_OFF);
  PORTB |= (1<<PIN_CSB);
}

void TWIInit(void){
  //set SCL to 100kHz
  TWSR = 0x00; //(TWPS1 | TWPS0); // Prescaler 1
  TWBR = 0x48; // 100khz
  //enable TWI
  TWCR = (1<<TWEN);
}

// send start signal
void TWIStart(void){
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void TWIStop(void){
  TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite(uint8_t u8data){
  TWDR = u8data;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWIReadACK(void){
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  while ((TWCR & (1<<TWINT)) == 0);
  return TWDR;
}

//read byte with NACK
uint8_t TWIReadNACK(void){
  TWCR = (1<<TWINT)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
  return TWDR;
}

uint8_t TWIGetStatus(void){
  uint8_t status;
  //mask status
  status = TWSR & 0xF8;
  return status;
}

uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data){
  TWIStart();
  if (TWIGetStatus() != 0x08){
    return ERROR;
  }
  TWIWrite((EEDEVADR)|(uint8_t)((u16addr & 0x0700)>>7));
  if (TWIGetStatus() != 0x18){
    return ERROR;
  }
  //send the rest of address
  TWIWrite((uint8_t)(u16addr<<8));  // high byte
  if (TWIGetStatus() != 0x28){
    return ERROR;
  }
  TWIWrite((uint8_t)(u16addr));  // low byte
  if (TWIGetStatus() != 0x28){
    return ERROR;
  }
  //write byte to eeprom
  TWIWrite(u8data);				// send data
  if (TWIGetStatus() != 0x28){
    return ERROR;
  }
  TWIStop();
  return SUCCESS;
}

uint8_t EEReadByte(uint16_t u16addr, uint8_t *u8data){
  TWIStart();
  if (TWIGetStatus() != 0x08){
    return ERROR;
  }
  //select devise and send A2 A1 A0 address bits
  TWIWrite((EEDEVADR)|((uint8_t)((u16addr & 0x0700)>>7)));
  if (TWIGetStatus() != 0x18){
    return ERROR;
  }
  //send the rest of address
  TWIWrite((uint8_t)(u16addr<<8));// high byte
  if (TWIGetStatus() != 0x28){
    return ERROR;
  }
  TWIWrite((uint8_t)(u16addr));// low byte
  if (TWIGetStatus() != 0x28){
    return ERROR;
  }
  //send start
  TWIStart();
  if (TWIGetStatus() != 0x10){
    return ERROR;
  }
  //select devise and send read bit
  TWIWrite((EEDEVADR)|((uint8_t)((u16addr & 0x0700)>>7))|1);
  if (TWIGetStatus() != 0x40){
    return ERROR;
  }
  *u8data = TWIReadNACK();
  if (TWIGetStatus() != 0x58){
    return ERROR;
  }
  TWIStop();
  return SUCCESS;
}

void int2str(char *str, uint16_t val){				//Integer zu String kovertieren
  str[0]=val%10+'0';
  str[1]='\0';
}

// Werden wir nicht mehr brauchen
char* fuse_string(const char *s1, const char *s2, const char *s3, const char *s4){			// Wird wahrschenlich nicht gebraucht
  char *result = malloc(strlen(s1)+strlen(s2)+strlen(s3)+strlen(s4)+1);					//+1 for the null-terminator

  strcpy(result, s1);
  strcat(result, s2);
  strcat(result, s3);
  strcat(result, s4);
  return result;
}

void OutputData(uint16_t u16eaddres){ 				// wird am Anfang aufgerufen, parameter ist die addresse.
  uint8_t datastr=0;
  char *s;
  char str[2];
  char str2[1];

  for (int j = 0; j < 5; j++){
    if (EEReadByte(j, &datastr) != ERROR){
      _delay_ms(50);
      int2str(str, j+1);													//Stelle die gedrückt wurde zb. 1
      int2str(str2, datastr);												// Daten aus eeprom werden in String konvertiert.
      s = fuse_string("Button press ", str," was on the PB", str2);
      write_string(s);

      _delay_ms(2000);
      clear_display();

    }
  }
}

void piezo(int k){
  BUZZER_R |= (1 << BUZZER_PIN);		 // Set the port for the buzzer output
  int i = 0;
  while(i < 50){
    BUZZER_PORT |= (1<<BUZZER_PIN);
    for(int j = 0; j <= k; j++ ){
      _delay_ms(1);
    }
    BUZZER_PORT &= ~(1<<BUZZER_PIN);
    for(int j = 0; j <= k; j++ ){
      _delay_ms(1);
    }
    i++;
  }
}
