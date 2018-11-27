/* vim: foldmethod=syntax foldnestmax=1 foldenable
   benjamin medicke */

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "config.h"
#include "eeprom.h"
#include "uart.h"

#define EEPROM_SIZE_IN_BYTES 256


void send_memory_layout() {
  uart_sendstring("\n\rdumping eeprom");
  int i = 0;
  for (i = 0; i < EEPROM_SIZE_IN_BYTES; i++) {
    if (i % 32 == 0) uart_sendstring("\n\r");
    if (i % 8 == 0) uart_sendstring(" ");
    uart_transmit(eeprom_read_byte(i) + '0');
  }
  uart_sendstring("\n\rend of eeprom\n\r");
}

int main() {
  uart_init(BAUD);
  eeprom_init(SCL);
  
  eeprom_write_byte(1,250);

  send_memory_layout();
  /* clear_eeprom(); */

  for (;;) {
  }
}

