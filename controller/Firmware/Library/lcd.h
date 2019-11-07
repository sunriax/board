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

#ifndef LCD_H_
#define LCD_H_

// Definition of SYSTEM parameters

#ifndef F_CPU			// Systemclock
	#define F_CPU 16000000UL
#endif

// Definition of LCD parameters

#ifndef F_LCD			// LCD enable clock
	#define F_LCD 100000UL
#endif

// LCD control directives
#ifndef LCD_DDR_CTRL	// LCD control direction register
	#define LCD_DDR_CTRL DDRB
#endif

#ifndef LCD_PORT_CTRL	// LCD control port register
	#define LCD_PORT_CTRL PORTB
#endif

#ifndef LCD_RS			// LCD register select
	#define LCD_RS PB5
#endif

#ifndef LCD_E			// LCD start data read/write
	#define LCD_E PB4
#endif

// LCD data directives
#ifndef LCD_DDR_DATA	// LCD data direction register
	#define LCD_DDR_DATA DDRB
#endif

#ifndef LCD_PORT_DATA	// LCD control direction register
	#define LCD_PORT_DATA PORTB
#endif

#ifndef LCD_DB0			// LCD data bit 0 (LCD display bit 4)
	#define LCD_DB0 PB3
#endif

#ifndef LCD_DB1			// LCD data bit 1 (LCD display bit 5)
	#define LCD_DB1 PB2
#endif

#ifndef LCD_DB2			// LCD data bit 2 (LCD display bit 6)
	#define LCD_DB2 PB1
#endif

#ifndef LCD_DB3		// LCD data bit 3 (LCD display bit 7)
	#define LCD_DB3 PB0
#endif

// LCD display parameters
#ifndef LCD_COLUMNS		// LCD display columns/row (1 - 20)
	#define LCD_COLUMNS 16
#endif

#ifndef LCD_START_ADDR	// Start position of the LCD RAM
	#define LCD_START_ADDR 0x80
#endif

// LCD time/instruction codes (!!! Do not change !!!)

// LCD time directives
#ifndef LCD_STARTUP_TIME	// LCD startup time in ms
	#define LCD_STARTUP_TIME 15
#endif

#ifndef LCD_CLEAR_TIME	// LCD startup time in ms
	#define LCD_CLEAR_TIME 2
#endif

#ifndef LCD_RETURN_TIME	// LCD return home time in ms
	#define LCD_RETURN_TIME 2
#endif

#ifndef LCD_ENTRY_TIME	// LCD entry mode time in us
	#define LCD_ENTRY_TIME 42
#endif

// #ifndef LCD_DISPLAY_TIME	// LCD display time in us
//	#define LCD_DISPLAY_TIME 42
// #endif

// #ifndef LCD_SHIFT_TIME	// LCD shift time in us
// 	#define LCD_SHIFT_TIME 42
// #endif

#ifndef LCD_FUNCTION_TIME	// LCD function time in us
	#define LCD_FUNCTION_TIME 42
#endif

#ifndef LCD_WRITE_TIME		// LCD WRITE time in us
	#define LCD_WRITE_TIME 42
#endif

#ifndef LCD_CMD_TIME		// LCD COMMAND time in us
	#define LCD_CMD_TIME 42
#endif

// LCD instruction directives
#ifndef LCD_CLEAR			// LCD clear display instruction
	#define LCD_CLEAR           0b00000001
#endif

#ifndef LCD_HOME			// LCD return home instruction
	#define LCD_HOME            0b00000010
#endif

#ifndef LCD_ENTRY			// LCD entry mode set instruction
	#define LCD_ENTRY           0b00000100
	#define LCD_ENTRY_INCREMENT 0b00000010
	#define LCD_ENTRY_SHIFT     0b00000001
#endif

#ifndef LCD_DISPLAY			// LCD display set instruction
	#define LCD_DISPLAY         0b00001000
	#define LCD_DISPLAY_ON      0b00000100
	#define LCD_CURSOR_ON       0b00000010
	#define LCD_BLINK_ON        0b00000001
#endif

#ifndef LCD_SHIFT			// LCD shift instruction
	#define LCD_SHIFT           0b00010000
	#define LCD_SHIFT_DISPLAY   0b00001000
	#define LCD_SHIFT_RIGHT     0b00000100
#endif

#ifndef LCD_FUNCTION		// LCD function instruction
	#define LCD_FUNCTION        0b00100000
	#define LCD_FUNCTION_8BIT   0b00010000
	#define LCD_FUNCTION_2LINE  0b00001000
	#define LCD_FUNCTION_5x10	0b00000100
#endif

#ifndef LCD_CGADDR			// LCD CGADDR instruction
	#define LCD_CGADDR          0b01000000
	#define LCD_CGADDR_CHAR0    0b00000000
	#define LCD_CGADDR_CHAR1    0b00000001
	#define LCD_CGADDR_CHAR2    0b00000010
	#define LCD_CGADDR_CHAR3    0b00000011
	#define LCD_CGADDR_CHAR4    0b00000100
	#define LCD_CGADDR_CHAR5    0b00000101
	#define LCD_CGADDR_CHAR6    0b00000110
	#define LCD_CGADDR_CHAR7    0b00000111
	#define LCD_CGADDDR_MAX     7
#endif

#ifndef LCD_DDADDR			// LCD DDADDR instruction
	#define LCD_DDADDR          0b10000000
#endif

#ifndef LCD_SPACE			// Space character
	#define LCD_SPACE 0x20
#endif

#ifndef LCD_NULL			// End character
	#define LCD_NULL 0x00
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

void lcd_init(void);
void lcd_disable(void);
void lcd_clock(void);
void lcd_set(unsigned char data);
void lcd_cmd(unsigned char instruction);
void lcd_char(char data);
void lcd_string(const char *data);
void lcd_clear(void);
void lcd_home(void);
void lcd_cursor(unsigned char x, unsigned char y);
void lcd_pattern(unsigned char address, const unsigned char *data);
void lcd_ul2ascii(unsigned long data, unsigned char base, unsigned char length);
void lcd_sl2ascii(const signed long data, unsigned char base, unsigned char length);
void lcd_d2ascii(const double data, unsigned char length, unsigned char precision);

#endif /* LCD_H_ */