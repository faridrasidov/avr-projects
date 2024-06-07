#ifndef LCD20X4_4BIT_H_
#define LCD20X4_4BIT_H_

#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define LCD_RS 0
#define LCD_EN 1

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);
void lcd_clear();

#endif 