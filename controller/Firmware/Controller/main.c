/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Controller
 * Platform: ATmega8
 * -------------------------------------
 * Name: CONTROLLER
 * Ver.: 1.0 Release
 * Type: Executeable
 * Text: Application for controller
 * -------------------------------------
 */

// System
#define F_CPU 16000000UL

// Display
#define DB7 PB0
#define DB6 PB1
#define DB5 PB2
#define DB4 PB3

#define E   PB4
#define RS  PB5

#include <avr/io.h>

// Sensor
#define TEMPRATURE PC0
#define INTENSITY  PC1

// Actor
#define CONTRAST   PC2
#define BACKLIGHT  PC3

// TWI
#define SDA  PC4
#define SCL  PC5
#define INTA PD2
#define INTB PD3

// UART
#define RXD PD0
#define TXD PD1
#define CTS PD4
#define RTS PD5

// Push-Button
#define S0 PD6
#define S1 PD7

int main(void)
{
    while (1) 
    {
    }
}

