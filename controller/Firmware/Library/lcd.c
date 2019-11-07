/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: STKX00
 * Platform: ATmeag8/16/2560
 * -------------------------------------
 * Name: adc
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       display characters onto the
 *       LCD @ 4 bit mode
 * -------------------------------------
 */

#include "lcd.h"

//	+---------------------------------------------------------------+
//	|						LCD initialization						|
//	+---------------------------------------------------------------+
void lcd_init(void)
{	
	// Initialize LCD command and data lines
	LCD_DDR_CTRL |= (1<<LCD_RS) | (1<<LCD_E);
	LCD_DDR_DATA |= (1<<LCD_DB3) | (1<<LCD_DB2) | (1<<LCD_DB1) | (1<<LCD_DB0);
	
	LCD_PORT_CTRL &= ~((1<<LCD_RS) | (1<<LCD_E));
	LCD_PORT_DATA &= ~((1<<LCD_DB3) | (1<<LCD_DB2) | (1<<LCD_DB1) | (1<<LCD_DB0));
	
	// Wait until LCD has started
	_delay_ms(LCD_STARTUP_TIME);

	lcd_set(LCD_CLEAR);
	_delay_ms(LCD_CLEAR_TIME);
	
	// Setup 4 bit mode & wait function time
	lcd_set(LCD_FUNCTION);
	_delay_us(LCD_FUNCTION_TIME);
	
	// Setup LCD settings
	lcd_cmd(LCD_FUNCTION | LCD_FUNCTION_2LINE);		// Setup number of display lines and character font
	lcd_cmd(LCD_DISPLAY | LCD_DISPLAY_ON);			// Setup display status, display cursor, display cursor blink
	lcd_cmd(LCD_ENTRY | LCD_ENTRY_INCREMENT);		// Setup display cursor move direction

	// Clears entire display
	lcd_clear();
}

//	+---------------------------------------------------------------+
//	|					LCD disable function						|
//	+---------------------------------------------------------------+
void lcd_disable(void)
{
	// Disable LCD
	LCD_DDR_CTRL &= ~((1<<LCD_RS) | (1<<LCD_E));
	LCD_DDR_DATA &= ~((1<<LCD_DB3) | (1<<LCD_DB2) | (1<<LCD_DB1) | (1<<LCD_DB0));
	
	LCD_PORT_CTRL &= ~((1<<LCD_RS) | (1<<LCD_E));
	LCD_PORT_DATA &= ~((1<<LCD_DB3) | (1<<LCD_DB2) | (1<<LCD_DB1) | (1<<LCD_DB0));
}

//	+---------------------------------------------------------------+
//	|						LCD generate clock						|
//	+---------------------------------------------------------------+
void lcd_clock(void)
{
	LCD_PORT_CTRL |= (1<<LCD_E);		// Enable E (HIGH) @ control port
	_delay_us((1000000UL/(F_LCD * 2)));	// Wait half of defined clock period
	LCD_PORT_CTRL &= ~(1<<LCD_E);		// Disalbe E (LOW) @ control port
	_delay_us((1000000UL/(F_LCD * 2)));	// Wait half of defined clock period
}

//	+---------------------------------------------------------------+
//	|						LCD set databyte						|
//	+---------------------------------------------------------------+
void lcd_set(unsigned char data)
{
	// Reset LCD data port
	LCD_PORT_DATA &= ~((1<<LCD_DB3) | (1<<LCD_DB2) | (1<<LCD_DB1) | (1<<LCD_DB0));

	if(data & (1<<7))					// Check if data bit 7 is set
		LCD_PORT_DATA |= (1<<LCD_DB3);	// Set data bit 3 @ databus
	if(data & (1<<6))					// Check if data bit 6 is set
		LCD_PORT_DATA |= (1<<LCD_DB2);	// Set data bit 2 @ databus
	if(data & (1<<5))					// Check if data bit 5 is set
		LCD_PORT_DATA |= (1<<LCD_DB1);	// Set data bit 1 @ databus
	if(data & (1<<4))					// Check if data bit 4 is set
		LCD_PORT_DATA |= (1<<LCD_DB0);	// Set data bit 0 @ databus

	// Generate a clock period
	lcd_clock();
}

//	+---------------------------------------------------------------+
//	|					LCD instruction transfer					|
//	+---------------------------------------------------------------+
void lcd_cmd(unsigned char instruction)
{
	// Select instruction register
	LCD_PORT_CTRL &= ~(1<<LCD_RS);
	
	lcd_set(instruction);		// Write high nibble to databus
	lcd_set((instruction<<4));	// Write low nibble to databus
	
	// Wait until instruction is accessed on the LCD
	_delay_us(LCD_CMD_TIME);
}

//	+---------------------------------------------------------------+
//	|					LCD character transfer						|
//	+---------------------------------------------------------------+
void lcd_char(char data)
{
	// Select data register
	LCD_PORT_CTRL |= (1<<LCD_RS);
	
	lcd_set((unsigned char)(data));		// Write high nibble to databus
	lcd_set((unsigned char)(data<<4));	// Write low nibble to databus
	
	// Wait until data is accessed on the LCD
	_delay_us(LCD_WRITE_TIME);
}

//	+---------------------------------------------------------------+
//	|						LCD string transfer						|
//	+---------------------------------------------------------------+
void lcd_string(const char *data)
{
	// Wait until \0 escape char is reached
	while(*data != LCD_NULL)
	{
		lcd_char(*data);	// Send character
		data++;				// Increment data
	}
}

