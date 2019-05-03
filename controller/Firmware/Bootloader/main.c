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

#include <avr/io.h>


int main(void)
{
    while (1) 
    {
    }
}

