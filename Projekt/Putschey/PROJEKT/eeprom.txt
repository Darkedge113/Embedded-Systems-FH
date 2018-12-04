
#define F_CPU 16000000

/** IO includes */
#include <avr/io.h>
/** _delay_ms */
#include <util/delay.h>

/** EEPROM base address **/
#define EE_ADDR 0b10100000
/** EEPROM Read flag */
#define EE_R 1
/** EEPROM Write flag */
#define EE_W 0
/** TWI status byte */
#define TWI_STATUS (TWSR & ~0b111)

/** How many button presses do we save? */
#define COUNT_BUTTONS   6
/** Start address for button savings... */
#define BUTTON_START    0x0F
/** Reset via jump to address 0 */
#define RESET() asm volatile (" jmp 0")

#if COUNT_BUTTONS > 9
    #error "Please define less than 9 button presses!"
#endif



/** ++++++++++   UART functions   ++++++++++ */
void uart_init (uint32_t baudrate)
{
    uint16_t  ubrr = (F_CPU / 8 / baudrate) - 1; 
    UBRR0H = (uint8_t) (ubrr >> 8);
    UBRR0L = (uint8_t) (ubrr & 0xff);
    UCSR0A |= (1<<U2X0);  //  "double speed" (bit 1) 
    UCSR0B |= ( 1<<TXEN0);   // enable UART transmit
    UCSR0B |= ( 1<<RXEN0);   // enable UART receive
}

void uart_transmit (uint8_t data)
{
	while ( (UCSR0A & (1 << UDRE0)) == 0); // warten, bis bit UDRE0 (bit 5) in UCSR0A 1 wird -> free to send !
	UDR0 = data;			       // data senden !
}

uint8_t uart_receive ()
{
	while ( (UCSR0A & (1 << RXC0)) == 0); // warten, bis bit bit RXC0 in UCSR0A 1 wird -> received something !
	return(UDR0);			      // auslesen und zur?ckgeben !
}

void uart_sendstring ( char * str )
{
	while ( * str != 0 )  
	{
		uart_transmit ( * str);
		str++;
	}
}

/** ++++++++++   TWI functions   ++++++++++ */
void twi_start() 
{
    //send start condition
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
    //wait for finished start bit transmission
    while ((TWCR & (1 << TWINT)) == 0);
}

void twi_stop() 
{
    //send stop bit
    TWCR = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);
}

uint8_t twi_read_ack() 
{
    //read a byte (with ack set)
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    //wait for finish
    while ((TWCR & (1 << TWINT)) == 0);
    //read data from twdr
    return TWDR;
}

uint8_t twi_read_nack() 
{
    //read a byte (without ack set)
    TWCR = (1 << TWINT) | (1 << TWEN);
    //wait for finish
    while ((TWCR & (1 << TWINT)) == 0);
    //read from TWDR
    return TWDR;
}

void twi_write(uint8_t value) 
{
    //load data into TWDR
    TWDR = value;
    //start transmission
    TWCR = (1 << TWINT) | (1 << TWEN);
    //wait for finish
    while ((TWCR & (1 << TWINT)) == 0);
}


void twi_init(uint32_t scl) {
    //reset status register
    TWSR = 0;
    //calculate bitrate (datasheet!)
    TWBR = ((F_CPU / scl) - 16)>>1;
    //enable
    TWCR = (1 << TWEN);
}

void eeprom_write_byte(uint16_t addr, uint8_t value) {
    twi_start();
    //W: EEPROM twi addr
    twi_write(EE_ADDR | EE_W);
    //W: EEPROM memory addr (high byte)
    twi_write((uint8_t)addr >> 8);
    //W: EEPROM memory addr (low byte)
    twi_write((uint8_t)addr & 0xFF);
    //W: value
    twi_write(value);
    twi_stop();
}

