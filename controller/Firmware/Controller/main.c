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

#include "main.h"

extern unsigned char ee_init;
extern unsigned char ee_intensity;
extern unsigned char ee_contrast;
extern unsigned char ee_offset;
extern unsigned char ee_pattern_degree[];
extern unsigned char ee_firmware[];
extern unsigned char ee_loader[];

static unsigned char init;
static unsigned char offset;
static unsigned char contrast;
static unsigned char intensity;

static unsigned char text[100];

const unsigned char pattern_degree[] =	{	0b01110, 0b01010, 0b01110, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 };
static unsigned int counter;

ISR(TIMER1_OVF_vect)
{
	DISPLAY_CTRL_PORT &= ~((1<<CONTRAST) | (1<<BACKLIGHT));
}

ISR(TIMER1_COMPA_vect)
{
	DISPLAY_CTRL_PORT |= (1<<CONTRAST);
}

ISR(TIMER1_COMPB_vect)
{
	DISPLAY_CTRL_PORT |= (1<<BACKLIGHT);
}


int main(void)
{	
	uart_init();
	uart_rts(1);
	
	// Firmware Version
	uart_set_prom(ee_firmware, 50);
	
	// Bootloader Version
	uart_set_prom(ee_loader, 50);
	
	// Application
	uart_setstring("Debug Application");
	uart_2linebreak();
	
	// Read EEPROM Data
	init = eeprom_read_byte(&ee_init);
	offset = eeprom_read_byte(&ee_offset);
	contrast = eeprom_read_byte(&ee_contrast);
	intensity = eeprom_read_byte(&ee_intensity);
	
	uart_setstring("Init:\t\t");
	uart_setvalue(init, 2);
	
	uart_setstring("Offset:\t\t");
	uart_setvalue(offset, 10);
	
	// Initialize Timer Counter1
	TCCR1A = (1<<WGM10);								// Fast PWM 8 Bit
	TCCR1B = (1<<WGM12) | (1<<CS10);					// No prescaler
	OCR1AL = contrast;
	OCR1BL = intensity;
	TIMSK  = (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1);	// Enable Compare Match A,B and Overflow Interrupt
	sei();												// Enable Interrupt globally
	
	uart_setstring("Contrast:\t");
	uart_setvalue(contrast, 10);

	uart_setstring("Intensity:\t");
	uart_setvalue(intensity, 10);
	
	// Initialize LCD Display
	DISPLAY_CTRL_DDR |= (1<<CONTRAST) | (1<<BACKLIGHT);
	DISPLAY_CTRL_PORT |= (1<<CONTRAST) | (1<<BACKLIGHT);
	
	uart_setstring("Initializing Input Signals");
	uart_linebreak();
	SWITCH_DDR &= ~((1<<S1) | (1<<S0));
	SWITCH_PORT |= (1<<S1) | (1<<S0);
	
	uart_setstring("Initializing Analog/Digital Converter");
	uart_linebreak();
	adc_init();
	
	uart_setstring("Initializing Two Wire Interface");
	uart_linebreak();
	twi_init(1);	// Master Mode
	
	uart_setstring("Initializing Display");
	uart_linebreak();
	lcd_init();
	
	uart_setstring("Initializing Patterns");
	uart_linebreak();
	
	for(unsigned char i=0; i < (unsigned char)(EEPROM_DISPLAY_SYMBOLS); i++)
	{
		// Write Patterns to Display
		eeprom_read_block(text, &ee_pattern_degree[(unsigned char)(i * EEPROM_DISPLAY_SYMBOL)], (unsigned char)(EEPROM_DISPLAY_SYMBOL));
		lcd_pattern((LCD_CGADDR_CHAR0 + i), text);
		
		for (unsigned char j=0; j < (unsigned char)(EEPROM_DISPLAY_SYMBOL); j++)
		{
			uart_setchar('\t');
			uart_setvalue(text[j], 2);
		}
		uart_linebreak();
	}
	uart_linebreak();
	
	//ds1337_set_time("13:15:30");
	//ds1337_set_date("06/06/19");
	
    while (1)
    {
		adc_channel(0);
		signed int temperature = adc_average(10) + offset;
		adc_channel(1);
		unsigned int intensity = adc_average(10);
		
		if(init & (1<<EEI))
		{
			int i = (218 - (float)(intensity)/(float)(2.75));
			
			if(i < 0)
			{
				i = 1;
			}
			
			OCR1BL = (unsigned char)(i);
		}
		
		temperature = (temperature * ((float)(5000)/(float)(1024)) - 500) / 10;
		
		char *ds1337_time = ds1337_get_time();
		char *ds1337_date = ds1337_get_date();
		
		// Display Time from DS1337 and Temperature
		lcd_home();
		lcd_string(ds1337_time);
		
		// Temperature
		lcd_char(' ');
		lcd_sl2ascii(temperature, 10, 3);
		lcd_char(LCD_CGADDR_CHAR0);
		
		lcd_cursor(0, 1);
		lcd_string(ds1337_date);
		
		// Intensity
		lcd_char(' ');
		lcd_ul2ascii(intensity, 10, 4);
		
		if(counter > 50)
		{
			uart_setchar('\r');
			uart_setstring("Stamp: ");
			uart_setstring(ds1337_time);
			uart_setchar('\t');
			uart_setstring(ds1337_date);
			uart_setchar('\t');
			
			static char buffer[4];
			
			itoa(temperature, buffer, 10);
			uart_setstring("Temperature: ");
			uart_setstring(buffer);
			uart_setchar('\t');
			
			itoa(intensity, buffer, 10);
			uart_setstring("Intensity: ");
			uart_setstring(buffer);
			uart_setchar(' ');
			
			counter = 0;
		}
		
		counter++;
    }
}