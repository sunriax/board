/*
 * loader.h
 *
 * Created: 02.11.2019 11:28:46
 *  Author: sunriax
 */ 


#ifndef LOADER_H_
#define LOADER_H_

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
unsigned int rad(unsigned char radix, unsigned char position);

#endif /* LOADER_H_ */