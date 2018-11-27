/*
Authors:
Harald Schuster

Sends a message over SPI.
*/


#include <avr/io.h>
#include <inttypes.h>
#include "dogm_lcd.h"

#include <util/delay.h>



//
int main(void) {
	int i = 5;
	
	
	// Initialize the SPI interface for the LCD display
	lcdSpiInit();

	// Initialize the LCD display
	lcdInit();

	lcdWriteString(LINE2, TWO_LINES_OFF, "Das ist ein %i", i);
	_delay_ms(5000);
	lcdWriteString(LINE1, TWO_LINES_ON, "Das ist ein %i.", i);
	_delay_ms(5000);


    lcdSetCursor(1, 0);
	lcdWriteChar(0x3C);
   // lcdWriteString(0, "Das ist ein %i", i);
	
	lcdCursorOnOff(CURSOR_OFF, POSITION_OFF);
/*
	_delay_ms(2000);
	
	lcdWriteString(text);

	_delay_ms(2000);

	lcdOnOff(LCD_OFF);
	
	_delay_ms(2000);
	lcdOnOff(LCD_ON);
	lcdCursorOnOff(CURSOR_OFF, POSITION_OFF);

	_delay_ms(1000);

	for (i = 0 ; i < 30; i++)
	{
		if(i < 16)
			lcdSetCursor(0, i);
		else
			lcdSetCursor(1, i-16);
		lcdWriteChar(i+8);
		_delay_ms(500);
	}

	_delay_ms(2000);
	lcdCursorOnOff(CURSOR_ON, POSITION_OFF);

		_delay_ms(2000);

	lcdOnOff(LCD_OFF);

		_delay_ms(1000);

	lcdOnOff(LCD_ON);
*/

	while (1)
	{
	
	} //endlessly

/*we never reach this*/
return 0;
}





