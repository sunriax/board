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
 *       reading data from DS1337
 * -------------------------------------
 */

#ifndef DS1337_H_
#define DS1337_H_

#define DS1337_ADDR 0b01101000

#include <stdlib.h>
#include <avr/io.h>
#include <avr/eeprom.h>

#include "../Library/uart.h"
#include "../Library/twi.h"

char* ds1337_get_time();
char* ds1337_get_date();

unsigned char ds1337_set_time(const char *string);
unsigned char ds1337_set_date(const char *string);

unsigned char ds1337_check_value(unsigned char number, char type);

#endif /* DS1337_H_ */