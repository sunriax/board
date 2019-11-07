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
 *       reading data from A/D Converter
 * -------------------------------------
 */

#include "adc.h"

//	+---------------------------------------------------------------+
//	|					ADC initialization							|
//	+---------------------------------------------------------------+
void adc_init(void)
{
	// Setup ADC parameters
	ADMUX = (((0x03 & ADC_REF)<<6) | ((0x01 & ADC_DATA_SHIFT)<<5));
	
	// Setup ADC clock prescaler
	// F_ADC = F_CPU / ADC_PRESCALER
	ADCSRA = ((0x07 & ADC_PRESCALER));
	
	// Setup ADC permanent transformation and trigger source
	#if ADC_MODE == 0x01
		ADCSRA |= (1<<ADEN) | (1<<ADSC);
	#endif
	
	// Check if ADC interrupt handler is active
	#ifdef ADC_ADIE
		ADCSRA |= (1<<ADIE);	// Enable ADC interrupt
		sei();					// Enable global interrupt
	#endif
}

//	+---------------------------------------------------------------+
//	|					ADC disable function						|
//	+---------------------------------------------------------------+
void adc_disable(void)
{
	ADCSRA &= ~(1<<ADEN);	// Disable ADC
}

//	+---------------------------------------------------------------+
//	|					ADC channel selection						|
//	+---------------------------------------------------------------+
void adc_channel(unsigned char channel)
{
	// On Controller only channel 0 and 1 are available!
	ADMUX = (ADMUX & ~(0x0F)) | (0x01 & channel);	// Select ADC Channel
}

#ifndef ADC_ADIE

//	+---------------------------------------------------------------+
//	|					ADC read value								|
//	+---------------------------------------------------------------+
unsigned int adc_read(void)
{
	#ifdef ADC_NOISE_REDUCTION
	// Enter ADC noise reduction mode (stop the CPU)
		MCUCR &= ~((1<<SM2) | (1<<SM1));
		MCUCR |= (1<<SM0);
	#endif
	
	#if ADC_MODE == 0x01
	
	// Wait until ADC interrupt flag is zero
	while(!(ADCSRA & (1<<ADIF)))
		asm volatile("NOP");
	
	unsigned char ADC_LOW = ADCL;	// Save ADC LOW value to variable
	unsigned char ADC_HIGH = ADCH;	// Save ADC HIGH value to variable
	
	ADCSRA |= (1<<ADIF);			// Reset ADC interrupt flag
	
	// Return ADC high + low value
	return ((ADC_HIGH<<8) | ADC_LOW);
	
	#else
	
	// Start single conversion
	ADCSRA |= (1<<ADEN) | (1<<ADSC);
	
	// Wait until conversion is in progress
	while(ADCSRA & (1<<ADSC))
		asm volatile("NOP");
	
	unsigned char ADC_LOW = ADCL;	// Save ADC LOW value to variable
	unsigned char ADC_HIGH = ADCH;	// Save ADC HIGH value to variable
	
	// Return ADC high + low value
	return ((ADC_HIGH<<8) | ADC_LOW);
	
	#endif
	
	#ifdef ADC_NOISE_REDUCTION
		// Exit ADC noise reduction mode (start the CPU)
		MCUCR &= ~((1<<SM2) | (1<<SM1)) | (1<<SM0));
	#endif
	
}

//	+---------------------------------------------------------------+
//	|					ADC read average from values				|
//	+---------------------------------------------------------------+
unsigned int adc_average(unsigned char size)
{
	double average = 0;	// average buffer
	
	// Build average
	for(unsigned char i=0; i < size; i++)
		average += (adc_read() / size);		// Divide ADC value through size of buffer
	
	// Return double as unsigned int
	return average;
}

#endif