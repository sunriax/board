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

#include "ds1337.h"

char* ds1337_get_time()
{
	static char time[] = "00:00:00";
	
	unsigned char second = TWI_ACK;
	unsigned char minute = TWI_ACK;
	unsigned char hour = TWI_NACK;
	
	twi_start();
	twi_address(DS1337_ADDR, TWI_WRITE);
	twi_set(0x00);
	twi_start();
	twi_address(DS1337_ADDR, TWI_READ);
	twi_get(&second);
	twi_get(&minute);
	twi_get(&hour);
	twi_stop();
	
	time[0] = ((hour & 0x30)>>4) + '0';
	time[1] = (hour & 0x0F) + '0';
	time[2] = ':';
	time[3] = ((minute & 0x70)>>4) + '0';
	time[4] = (minute & 0x0F) + '0';
	time[5] = ':';
	time[6] = ((second & 0xF0)>>4) + '0';
	time[7] = (second & 0x0F) + '0';
	time[8] = '\0';
	
	return time;
}

char* ds1337_get_date()
{
	static char date[] = "00/00/00";

	unsigned char day = TWI_ACK;
	unsigned char month = TWI_ACK;
	unsigned char year = TWI_NACK;

	twi_start();
	twi_address(DS1337_ADDR, TWI_WRITE);
	twi_set(0x04);
	twi_start();
	twi_address(DS1337_ADDR, TWI_READ);
	twi_get(&day);
	twi_get(&month);
	twi_get(&year);
	twi_stop();
	
	date[0] = ((day & 0x30)>>4) + '0';
	date[1] = (day & 0x0F) + '0';
	date[2] = '/';
	date[3] = ((month & 0x10)>>4) + '0';
	date[4] = (month & 0x0F) + '0';
	date[5] = '/';
	date[6] = ((year & 0xF0)>>4) + '0';
	date[7] = (year & 0x0F) + '0';
	date[8] = '\0';

	return date;
}

unsigned char ds1337_set_time(const char *string)
{	
	unsigned char hour = ((string[0] - '0')<<4);
	hour |= ((string[1] - '0') & 0x0F);
	
	unsigned char minute = ((string[3] - '0')<<4);
	minute |= ((string[4] - '0') & 0x0F);
	
	unsigned char second = ((string[6] - '0')<<4);
	second |= ((string[7] - '0') & 0x0F);
	
	if( ds1337_check_value(hour,	'h') ||
		ds1337_check_value(minute,	'm') ||
		ds1337_check_value(second,	's') )
			return 0xF0;
	
	twi_start();
	twi_address(DS1337_ADDR, TWI_WRITE);
	twi_set(0x00);
	twi_set(second);
	twi_set(minute);
	twi_set(hour);
	twi_stop();
	
	return 0x00;
}

unsigned char ds1337_set_date(const char *string)
{
	unsigned char day = ((string[0] - '0')<<4);
	day |= ((string[1] - '0') & 0x0F);
	
	unsigned char month = ((string[0] - '0')<<4);
	month |= ((string[1] - '0') & 0x0F);
	
	unsigned char year = ((string[0] - '0')<<4);
	year |= ((string[1] - '0') & 0x0F);
	
	if( ds1337_check_value(day,		'D') ||
		ds1337_check_value(month,	'M') ||
		ds1337_check_value(year,	'Y') )
			return 0xF0;
	
	twi_start();
	twi_address(DS1337_ADDR, TWI_WRITE);
	twi_set(0x04);
	twi_set(day);
	twi_set(month);
	twi_set(year);
	twi_stop();
	
	return 0x00;
}

unsigned char ds1337_check_value(unsigned char number, char type)
{
	switch (type)
	{
		case 'D':	if(number > 0x31 || (0x0F & number) > 0x09)
						return 0xFF;
					break;
					
		case 'M':	if(number > 0x12 || (0x0F & number) > 0x09)
						return 0xFF;
					break;
					
		case 'Y':	if(number > 0x99 || (0x0F & number) > 0x09)
						return 0xFF;
					break;
		
		case 'h':	if(number > 0x23 || (0x0F & number) > 0x09)
						return 0xFF;
					break;
					
		default:	if(number > 0x59 || (0x0F & number) > 0x09)
						return 0xFF;
					break;
	}
	return 0x00;
}