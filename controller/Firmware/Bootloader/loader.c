/*
 * loader.c
 *
 * Created: 02.11.2019 11:28:55
 *  Author: sunriax
 */ 

#include "loader.h"

void program(unsigned long page, unsigned char *buffer)
{
	cli();
	
	eeprom_busy_wait();

	boot_page_erase(page);
	boot_spm_busy_wait();
	
	for(unsigned char i=0; i < SPM_PAGESIZE; i += 2)
	{
		unsigned int word = *buffer;
		buffer++;
		
		word = (*buffer<<8);
		buffer++;
		
		boot_page_fill((page + i), word);
	}
	
	boot_page_write(page);
	boot_spm_busy_wait();
	boot_rww_enable();
	
	sei();
}

// 0x010F
unsigned int hex2word(char *ascii)
{
	unsigned int word = 0;
	word |= (hex2byte(ascii)<<8);
	ascii += 2;
	word |= hex2byte(ascii);

	return word;
}

unsigned char hex2byte(char *ascii)
{
	unsigned char byte = 0;
	
	for (unsigned char i=0; i < 2; i++)
	{
		if(ascii[i] >= '0' && ascii[i] <= '9')
		{
			byte += (ascii[i] - '0') * rad(16, (1 - i));
		}
		else if(ascii[i] >= 'A' && ascii[i] <= 'F')
		{
			byte += (ascii[i] - 'A' + 10) * rad(16, (1 - i));
		}
		else if(ascii[i] >= 'a' && ascii[i] <= 'f')
		{
			byte += (ascii[i] - 'a' + 10) * rad(16, (1 - i));
		}
	}
	return byte;
}

unsigned int rad(unsigned char radix, unsigned char position)
{
	unsigned char number = 1;
	
	for (unsigned char i=0; i < position; i++)
	{
		number *= radix;
	}
	
	return number;
}