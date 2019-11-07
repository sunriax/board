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
 *       Includes [FLASH][/FLASH] and
 *       [EEPROM][/EEPROM] section
 * -------------------------------------
 */

// System
#define F_CPU 16000000UL

// Push-Button
#define SWITCH_DDR  DDRD
#define SWITCH_PORT PORTD
#define SWITCH_PIN  PIND
#define S0 PD6
#define S1 PD7

#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "uart.h"
#include "loader.h"

static char EEMEM eetitle[] = "Bootloader:\n\rInsert Dump:\n\r";
static char EEMEM textstart[] = "[FLASH]\r\n";
static char EEMEM textstop[] = "[/FLASH]\r\n";
static char EEMEM eestart[] = "[EEPROM]\r\n";
static char EEMEM eestop[] = "[/EEPROM]\r\n";

static char data[5];

static unsigned int page_address;
static unsigned char page_pointer;
static unsigned char page_space[SPM_PAGESIZE];

struct dump_t
{
	unsigned char length;
	unsigned int address;
	unsigned char type;
	unsigned char data[16];
	unsigned char checksum;
} line;


int main(void)
{
	// Function pointer to flash start address
	void (*start)( void ) = 0x0000;
	
	unsigned char temp = GICR;
	// !!! Important, atomic modify write
	GICR = temp | (1<<IVCE);
	GICR = temp | (1<<IVSEL);
	
	SWITCH_DDR |= (1<<S1) | (1<<S0);
	SWITCH_PORT |= (1<<S1) | (1<<S0);
	
	if(!(SWITCH_PIN & (1<<S1) || SWITCH_PIN & (1<<S0)))
	{
		uart_init();
	
		for(unsigned char i=0; i < sizeof(eetitle); i++)
		{
			uart_setchar((char)eeprom_read_byte((unsigned char *)&eetitle[i]));
		}
	
		// Puffer Reset
		memset(page_space, 0xFF, sizeof(page_space));
		
		for (unsigned char mode=0; mode < 2; mode++)
		{
			// Start programming section
			status_t status = Start;
					
			unsigned int checksum;
			
			if(mode == 0)
			{
				for(unsigned char i=0; i < sizeof(textstart); i++)
				{
					uart_setchar((char)eeprom_read_byte((unsigned char *)&textstart[i]));
				}
			}
			else
			{
				for(unsigned char i=0; i < sizeof(eestart); i++)
				{
					uart_setchar((char)eeprom_read_byte((unsigned char *)&eestart[i]));
				}
			}
			
			do 
			{
				char dump = '\0';
				unsigned char left;
		
				switch (status)
				{
					case Length:
				
						uart_xon();
						uart_getstring(data, 2, OFF);
						uart_xoff();
				
						line.length = hex2byte(data);
				
						checksum = line.length;
						status = Address;
				
					break;
			
					case Address:
				
						uart_xon();
						uart_getstring(data, 4, OFF);
						uart_xoff();
					
						line.address = hex2word(data);
				
						if(page_pointer == 0)
						{
							page_address = line.address;
						}
				
						checksum += (line.address>>8) + (0x00FF & line.address);
						status = Type;
				
					break;
			
					case Type:
				
						uart_xon();
						uart_getstring(data, 2, OFF);
						uart_xoff();
				
						line.type = hex2byte(data);
				
						checksum += line.type;
						status = Data;
				
						if(line.length == 0)
							status = Checksum;
				
					break;
			
					case Data:
				
						for (unsigned char i=0; i < line.length; i++)
						{
							uart_xon();
							uart_getstring(data, 2, OFF);
							uart_xoff();
							
							line.data[i] = hex2byte(data);
						
							checksum += line.data[i];
						}
				
						status = Checksum;
				
					break;
			
					case Checksum:
				
						uart_xon();
						uart_getstring(data, 2, OFF);
						uart_xoff();
				
						line.checksum = hex2byte(data);
				
						if((~(checksum) + 1) != line.checksum)
							status = Error;
				
						status = Page;
				
					break;
			
					case Page:
						
						if(mode == 0)
						{
							left = 0;

							for (unsigned char i=0; i < line.length; i++)
							{
								if(page_pointer < SPM_PAGESIZE)
								{
									uart_setchar('.');
									page_space[page_pointer++] = line.data[i];
								}
								else
								{
									left = i;
									break;
								}
							}
							
							// Check if end of data is reached
							if(line.type == 0x01 && line.checksum == 0xFF)
							{
								if(page_pointer > 0)
								page_pointer = SPM_PAGESIZE;
								
								status = Done;
							}
							
							// Reset pointer
							if(page_pointer >= SPM_PAGESIZE)
							{
								uart_setchar('P');
								uart_setchar('\n');
								uart_setchar('\r');
								
								program((unsigned int)(page_address), page_space);
								memset(page_space, 0xFF, sizeof(page_space));
								
								page_pointer = 0;
								
								if(left > 0)
								{
									for (unsigned char i=left; i < line.length; i++)
									{
										uart_setchar('.');
										page_space[page_pointer++] = line.data[i];
									}
									page_address += SPM_PAGESIZE;
								}
							}
							
							if(status != Done)
								status = Start;
						}
						else
						{
							if(line.type == 0x01 && line.checksum == 0xFF)
							{
								status = Done;
								break;
							}
							
							for (unsigned char i=0; i < line.length; i++)
							{
								uart_setchar('.');
								eeprom_write_byte((unsigned char *)(line.address + i), line.data[i]);
							}
							
							uart_setchar('O');
							uart_setchar('\n');
							uart_setchar('\r');
							
							status = Start;
						}
				
					break;
			
					case Error:
			
						// Error
						uart_setchar('!');
						return -1;
			
					break;
			
					default:
			
						uart_xon();
						if(uart_getchar(&dump, OFF))
						{
							if(dump == ':')
							{
								status = Length;		
							}
							else if(dump == 'q')
							{
								status = Done;
							}
							else
							{
								dump = '\0';
							}
						}
					break;
				}
		
			} while (status != Done);
			// End of programming section
		
			if(mode == 0)
			{
				for(unsigned char i=0; i < sizeof(textstop); i++)
				{
					uart_setchar((char)eeprom_read_byte((unsigned char *)&textstop[i]));
				}
			}
			else
			{
				for(unsigned char i=0; i < sizeof(eestop); i++)
				{
					uart_setchar((char)eeprom_read_byte((unsigned char *)&eestop[i]));
				}
			}
		}
		
		_delay_ms(2000);
		
		uart_disable();
	}
	
    temp = GICR;
    GICR = temp | (1<<IVCE);
    GICR = temp & ~(1<<IVSEL);

	// Jump to start of flash
    start();
	
    return 0;
}
