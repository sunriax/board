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
 *       communication over UART
 * -------------------------------------
 */

#include "uart.h"

//	+---------------------------------------------------------------+
//	|					UART initialization							|
//	+---------------------------------------------------------------+
void uart_init()	{

	// Baudrate calculation (depends on sample setting)
	#ifdef U2XEN
		UCSRA = (1<<U2X);											// Double Speed Mode activated
		UBRRH = (((unsigned int)(F_CPU / (8 * (BAUD - 1))))>>8);	// Calculate UBRR factor
		UBRRL = (unsigned int)(F_CPU / (8 * (BAUD - 1)));
	#else
		UCSRA = ~(1<<U2X);											// Double Speed Mode deactivated
		UBRRH = (((unsigned int)(F_CPU / (16 * (BAUD - 1))))>>8);	// Calculate UBRR factor
		UBRRL = (unsigned int)(F_CPU / (16 * (BAUD - 1)));
	#endif

	unsigned char setreg;

	// Setup datasize
	#ifdef DATASIZE
		#if DATASIZE > 0x04 && DATASIZE < 0x09
			setreg = (1<<URSEL) | ((0x03 & (DATASIZE - 0x05))<<1);
		#else
			#error "Selected datasize not available"
		#endif
	#else
		#error "No datasize setup"
	#endif
	
	#ifdef PARITY
		#if PARITY < 0x04
			setreg |= ((0x03 & PARITY)<<4);
		#else
			#error "Selected parity mode not available"
		#endif
	#else
		#error "No parity setup"
	#endif
	
	#ifdef STOPBITS
		#if STOPBITS > 0x00 && STOPBITS < 0x03
			setreg |= (1<<URSEL) | ((0x01 & (STOPBITS - 0x01))<<3);
		#else
			#error "Selected stop bits not available"
		#endif
	#else
		#error "No stopbit setup"
	#endif
	
	UCSRC = setreg;
	UCSRB = (1<<RXEN) | (1<<TXEN);	// Activate UART transmitter and receiver

	// Interrupt control
	
	// Receiver interrupt setup
	#ifdef UARTRXCIE
		UCSRB  |= (1<<RXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTTXCIE
		UCSRB  |= (1<<TXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTUDRIE
		#ifndef UARTTXCIE
		UCSRB  |= (1<<UDRIE);
		sei();
		#endif
	#endif

	#ifdef RTS
		UART_DDR |= (1<<RTS);
	#endif

	#ifdef CTS
		UART_DDR &= ~(1<<CTS);
		
		#ifdef CTS_PULLUP
			UART_PORT |= (1<<CTS);
		#endif
	#endif

	uart_rts(1);			// Enable Data receiving
	uart_setchar(0x00);		// Transmit a Dummy Byte
	uart_setchar('\r');
	uart_setchar('\n');
	uart_setchar('\n');
}

//	+---------------------------------------------------------------+
//	|					UART disable function						|
//	+---------------------------------------------------------------+
void uart_disable(void)
{
	// Disable UART
	UCSRB = ~((1<<RXEN) | (1<<TXEN));
	
	// Receiver interrupt setup
	#ifdef UARTRXCIE
		UCSRB  &= ~(1<<RXCIE);
	#endif

	// Transmitter interrupt setup
	#ifdef UARTTXCIE
		UCSRB  &= ~(1<<TXCIE);
	#endif

	// Transmitter interrupt setup
	#ifdef UARTUDRIE
		#ifndef UARTTXCIE
			UCSRB  &= ~(1<<UDRIE);
		#endif
	#endif
}

//	+---------------------------------------------------------------+
//	|					UART reset function							|
//	+---------------------------------------------------------------+
void uart_reset(void)
{
	UDR;	// Clear the error flags (by reading UDR)
}

#ifdef RTS
	void uart_rts(unsigned char status)
	{
		if(status == 0)
		{
			UART_PORT |= (1<<RTS);
		}
		else
		{
			UART_PORT &= ~(1<<RTS);
		}
	}
#endif


#ifdef CTS
	unsigned char uart_cts()
	{
		if(UART_PIN & (1<<CTS))
		{
			return 0x00;
		}
		else
		{
			return 0xFF;
		}
	}
#endif

#ifndef UARTRXCIE	// Check if interrupt control is disabled

//	+---------------------------------------------------------------+
//	|					UART transmit character						|
//	+---------------------------------------------------------------+
void uart_setchar(unsigned char data)	{
	while(!(UCSRA & (1<<UDRE)));			// Wait until transmit buffer is free
		UDR = data;							// Write data into transmit buffer
}

//	+---------------------------------------------------------------+
//	|					UART transmit string						|
//	+---------------------------------------------------------------+
void uart_setstring(char *string)	{
	// Repeat until end of string (\0)
	while(*string) {
		uart_setchar(*string);	// Send Character
		string++;				// Increase string address
	}
}

void uart_setvalue(unsigned char data, unsigned char radix)
{
	char buffer[4];
	
	switch ((radix & 0x0F))
	{
		case 2:		if((radix & 0xF0) > 0)
						uart_setstring("0b");
				
					for (unsigned char i=8; i > 0; i--)
					{
						if(data & (1<<(i-1)))
						{
							uart_setchar('1');
						}
						else
						{
							uart_setchar('0');
						}
					}
					uart_linebreak();
					break;
		
		case 16:	if((radix & 0xF0) > 0)
						uart_setstring("0x");
					
					itoa(data, buffer, 16);
					uart_setstring(buffer);
					uart_linebreak();
					break;
					
		default:	itoa(data, buffer, 10);
					uart_setstring(buffer);
					uart_linebreak();
					break;
	}
}


void uart_linebreak()
{
	uart_setchar('\r');
	uart_setchar('\n');
}

void uart_2linebreak()
{
	uart_linebreak();
	uart_linebreak();
}

void uart_delimiter(unsigned char delimiter)
{
	switch (delimiter)
	{
		case 0	:	uart_setchar(0x00);	break;	// NUL		(NULL)
		case 1	:	uart_setchar(0x0D);	break;	// CR		(CR)
		case 2	:	uart_setchar(0x0A);	break;	// LF		(NULL)
		case 3	:	uart_setchar(0x0A);			// LF		(Line Feed)
					uart_setchar(0x0D);	break;	// CR		(Carriage Return)
		case 4	:	uart_setchar(0x09);	break;	// TAB		(tab)
		case 5	:	uart_setchar(0x20);	break;	// SPACE	(space)
		case 6	:	uart_setchar(0x1B);	break;	// ESC		(escape)
		case 7	:	uart_setchar(0x0C);	break;	// NP		(New Page)
		default	:						break;	// do nothing
	}
}

#endif

#ifndef UARTTXCIE	// Check if interrupt control is disabled
#ifndef UARTUDRIE	// Check if interrupt control is disabled

//	+---------------------------------------------------------------+
//	|					UART receive character						|
//	+---------------------------------------------------------------+
unsigned char uart_getchar(unsigned char *data, unsigned char echo)	{
	// Check data buffer
	if(UCSRA & (1<<RXC))
	{
		if(UCSRA & (1<<FE))
			return 0x01;			// Frame error
		else if(UCSRA & (1<<DOR))
			return 0x02;			// Receiver overflow
		else if(UCSRA & (1<<PE))
			return 0x03;			// Parity error
		
		*data = UDR;		// Write received data to pointer address
	}
	else
	{
		return 0x00;		// When no data received
	}
	
	// Transmit an echo if active
	if(echo != 0x00)
		uart_setchar(*data);
	
	return 0xFF;			// When data received
}

//	+---------------------------------------------------------------+
//	|					UART receive string							|
//	+---------------------------------------------------------------+
unsigned char uart_getstring(unsigned char *string, unsigned char length, unsigned char delimiter, unsigned char echo)	{
	
	// Temporary variable
	unsigned char data;
	
	// Run through the string
	for(unsigned char i=0; i < (length - 1); i++)
	{
		// Loop until char is received
		unsigned char receive;
		
		do
		{
			receive = uart_getchar(&data, echo);
			
			if(receive != 0x00 && receive != 0xFF)
				return receive;
			
		} while (receive != 0xFF);
		
		*string = data;	// Write data to string
		string++;		// Increase string pointer
		
		// If received data is equal delimiter return
		if(data == delimiter)
		{
			// If LF & CR are required
			if(echo == 0xF0)
			{
				uart_setchar('\n');
				uart_setchar('\r');
			}
			
			return 0x00;
		}
	}
	return 0xFF;	// if delimiter not found buffer overflow
}
#endif
#endif