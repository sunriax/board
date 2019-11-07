/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Controller
 * Platform: ATmega8
 * -------------------------------------
 * Name: loader
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for converting bytes
 *       and word and write pages to
 *       flash memory
 * -------------------------------------
 */

#ifndef LOADER_H_
#define LOADER_H_

#define LINE_LENGTH 0x10

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>

typedef enum {
	Done,
	Start,
	Length,
	Address,
	Type,
	Data,
	Checksum,
	Page,
	Error
	
} status_t;

void program(unsigned long page, unsigned char *buffer);
unsigned int hex2word(char *ascii);
unsigned char hex2byte(char *ascii);

#endif /* LOADER_H_ */