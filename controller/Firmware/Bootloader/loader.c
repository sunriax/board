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

#include "loader.h"
#include "uart.h"

void program(unsigned long page, unsigned char *buffer)
{
	unsigned char temp = SREG;
	
	cli();
	
	eeprom_busy_wait();

	boot_page_erase(page);
	boot_spm_busy_wait();
	
	for(unsigned char i=0; i < SPM_PAGESIZE; i += 2)
	{
		
		unsigned int word = *buffer++;
		word += ((*buffer++)<<8);
		
		boot_page_fill((page + i), word);
	}
	
	boot_page_write(page);
	boot_spm_busy_wait();
	boot_rww_enable();
	
	sei();
	
	SREG = temp;
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
	
	for(unsigned char i=0; i < 2; i++)
	{	
		if((*ascii >= '0') && (*ascii <= '9'))
		{
			byte += ((*ascii - '0')<<((1 - i) * 4));
		}
		else if((*ascii >= 'A') && (*ascii <= 'F'))
		{
			byte += ((*ascii - 'A' + 10)<<((1 - i) * 4));
		}
		else if((*ascii >= 'a') && (*ascii <= 'f'))
		{
			byte += ((*ascii - 'a' + 10)<<((1 - i) * 4));
		}
		ascii++;
	}
	
	ascii -= 2;
	return byte;
}