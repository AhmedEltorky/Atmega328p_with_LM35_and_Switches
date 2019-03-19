#ifndef LCDLIB_
#define LCDLIB_

#define databus_direction DDRD //  LCD data and Control bus Direction Configuration
#define control_direction DDRD

#define databus PORTD     //	LCD databus connected to PORTB
#define control_bus PORTD //	LCD Control bus connected to PORTB

#define RS 0 // Register select pin connected 1st bit(D0) Control bus
//#define rw 1                // Read Write pin connected to 2nd bit(D1) Control bus
#define EN 1 // Enable pin connected to 3rd bit(D2) Control bus

#define _LCD_CLR 0x01

void LCD_Init();
void LCD_CmdWrite(char cmd);
void LCD_DataWrite(char dat);
void lcd_write_string(char *str1);
void lcd_write_int(int val);
void lcd_write_float(int val);

#endif
