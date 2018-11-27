#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef BAUD
#define BAUD 115200
#endif

#define SCL 400000

#define EEPROM_STARTING_ADDRESS 0
#define EEPROM_TERMINATOR 0

#define BUTTON_DDR  DDRD
#define BUTTON_PIN  PIND
#define BUTTON_PORT PORTD

#define BUTTON1 (1<<PD5)
#define BUTTON2 (1<<PD6)
#define BUTTON3 (1<<PD7)

#endif /* _CONFIG_H_ */
