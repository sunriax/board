/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Controller
 * Platform: ATmega8
 * -------------------------------------
 * Name: BOOTLOADER
 * Ver.: 1.0 Release
 * Type: Executeable
 * Text: Bootloader for controller
 * -------------------------------------
 */

// System
#define F_CPU 16000000UL

// UART
#define RXD PD0
#define TXD PD1
#define CTS PD4
#define RTS PD5

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/boot.h>

#include "uart.h"
#include "loader.h"

static unsigned char line_pointer;
static unsigned char page_pointer;
static unsigned char page_space[SPM_PAGESIZE];

static char EEMEM eetitle[] = "SUNriaX Engineering!\r\nLoader v1.0";
static char EEMEM eeprogram[] = "Program (Insert HEX dump):\r\n";
static char EEMEM eestart[] = "[START]\r\n";
static char EEMEM eestop[] = "[END]\r\n";

struct dump_t
{
	unsigned char length;
	unsigned int address;
	unsigned char type;
	unsigned char *data;
	unsigned char checksum;
} line;


int main(void)
{
	// Function pointer to flash start address
	void (*start)( void ) = 0x0000;
	
	//unsigned char sregtemp = SREG;
	cli();
	
	unsigned char temp = MCUCR;
	// !!! Important, atomic modify write
	GICR = temp | (1<<IVCE);
	GICR = temp | (1<<IVSEL);
	
	//SREG = sregtemp;	
	sei();
	
	uart_init();
	
	char *data;
	
	data = (char *)calloc(sizeof(eetitle), sizeof(char));
	eeprom_read_block(data, eetitle, sizeof(eetitle));
	uart_setstring(data, CRLF);
	free(data);

	data = (char *)calloc(sizeof(eeprogram), sizeof(char));
	eeprom_read_block(data, eeprogram, sizeof(eeprogram));
	uart_setstring(data, CRLF);
	free(data);

	data = (char *)calloc(sizeof(eestart), sizeof(char));
	eeprom_read_block(data, eestart, sizeof(eestart));
	uart_setstring(data, CRLF);
	free(data);

	// start Programming Section
	status_t status = Start;
	
	unsigned int checksum;
	
    do 
    {
		char dump = '\0';
		
		switch (status)
		{
			case Length:
				
				data = (char *)calloc(2, sizeof(char));
				uart_getstring(data, 2, ON);
				line.length = hex2byte(data);
				free(data);
				
				checksum = line.length;
				status = Address;
			break;
			
			case Address:
			
				data = (char *)calloc(4, sizeof(char));
				uart_getstring(data, 4, ON);
				line.address = hex2word(data);
				free(data);
				
				checksum += (line.address>>8) + (0x00FF & line.address);
				status = Type;
			break;
			
			case Type:
			
				data = (char *)calloc(2, sizeof(char));
				uart_getstring(data, 2, ON);
				line.type = hex2byte(data);
				free(data);
				
				checksum += line.type;
				status = Data;
				
				if(line.length == 0)
					status = Checksum;
			break;
			
			case Data:
			
				data = (char *)calloc((line.length * 2), sizeof(char));
				uart_getstring(data, (line.length * 2), ON);
				
				line.data = (unsigned char *)calloc(line.length, sizeof(unsigned char));
				
				for (unsigned char i=0; i < line.length; i++)
				{
					line.data[i] = hex2byte(&data[(2 * i)]);
					checksum += line.data[i];
				}
				
				free(data);
				
				status = Checksum;
			break;
			
			case Checksum:
				
				data = (char *)calloc(2, sizeof(char));
				uart_getstring(data, 2, ON);
				line.checksum = hex2byte(data);
				free(data);
				
				if((~(checksum) + 1) != line.checksum)
					status = Error;
				
				status = Page;
			break;
			
			case Page:
			
				// Check if end of data is reached
				if(line.type == 0x01 && line.checksum == 0xFF)
					status = Done;
				
				do 
				{
					if(page_pointer < SPM_PAGESIZE)
					{
						
					}
					
				} while (1);
			
			break;
			
			case Error:
			
				// Error
			
			break;
			
			default:
				if(uart_getchar(&dump, ON))
				{
					if(dump == ':')
					{
						status = Length;
					}
				}
			break;
		}
		
    } while (1);
	// End of programming section
	
	
	data = (char *)calloc(sizeof(eestop), sizeof(char));
	eeprom_read_block(data, eestop, sizeof(eestop));
	uart_setstring(data, CRLF);
	free(data);
	
	_delay_ms(1000);
	
	uart_disable();
    
	cli();
	
    temp = MCUCR;
    GICR = temp | (1<<IVCE);
    GICR = temp | (1<<IVSEL);

	// Jump to start of flash
    start();
	
    return 0;
}
