/*
 * Atmega328p_with_LM35_and_Switches.c
 *
 * Created: 3/19/19 2:39:56 PM
 * Author : Ahmed El-Torky
 */

#define F_CPU 1000000ul

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd/lcdlib.h"

int main(void)
{
	// LCD initialization
	LCD_Init();
	// ADC initialization
	ADMUX |= (1 << REFS0);												// select AVCC as volt reference
	ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3); // select the ADC0 from multiplexer
	ADCSRA |= (1 << ADPS2);												// set the ADC prescaler to 16 ==> ADC feq. = 1M / 16 = 62.5 KHz
	ADCSRA |= (1 << ADIE);												// enable ADC interrupt
	ADCSRA |= (1 << ADEN);												// enable the ADC
	// pin change interrupt initial
	PCICR |= (1 << PCIE0);									 // set the pin change interrupt for group 0
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2); // set the PCINT for pin 0, 1 and 2

	sei();				   // set global interrupt
	ADCSRA |= (1 << ADSC); // start the ADC conversion

	while (1)
	{
	}
}

ISR(PCINT0_vect)
{
	// this code doesn't support multiple pressed switches
	uint8_t read = PINB;							// read port B
	read &= (1 << PINB0 | 1 << PINB1 | 1 << PINB2); // masking the read value
	switch (read)
	{
		case 1: // first switch pressed
			LCD_CmdWrite(_LCD_CLR);
			lcd_write_string("01");
			_delay_ms(500);
			LCD_CmdWrite(_LCD_CLR);
			break;
		case 2: // second switch pressed
			LCD_CmdWrite(_LCD_CLR);
			lcd_write_string("02");
			_delay_ms(500);
			LCD_CmdWrite(_LCD_CLR);
			break;
		case 4: // third switch pressed
			LCD_CmdWrite(_LCD_CLR);
			lcd_write_string("03");
			_delay_ms(500);
			LCD_CmdWrite(_LCD_CLR);
			break;
		default:
			break;
	}
}

ISR(ADC_vect)
{
	sei(); // set global interrupt to enable interrupt nesting
	uint16_t adcValue = ADCW;
	float vin = (float)adcValue * 5 / 1024; // Vin = ADC * Vref / (2^n) ==> Vin = ADC * 5 / 1024 // the result will be in volt
	vin *= 1000;							// to convert it from volt to mv
	uint16_t temp = vin / 10;				// each 10 mv represent 1 Celsius degree
	LCD_CmdWrite(_LCD_CLR);					// clear the LCD
	lcd_write_string("temp = ");
	lcd_write_int(temp);
	_delay_ms(500);
	ADCSRA |= (1 << ADSC); // start ADC next conversion
}
