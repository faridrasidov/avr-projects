#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD20x4_4bit.h"  // Include your custom LCD library header file

char saat[20];
char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};

int a = 0, b = 0, c = 0, hob = 0;
const int t = 1000;
uint8_t F1 = 0, F2 = 0, F3 = 0, F4 = 0;

int main(void)
{
	// Initialize the LCD
	lcdinit();

	// Set DDR registers
	DDRC = 0xFF;
	DDRB = 0xFF;
	DDRD = 0b11110000;
	PORTD = 0b00001111;
	PORTC = 0xFF;

	while (1)
	{
		if (!(PIND & (1 << PD3)))
		{
			PORTB = seg[b % 10];
			PORTC = seg[b / 10];

			if ((PIND & (1 << PD2)) && !F1)
			{
				F1 = 1;
				b++;
			}
			if (!(PIND & (1 << PD2))) F1 = 0;
			if (b >= 60) b = 0;

			if ((PIND & (1 << PD1)) && !F3)
			{
				F3 = 1;
				b--;
			}
			if (!(PIND & (1 << PD1))) F3 = 0;
			if (b < 0) b = 60;
		}

		if (PIND & (1 << PD3))
		{
			PORTB = seg[a % 10];
			PORTC = seg[a / 10];

			if ((PIND & (1 << PD2)) && !F2)
			{
				F2 = 1;
				a++;
			}
			if (!(PIND & (1 << PD2))) F2 = 0;
			if (a >= 24) a = 0;

			if ((PIND & (1 << PD1)) && !F4)
			{
				F4 = 1;
				a--;
			}
			if (!(PIND & (1 << PD1))) F4 = 0;
			if (a < 0) a = 24;
		}

		if (!(PIND & (1 << PD0)))
		{
			while (1)
			{
				sprintf(saat, "%d:%d:%d", a, b, c);
				lcd_clear();  // Clear the LCD screen
				lcd_print(saat);  // Print the formatted time string
				_delay_ms(t);  // Delay for the specified time

				c++;
				if (c == 60)
				{
					c = 0;
					b++;
				}
				if (b == 60)
				{
					b = 0;
					a++;
				}
				if (a == 24)
				{
					a = b = 0;
				}

				if ((a % 2) == 0) PORTD |= (1 << PD4);
				else PORTD &= ~(1 << PD4);

				if ((a % 3) == 0) PORTD |= (1 << PD5);
				else PORTD &= ~(1 << PD5);

				if ((a % 5) == 0) PORTD |= (1 << PD6);
				else PORTD &= ~(1 << PD6);

				if ((a % 8) == 0) PORTD |= (1 << PD7);
				else PORTD &= ~(1 << PD7);

				if ((c % 5) == 0)
				{
					PORTB = seg[b % 10];
					PORTC = seg[b / 10];
					hob++;
				}
				else
				{
					PORTB = seg[c % 10];
					PORTC = seg[c / 10];
				}

				if ((c % 5) == 0 && hob == 2)
				{
					PORTB = seg[a % 10];
					PORTC = seg[a / 10];
					hob = 0;
				}
			}
		}
	}

	return 0;
}
