/*LCD.c
 * Author: Mario Wolf
 * Contact: Tronic3D - https://tronic3d.de
 * version: 202409V01
 * description: 16x2 / 20x4 lcd driver header 4-Bit / 8-Bit-Mode
 */

#include "LCD.h"

void LCD_Backlight(uint8_t onoff) {
    if (onoff == 1)
        BACKLIGTPORT |= (1 << BL);
    else
        BACKLIGTPORT &= ~(1 << BL);
}

void LCD_InitLCD() {
    BACKLIGHTDIR |= (1 << BL); //0x01;
    EN_RS_DIR |= (1 << RS) | (1 << EN);
    LCDDIR = 0xFF;

    uint8_t funcset;
    switch (CONF_LCD_BIT) {
        case 0:
            funcset = 0x28; // Functionset 4-Bit Mode
            break;
        case 1:
            funcset = 0x38; //Functionset 8-Bit Mode
            break;
    }

    _delay_ms(20);
    SendCMD(CMD_RESET);
    _delay_ms(5);
    SendCMD(CMD_RESET);
    _delay_us(200);
    SendCMD(CMD_RESET);
    _delay_us(200);
    SendCMD(CMD_HOME);
    SendCMD(funcset);
    SendCMD(CMD_LCD_ON);
    SendCMD(CMD_CLR);
    SendCMD(CMD_ENTRYMODE);
}

void SendCMD(uint8_t cmd) {
    EN_RS_PORT &= ~(1 << RS);
    Send(cmd);
    _delay_ms(2);
}

void Send(uint8_t s) {
    if (CONF_LCD_BIT == 0) {
        LCDPORT = (LCDPORT & 0x0F) | (s & 0xF0);
        EN_RS_PORT |= (1 << EN);
        _delay_us(1);
        EN_RS_PORT &= ~(1 << EN);
        _delay_us(200);

        LCDPORT = (LCDPORT & 0x0F) | (s << 4);
        EN_RS_PORT |= (1 << EN);
        _delay_us(1);
        EN_RS_PORT &= ~(1 << EN);
        _delay_us(200);
    } else {
        LCDPORT = (s);
        EN_RS_PORT |= (1 << EN);
        _delay_us(1);
        EN_RS_PORT &= ~(1 << EN);
        _delay_us(200);
    }
}

void LCD_Print(uint8_t line, uint8_t pos, char *data) {
    LCD_Pos(line, pos);

    for (int i = 0; data[i] != 0; i++) {
        EN_RS_PORT |= (1 << RS);
        Send(data[i]);
    }
}

void LCD_Clear(void) {
    SendCMD(CMD_CLR);
    SendCMD(CMD_HOME);
}

void LCD_Pos(uint8_t line, uint8_t pos) {
    uint8_t adress = 0;
    if (CONF_LINE == 4) {

        switch (line) {
            case 0:
                adress = 0x00;
                break;
            case 1:
                adress = 0x40;
                break;
            case 2:
                adress = 0x14;
                break;
            case 3:
                adress = 0x54;
                break;
        }
    } else {
        switch (line) {
            case 0:
                adress = 0x00;
                break;
            case 1:
                adress = 0x40;
                break;
        }
    }
    SendCMD((CMD_DDRAM | (adress)) + pos);
    _delay_us(50);
}

void LCD_Curs_Off(void) {
    SendCMD(CMD_LCD_ON);
}

void LCD_Curs_On(void) {
    SendCMD(CMD_CURS_ON);
}

void LCD_Diplay_Off(void) {
    SendCMD(CMD_LCD_OFF);
}

void LCD_Curs_Blink(void) {
    SendCMD(CMD_Blink_ON);
}