/*
 * LCD.h
 *
 * Created: 22.09.2024 12:54:13
 *  Author: wlfma
 */


#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#undef  F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

// ********** Configuration start **********
#define BACKLIGHTDIR DDRB
#define BACKLIGTPORT PORTB
#define LCDDIR DDRD
#define LCDPORT PORTD
#define EN_RS_DIR DDRB                  // DDRB EN / RS
#define EN_RS_PORT PORTB                // Port for EN / RS
#define BL PORTB0                       // PB0 - Back light VCC Pin
#define RS PORTB1                       // PB1
#define EN PORTB2                       // PB2
#define CONF_LCD_BIT    0               // 4-Bit = 0 / 8-Bit = 1
#define CONF_LINE       2               // number of Display lines (2 or 4)
// ********** Configuration end **********

#define CMD_CLR			0x01            // Clear Display
#define CMD_HOME		0x02            // Display Home
#define CMD_RESET       0x03            // Reset display
#define CMD_ENTRYMODE	0x06            // Increment cursor, no Shift
#define CMD_LCD_OFF		0x08            // Display off, Cursor off, Blinking off
#define CMD_FUNC_SET	0x28            // 4-Bit Mode, 2-line Display, 5x8 character Font
#define CMD_DDRAM		0x80            // Display position
#define CMD_LCD_ON		0x0C            // Display on, Cursor off, Blinking off    
#define CMD_CURS_ON		0x0E            // Display on, Cursor on, Blinking off
#define CMD_Blink_ON	0x0F            // Display on, Cursor on, Blinking on

void LCD_Backlight(uint8_t onoff);
void LCD_InitLCD();
void LCD_Pos(uint8_t line, uint8_t pos);
void LCD_Print(uint8_t line, uint8_t pos, char *data);
void LCD_Clear(void);
void LCD_Curs_Off(void);
void LCD_Curs_On(void);
void LCD_Diplay_Off(void);
void LCD_Curs_Blink(void);
void Send(uint8_t s);
void SendCMD(uint8_t cmd);

#endif /* LCD_H_ */