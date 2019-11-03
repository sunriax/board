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

// Datasize
// 5 = 5 bit mode
// 6 = 6 bit mode
// 7 = 7 bit mode
// 8 = 8 bit mode
#ifndef DATASIZE
	#define DATASIZE 8
#endif

// Parity
// 0 = None
// 1 = Reserved
// 2 = Even
// 3 = Odd
#ifndef PARITY
	#define PARITY 0
#endif

// Stopbit
// 1 = 1 Stop bit
// 2 = 2 Stop bit
#ifndef STOPBITS
	#define STOPBITS 1
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

// Definition of flow control characters
#ifndef XON
	#define XON 0x11;
#endif

#ifndef XOFF
	#define XOFF 0x13;
#endif

typedef enum {
	NUL=0,
	CR=1,
	LF=2,
	CRLF=3,
	TAB=4,
	SPACE=5,
	ESC=6,
	NONE=7
} line_t;

typedef enum {
	OFF=0,
	ON=1,
} echo_t;

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

void uart_init(void);
void uart_disable(void);
void uart_clear(void);

#ifndef UARTTXCIE
	#ifndef UARTUDRIE
		void uart_setchar(char data);
		void uart_setstring(char *string, line_t delimiter);
	#endif
#endif

#ifndef UARTRXCIE
	unsigned char uart_getchar(char *data, echo_t status);
	unsigned char uart_getstring(char *string, unsigned char length, echo_t status);
#endif

#endif /* UART_H_ */