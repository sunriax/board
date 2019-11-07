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
 * Text: Example Software for the
 *       Controller. Display Time and
 *       Date from DS1337, temperature
 *       and light intensity. Backlight
 *       of the display is controlled
 *       by the light sensor. Data can
 *       also be catched over uart
 * -------------------------------------
 */

#ifndef MAIN_H_
#define MAIN_H_

// System
#define F_CPU 16000000UL

// EEPROM Data
#define EEI 0

// Display
#define DISPLAY_CTRL_DDR DDRC
#define DISPLAY_CTRL_PORT PORTC
#define CONTRAST   PC2
#define BACKLIGHT  PC3

// Sensor
#define SENSOR_DDR  DDRC
#define SENSOR_PORT PORTC
#define TEMPRATURE PC0
#define INTENSITY  PC1

// DS1337 Interrupts
#define DS1337_DDR  DDRD
#define DS1337_PORT PORTD
#define INTA PD2
#define INTB PD3

// Push-Button
#define SWITCH_DDR  DDRD
#define SWITCH_PORT PORTD
#define SWITCH_PIN  PIND
#define S0 PD6
#define S1 PD7

// Libraries
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "../Library/adc.h"
#include "../Library/lcd.h"
#include "../Library/twi.h"
#include "../Library/uart.h"
#include "../Library/eeprom.h"
#include "../Library/ds1337.h"

#endif /* MAIN_H_ */