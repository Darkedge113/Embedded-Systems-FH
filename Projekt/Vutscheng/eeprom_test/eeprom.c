#include <avr/io.h>
#include <util/twi.h> /* two wire interface */

#include "eeprom.h"
#include "uart.h"

/* debug notes: when debug mode enabled (!= 0):
 * underscore (quasi-private) functions:
 * on exit  print: < [function name]
 * public functions:
 * on enter print: >> [function name]
 * on exit  print: << [function name]
 */
static const uint8_t debug = 0;

#define EEPROM_ADDRESS 0b10100000 /* last digit must be 0. */
#define READ_MODE  1
#define WRITE_MODE 0

void _twi_start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); /* start  bit. */
  while ((TWCR & (1 << TWINT)) == 0); /* block until transmission complete. */
  if (debug) uart_sendstring("<  start()\n\r");
}

void _twi_stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); /* stop bit. */
  if (debug) uart_sendstring("<  stop()\n\r");
}

uint8_t _twi_read_ack() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); /* include ack bit. */
  while ((TWCR & (1 << TWINT)) == 0); /* block until transmission complete. */
  if (debug) uart_sendstring("<  read_ack()\n\r");
  return TWDR;
}

uint8_t _twi_read_nack() {
  TWCR = (1 << TWINT) | (1 << TWEN); /* ommit ack bit. */
  while ((TWCR & (1 << TWINT)) == 0); /* block until transmission complete. */
  if (debug) uart_sendstring("<  read_nack()\n\r");
  return TWDR;
}

void _twi_write(uint8_t value) {
  TWDR = value; /* data register. */
  TWCR = (1 << TWINT) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0); /* block until transmission complete. */
  if (debug) uart_sendstring("<  write()\n\r");
}

void _twi_send_address(uint16_t target) {
  _twi_write((uint8_t)target >> 8);   /* 8 MSB. */
  _twi_write((uint8_t)target & 0xFF); /* 8 LSB. */
}

uint8_t _twi_read_status() {
  return TWSR & ~0b111; /* mask out 3 LSB, we need the 5 MSB. */
  if (debug) uart_sendstring("<  read_status()\n\r");
}

void eeprom_init(uint32_t scl) {
  if (debug) uart_sendstring(">> twi_init()\n\r");
  TWSR = 0; /* clear status register. */

  TWBR = 0.5 * ((F_CPU / scl) - 16); /* calculate bit rate. */
  TWCR = (1 << TWEN); /* enable TWI. */
  if (debug) uart_sendstring("<< twi_init()\n\r");
}

void eeprom_write_byte(uint16_t target, uint8_t value) {
  if (debug) uart_sendstring(">> eeprom_write_byte()\n\r");
  _twi_start();

  _twi_write(EEPROM_ADDRESS | WRITE_MODE); /* select device and mode. */
  _twi_send_address(target);
  _twi_write(value);

  _twi_stop();
  if (debug) uart_sendstring("<< eeprom_write_byte()\n\r");
}

uint8_t eeprom_read_byte(uint16_t target) {
  if (debug) uart_sendstring(">> eeprom_read_byte()\n\r");
  uint8_t value = 0;
  _twi_start();

  _twi_write(EEPROM_ADDRESS | WRITE_MODE);
  _twi_send_address(target);

  _twi_start();
  _twi_write(EEPROM_ADDRESS | READ_MODE);
  value = _twi_read_nack();

  _twi_stop();
  if (debug) uart_sendstring("<< eeprom_read_byte()\n\r");
  return value;
}