//	+---------------------------------------------------------------+
//	|						LCD clear screen						|
//	+---------------------------------------------------------------+
void lcd_clear(void)
{
	lcd_cmd(LCD_CLEAR);			// Clear the LCD screen
	_delay_ms(LCD_CLEAR_TIME);	// Wait LCD is cleared
}

//	+---------------------------------------------------------------+
//	|					LCD cursor to home position					|
//	+---------------------------------------------------------------+
void lcd_home(void)
{
	lcd_cmd(LCD_HOME);			// Return cursor to the start position (0/0)
	_delay_ms(LCD_RETURN_TIME);	// Wait until CURSOR is at home position
}

//	+---------------------------------------------------------------+
//	|						LCD cursor position						|
//	+---------------------------------------------------------------+
void lcd_cursor(unsigned char x, unsigned char y)
{
	// Switch to LCD display line
	switch(y)
	{
		case 0	:	lcd_cmd(LCD_START_ADDR + x);					break;	// Start at display line 0 and column x
		case 1	:	lcd_cmd(LCD_START_ADDR + 0x40 + x);				break;	// Start at display line 1 and column x
		case 2	:	lcd_cmd(LCD_START_ADDR + LCD_COLUMNS * 2 + x);	break;	// Start at display line 2 and column x
		case 3	:	lcd_cmd(LCD_START_ADDR + 0x50 + x);				break;	// Start at display line 3 and column x
		default	:	return;	// Return if no LCD display line is set
	}
}


//	+---------------------------------------------------------------+
//	|					LCD save patterns to RAM					|
//	+---------------------------------------------------------------+
void lcd_pattern(unsigned char address, const unsigned char *data)
{
	// Check if address is greater than max. allowed address
	if(address > LCD_CGADDDR_MAX)
		return;

	lcd_cmd(LCD_CGADDR + (address * 8));	// Setup LCD display CGADDR start address + which character
	
	// Write data to LCD display CGRAM
	for(unsigned char i=0; i < 8; i++)
		lcd_char(data[i]);
	
	lcd_cmd(LCD_DDADDR);					// Setup LCD display DDADDR (HOME position)
}

//	+---------------------------------------------------------------+
//	|					LCD unsigned long to ASCII					|
//	+---------------------------------------------------------------+
void lcd_ul2ascii(const unsigned long data, unsigned char base, unsigned char length)
{
	unsigned char count = 0;	// Internal counter for character length
	char buffer[12];			// ASCII buffer 10 digits + \0 escape character
	
	// If base is empty stop
	if(base == 0)
		return;
	
	// Convert unsigned long to ASCII
	ultoa(data, buffer, base);

	// Check if position adjustment is necessary
	if(length != 0)
	{
		// Loop until \0 escape char is reached
		for(unsigned char i=0; i < sizeof(buffer); i++)
		{
			// Check if buffer data is not equal to \0 escape char
			if(buffer[i] != LCD_NULL)
				count++;	// increment data counter
			else
				break;		// exit loop
		}
		
		// Check if length is greater than count
		if(count < length)
		{
			// Write spaces to LCD display until position adjustment is done
			for(unsigned char i=0; i < (length - count); i++)
				lcd_char(LCD_SPACE);
		}
		// Check if length is lower than count
		else if(count > length)
		{
			// Write \0 escape char to the max. length allowed through position adjustment
			buffer[length] = LCD_NULL;
		}
	}
	
	// Write String to LCD
	lcd_string(buffer);
}

//	+---------------------------------------------------------------+
//	|					LCD signed long to ASCII					|
//	+---------------------------------------------------------------+
void lcd_sl2ascii(const signed long data, unsigned char base, unsigned char length)
{
	unsigned char count = 0;	// Internal counter for character length
	char buffer[12];			// ASCII buffer 10 digits + \0 escape character
	
	// If base is empty stop
	if(base == 0)
		return;
	
	// Convert data to ASCII
	ltoa(data, buffer, base);

	// Check if position adjustment is necessary
	if(length != 0)
	{
		// Loop until \0 escape char is reached
		for(unsigned char i=0; i < sizeof(buffer); i++)
		{
			// Check if buffer data is not equal to \0 escape char
			if(buffer[i] != LCD_NULL)
				count++;	// increment data counter
			else
				break;		// exit loop
		}
		
		// Check if length is greater than count
		if(count < length)
		{
			// Write spaces to LCD display until position adjustment is done
			for(unsigned char i=0; i < (length - count); i++)
				lcd_char(LCD_SPACE);
		}
		// Check if length is lower than count
		else if(count > length)
		{
			// Write \0 escape char to the max. length allowed through position adjustment
			buffer[length] = LCD_NULL;
		}
	}
	
	// Write String to LCD
	lcd_string(buffer);
}

//	+---------------------------------------------------------------+
//	|						LCD double to ASCII						|
//	+---------------------------------------------------------------+
void lcd_d2ascii(const double data, unsigned char length, unsigned char precision)
{
	char buffer[length + precision + 2];	// ASCII buffer (double width) digits + \0 escape character
	
	// If length is empty stop
	if(length == 0)
		return;
	
	// If length + 1 is lower than precision 
	if(length + 1 < precision)
		return;
	
	// Convert double to ASCII
	dtostrf(data, length, precision, (char*)(buffer));
	
	// Write String to LCD
	lcd_string(buffer);
}