uint8_t eeprom_read_bytes(uint16_t addr, uint8_t *values, uint8_t size) {
    uint8_t i = 0;
    //no length given -> return (no bytes are read)
    if(size == 0) return 0;

    twi_start();
    //W: EEPROM twi addr
    twi_write(EE_ADDR | EE_W);
    //W: EEPROM memory addr (high byte)
    twi_write((uint8_t)addr >> 8);
    //W: EEPROM memory addr (low byte)
    twi_write((uint8_t)addr & 0xFF);
    //restart  
    twi_start();
    //W: EEPROM twi addr (read mode)
    twi_write(EE_ADDR | EE_R);
    //R: EEPROM byte(s) 
    for(; i<(size-1); i++) values[i] = twi_read_ack();
    //R: last byte (without ACK)
    values[size-1] = twi_read_nack();
    
    //stop TWI
    twi_stop();
    //return count of read bytes
    return i;
}

/** ++++++++++   button CLI   ++++++++++ */
void printButtons(void)
{
    //use array for all buttons
    uint8_t btn[COUNT_BUTTONS];
    //read amount of bytes
    eeprom_read_bytes(BUTTON_START,btn,COUNT_BUTTONS);
    //output via serial...
    uart_sendstring("Following buttons were pressed last time:\r\n");
    for(uint8_t i = 0; i<COUNT_BUTTONS; i++)
    {
        //do some sanity check, if it is a correct btn number, send
        //number otherwise send 'e'
        if(btn[i] <= 3 && btn[i] >= 1)
        {
            uart_transmit(btn[i]+'0');
        } else {
            uart_transmit('e');
        }
        uart_transmit(' ');
    }
    uart_sendstring("\r\n");
}

/** ++++++++++   MAIN   ++++++++++ */
int main(void) 
{
    uint8_t press_count = 0;
    uint8_t button[COUNT_BUTTONS];
    
    //init uart (115k2; 8N1)
    uart_init(115200);
    //init TWI (100kHz clock)
    twi_init(100000);
    //init buttons
    DDRD &= ~((1<<PD5)|(1<<PD6)|(1<<PD7));
    PORTD |= (1<<PD5)|(1<<PD6)|(1<<PD7);
    
    uart_sendstring("Welcome!\r\n");
    
    printButtons();
    
    uart_sendstring("Please press ");
    uart_transmit(COUNT_BUTTONS+'0');
    uart_sendstring(" buttons to continue\r\n");
    
    while(1)
    {
        //test for pressed buttons
        switch(PIND & ((1<<PD5)|(1<<PD6)|(1<<PD7)))
        {
            //PD5 pressed (PD6 & PD7 are 1)
            case (1<<PD6)|(1<<PD7):
                button[press_count] = 1;
                press_count++;
                uart_sendstring("Button 1 pressed\r\n");
                //debounce via delay
                _delay_ms(50);
                //wait for button release
                while((PIND & (1<<PD5)) == 0);
                //debounce via delay
                _delay_ms(50);
            break;
            //PD6 pressed (PD5 & PD7 are 1)
            case (1<<PD5)|(1<<PD7):
                button[press_count] = 2;
                press_count++;
                uart_sendstring("Button 2 pressed\r\n");
                //debounce via delay
                _delay_ms(50);
                //wait for button release
                while((PIND & (1<<PD6)) == 0);
                //debounce via delay
                _delay_ms(50);
            break;
            //PD7 pressed (PD5 & PD6 are 1)
            case (1<<PD5)|(1<<PD6):
                button[press_count] = 3;
                press_count++;
                uart_sendstring("Button 3 pressed\r\n");
                //debounce via delay
                _delay_ms(50);
                //wait for button release
                while((PIND & (1<<PD7)) == 0);
                //debounce via delay
                _delay_ms(50);
            break;
            
            //no buttons are pressed or more than one
            default: break;
        }
            
        //if we have our wanted amount, save to eeprom & reset
        if(press_count == COUNT_BUTTONS) 
        {
            //save to eeprom
            for(uint8_t i = 0; i<COUNT_BUTTONS; i++)
            {
                eeprom_write_byte(BUTTON_START+i,button[i]);
                _delay_ms(10);
            }
            uart_sendstring("All buttons pressed & saved -> resetting\r\n");
            //delay a little bit
            _delay_ms(50);
            //reset via jmp 0
            RESET();
        }
    }
}











