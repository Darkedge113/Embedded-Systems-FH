#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <stdint.h>

void eeprom_init(uint32_t scl);
void eeprom_write_byte(uint16_t target, uint8_t value);
uint8_t eeprom_read_byte(uint16_t target);

#endif /* _EEPROM_H_ */
