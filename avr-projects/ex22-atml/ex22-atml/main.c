#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	int i, g = 3, r = 15, t = 1000;

	DDRA = 0xFF; // Set PORTA as output
	DDRB = 0xFF; // Set PORTB as output
	DDRC = 0xFF; // Set PORTC as output
	DDRD = 0xFF; // Set PORTD as output

	for (;;)
	{
		PORTA |= (1 << PA0); // Turn on green LED
		for (i = g; i >= 0; i--)
		{
			PORTB = seg[i];
			_delay_ms(t);
		}

		PORTA &= ~(1 << PA0); // Turn off green LED
		PORTA |= (1 << PA6);  // Turn on red LED
		for (i = r; i >= 0; i--)
		{
			PORTD = 0b00000001;
			PORTC = seg[i % 10];
			_delay_ms(1);
			PORTD = 0b00000010;
			PORTC = seg[i / 10];
			_delay_ms(100);
		}

		PORTA &= ~(1 << PA6); // Turn off red LED
	}
}
