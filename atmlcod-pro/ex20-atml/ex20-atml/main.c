#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	int i = 0;
	char Aseg[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

	DDRA |= (1 << PA0) | (1 << PA6); // Set PA0 and PA6 as outputs
	DDRC = 0xFF; // Set PORTC as output
	DDRD = 0xFF; // Set PORTD as output

	for (;;)
	{
		PORTA |= (1 << PA0); // Turn on green LED
		for (i = 16; i >= 0; i--)
		{
			PORTC = Aseg[i % 10];
			PORTD = Aseg[i / 10];
			_delay_ms(500);
		}

		PORTA &= ~(1 << PA0); // Turn off green LED
		PORTA |= (1 << PA6); // Turn on red LED
		for (i = 14; i >= 0; i--)
		{
			PORTC = Aseg[i % 10];
			PORTD = Aseg[i / 10];
			_delay_ms(500);
		}

		PORTA &= ~(1 << PA6); // Turn off red LED
	}
}
