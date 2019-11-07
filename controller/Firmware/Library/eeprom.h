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

#ifndef EEPROM_H_
#define EEPROM_H_

#define EEPROM_DISPLAY_SYMBOL 8
#define EEPROM_DISPLAY_SYMBOLS 8
#define EEPROM_UART_BUFFER 100

#include <avr/io.h>
#include <avr/eeprom.h>

#include "../Library/uart.h"

void uart_set_prom(unsigned char *pointer, unsigned char length);

#endif /* EEPROM_H_ */