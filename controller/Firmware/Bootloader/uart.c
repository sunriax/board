/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Controller
 * Platform: ATmega8
 * -------------------------------------
 * Name: uart
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

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	#if USE_2X
		UCSRA |= (1<<U2X);											// Double Speed Mode activated
	#else
		UCSRA &= ~(1 << U2X);
	#endif

	unsigned char setreg = ((0x03 & PARITY)<<4) | ((0x01 & (STOPBITS - 1))<<3) | ((0x03 & (DATASIZE - 5))<<1);

	UCSRC = (1<<URSEL) | setreg;
	UCSRB = (1<<RXEN) | (1<<TXEN);	// Activate UART transmitter and receiver

	// Interrupt control
	
	// Receiver interrupt setup
	#ifdef UARTRXCIE
		UCSRB |= (1<<RXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTTXCIE
		UCSRB |= (1<<TXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTUDRIE
		#ifndef UARTTXCIE
			UCSRB |= (1<<UDRIE);
			sei();
		#endif
	#endif

	uart_setchar(0x00);		// Transmit a Dummy Byte
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

void uart_clear(void)
{
	UDR;	// Clear the error flags (by reading UDR)
}

#ifndef UARTTXCIE	// Check if interrupt control is disabled
	#ifndef UARTUDRIE	// Check if interrupt control is disabled

		//	+---------------------------------------------------------------+
		//	|					UART transmit character						|
		//	+---------------------------------------------------------------+
		void uart_setchar(char data)	{
			while(!(UCSRA & (1<<UDRE)));			// Wait until transmit buffer is free
			UDR = data;								// Write data into transmit buffer
		}

		//	+---------------------------------------------------------------+
		//	|					UART transmit string						|
		//	+---------------------------------------------------------------+
		void uart_setstring(char *string, line_t delimiter)	{
			// Repeat until end of string (\0)
			while(*string) {
					uart_setchar(*string);	// Send Character
					
				#ifdef SOFT_CTRL
					char data = '\0';
					
					do 
					{
						uart_getchar(&data, OFF);
					} while (data == XOFF);
				
				#endif
					
				string++;					// Increase string variable
			}
		
			switch (delimiter)
			{
				case NUL		:	uart_setchar(0x00);	break;	// NUL		(NULL)
				case CR		:	uart_setchar(0x0D);	break;	// CR		(CR)
				case LF		:	uart_setchar(0x0A);	break;	// LF		(NULL)
				case CRLF	:	uart_setchar(0x0A);			// LF		(Line Feed)
								uart_setchar(0x0D);	break;	// CR		(Carriage Return)
				case TAB		:	uart_setchar(0x09);	break;	// TAB		(tab)
				case SPACE	:	uart_setchar(0x20);	break;	// SPACE	(space)
				case ESC		:	uart_setchar(0x1B);	break;	// ESC		(escape)
				default	:									break;	// do nothing
			}
		}

		#ifdef SOFT_CTRL
		
			void uart_xon() {
				uart_setchar(XON);
			}
			
			void uart_xoff() {
				uart_setchar(XOFF);
			}
		
		#endif
	#endif
#endif


#ifndef UARTRXCIE	// Check if interrupt control is disabled
	//	+---------------------------------------------------------------+
	//	|					UART receive character						|
	//	+---------------------------------------------------------------+
	unsigned char uart_getchar(char *data, echo_t status)	{
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
		if(status == ON)
			uart_setchar(*data);
			
		return 0xFF;			// When data received
	}

	//	+---------------------------------------------------------------+
	//	|					UART receive string							|
	//	+---------------------------------------------------------------+
	unsigned char uart_getstring(char *string, unsigned char length, echo_t status)	{
		
		// Temporary variable
		char data;
			
		// Run through the string
		for(unsigned char i=0; i < length; i++)
		{
			// Loop until char is received
			unsigned char receive;
				
			do 
			{
				receive = uart_getchar(&data, status);
					
				// If an error occurs abort transaction
				if(receive != 0x00 && receive != 0xFF)
					return receive;
					
			} while (receive != 0xFF);
				
			*string = data;	// Write data to string
			string++;		// Increase string pointer
		}
		return 0xFF;	// if delimiter not found buffer overflow
	}
#endif

