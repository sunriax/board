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

#ifndef UART_H_
#define UART_H_

// Definition of SYSTEM parameters

#ifndef F_CPU	// Systemclock
	#define F_CPU 16000000UL
#endif

// Definition of UART parameters

#ifndef BAUD	// UART baudrate
	#define BAUD 9600UL
#endif

#ifndef DATASIZE	//UART datasize
	#define DATASIZE 0x08	// 5 Bit = 0x05
							// 6 Bit = 0x06
							// 7 Bit = 0x07
							// 8 Bit = 0x08
#endif

#ifndef PARITY
	#define PARITY 0x00		// 0x00 = None
							// 0x01 = Reserved
							// 0x02 = Even Parity
							// 0x03 = Odd Parity
#endif

#ifndef STOPBITS
	#define STOPBITS 0x01	// 0x01 = 1 Stopbit
							// 0x02 = 2 Stopbit
#endif

#ifndef U2XEN	// Sample rate (defined = 8 Samples/Bit | undefined = 16 Samples/Bit)
	#define U2XEN
#endif

// Definition of UART processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! Interrupts are not included in this library !
// ! If interrupts are used, disable the polling !
// ! by uncommenting the next lines              !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#ifndef UARTRXCIE	// Receiver Interrupt based processing
//	#define UARTRXCIE
//#endif

//#ifndef UARTTXCIE	// Transmitter Interrupt based processing
//	#define UARTTXCIE
//#endif

//#ifndef UARTUDRIE	// Transmitter Interrupt based processing
//	#ifndef UARTTXCIE
//		#define UARTUDRIE
//	#else
//		#undef UARTUDRIE
//	#endif
//#endif

// UART
#ifndef UART_DDR
	#define UART_DDR  DDRD
#endif

#ifndef UART_PORT
	#define UART_PORT PORTD
#endif

#ifndef UART_PIN
	#define UART_PIN PIND
#endif

#ifndef CTS
	#define CTS PD4
	
	#ifndef CTS_PULLUP
		#define CTS_PULLUP
	#endif
#endif

#ifndef RTS
	#define RTS PD5
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(void);
void uart_disable(void);
void uart_reset(void);

#ifdef RTS
	void uart_rts(unsigned char status);
#endif

#ifdef CTS
	unsigned char uart_cts(void);
#endif

#ifndef UARTTXCIE
	#ifndef UARTUDRIE
		void uart_setchar(unsigned char data);
		void uart_setstring(char *string);
		void uart_setvalue(unsigned char data, unsigned char radix);
		
		void uart_linebreak(void);
		void uart_2linebreak(void);
		void uart_delimiter(unsigned char delimiter);
		
	#endif
#endif

#ifndef UARTRXCIE
	unsigned char uart_getchar(unsigned char *data, unsigned char echo);
	unsigned char uart_getstring(unsigned char *string, unsigned char length, unsigned char delimiter, unsigned char echo);
#endif

#endif /* UART_H_ */