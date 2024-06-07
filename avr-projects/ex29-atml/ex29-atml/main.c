#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD20x4_4bit.h"

// Definitions for button pins
#define UP     PINB0
#define DOWN   PINB1
#define SET    PINB2
#define ALARM  PINB3

char lcd[16];
int i, H = 23, M = 59, S = 55, AH = 12, AM = 0;

void Setting();
void Al_setting();

int main(void)
{
	// Initialize LCD
	lcdinit();
	lcd_clear();

	// Set PORTC as output for alarm indication
	DDRC = 0xFF;

	// Set PORTB lower nibble as input with pull-ups enabled for buttons
	DDRB = 0x00;
	PORTB = 0x0F;

	while(1)
	{
		S++;
		if(S == 60) { S = 0; M++; }
		if(M == 60) { M = 0; H++; }
		if(H == 24) { H = 0; M = 0; S = 0; }

		// Display time on LCD
		lcd_clear();
		sprintf(lcd, "%02u:%02u:%02u", H, M, S);
		lcd_print(lcd);

		// Delay and button handling
		for(i = 0; i < 20; i++)
		{
			_delay_ms(50);
			if(!(PINB & (1 << SET))) Setting();
			if(!(PINB & (1 << ALARM))) Al_setting();
		}

		// Check for alarm condition
		if(H == AH && M == AM)
		PORTC = 0xFF;  // Turn on alarm (all LEDs)
		else
		PORTC = 0x00;  // Turn off alarm
	}
}

void Setting()
{
	char t1, t2;
	lcd_clear();
	lcd_print("Setting Minute: ");
	while(!(PINB & (1 << SET)));
	_delay_ms(250);

	t1 = M;
	while((PINB & (1 << SET)))
	{
		if(!(PINB & (1 << UP))) { t1++; if(t1 > 59) t1 = 0; }
		if(!(PINB & (1 << DOWN))) { t1--; if(t1 > 59) t1 = 59; }
		lcd_gotoxy(0, 1);
		sprintf(lcd, "%02u ", t1);
		lcd_print(lcd);
		_delay_ms(100);
	}

	lcd_clear();
	lcd_print("Setting Hour: ");
	while(!(PINB & (1 << SET)));
	_delay_ms(250);

	t2 = H;
	while((PINB & (1 << SET)))
	{
		if(!(PINB & (1 << UP))) { t2++; if(t2 > 23) t2 = 0; }
		if(!(PINB & (1 << DOWN))) { t2--; if(t2 > 23) t2 = 23; }
		lcd_gotoxy(0, 1);
		sprintf(lcd, "%02u ", t2);
		lcd_print(lcd);
		_delay_ms(100);
	}

	while(!(PINB & (1 << SET)));
	_delay_ms(100);
	lcd_clear();
	lcd_print("Are you sure? ");
	lcd_gotoxy(0, 1);
	lcd_print("UP=yes Down=No");

	while((PINB & 0x03) == 0x03);

	lcd_clear();
	if(!(PINB & (1 << UP)))
	{
		lcd_print("Clock Done");
		H = t2;
		M = t1;
		S = 0;
	}
	if(!(PINB & (1 << DOWN))) lcd_print("Clock Cancel");

	_delay_ms(500);
}

void Al_setting()
{
	char t1, t2;
	lcd_clear();
	lcd_print("Setting Alarm M:");
	while(!(PINB & (1 << ALARM)));
	_delay_ms(250);

	t1 = AM;
	while((PINB & (1 << ALARM)))
	{
		if(!(PINB & (1 << UP))) { t1++; if(t1 > 59) t1 = 0; }
		if(!(PINB & (1 << DOWN))) { t1--; if(t1 > 59) t1 = 59; }
		lcd_gotoxy(0, 1);
		sprintf(lcd, "%02u ", t1);
		lcd_print(lcd);
		_delay_ms(100);
	}

	lcd_clear();
	lcd_print("Setting Alarm H:");
	while(!(PINB & (1 << ALARM)));
	_delay_ms(250);

	t2 = AH;
	while((PINB & (1 << ALARM)))
	{
		if(!(PINB & (1 << UP))) { t2++; if(t2 > 23) t2 = 0; }
		if(!(PINB & (1 << DOWN))) { t2--; if(t2 > 23) t2 = 23; }
		lcd_gotoxy(0, 1);
		sprintf(lcd, "%02u ", t2);
		lcd_print(lcd);
		_delay_ms(100);
	}

	while(!(PINB & (1 << ALARM)));
	_delay_ms(100);
	lcd_clear();
	lcd_print("Are you sure?");
	lcd_gotoxy(0, 1);
	lcd_print("UP=yes Down=No");

	while((PINB & 0x03) == 0x03);

	lcd_clear();
	if(!(PINB & (1 << UP)))
	{
		lcd_print("Alarm Done");
		AH = t2;
		AM = t1;
	}
	if(!(PINB & (1 << DOWN))) lcd_print("Alarm Cancel");

	_delay_ms(500);
}
