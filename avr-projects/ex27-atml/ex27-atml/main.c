#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD20x4_4bit.h"  // Custom library for LCD

char hour[16];
int a = 23, b = 59, c = 50;
const int t = 1000;

int main(void)
{
	// Initialize the LCD
	lcdinit();

	while (1)
	{
		// Format the time string
		sprintf(hour, "Time=%02u:%02u:%02u", a, b, c);

		// Display the time on the LCD
		lcd_clear();  // Clear the LCD screen
		lcd_print(hour);  // Print the time string
		_delay_ms(t);  // Delay for the specified time

		// Increment the time
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
			a = b = c = 0;
		}
	}

	return 0;
}
