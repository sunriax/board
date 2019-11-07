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
 *       reading data from EEPROM
 * -------------------------------------
 */

#include "eeprom.h"

const unsigned char EEMEM ee_init = 0b00000001;
const unsigned char EEMEM ee_intensity = 1;
const unsigned char EEMEM ee_contrast = 220;
const unsigned char EEMEM ee_offset = 0;
const unsigned char EEMEM ee_pattern_degree[(8 * EEPROM_DISPLAY_SYMBOLS)] = { 0b00001110, 0b00001010, 0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 };
const unsigned char EEMEM ee_firmware[] = "Firmware Version 1.0\r\n";
const unsigned char EEMEM ee_loader[] = "Loader Version 1.0\r\n";

void uart_set_prom(unsigned char *pointer, unsigned char length)
{
	if((length > 0) && (length < EEPROM_UART_BUFFER))
	{
		char buffer[length];
		eeprom_read_block(buffer, pointer, length);
		uart_setstring(buffer);
	}
}
