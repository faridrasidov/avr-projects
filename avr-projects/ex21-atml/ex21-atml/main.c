#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	int i, g = 14, r = 12, t = 1000;
	char Cseg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F, 0xF7, 0xFC, 0xB9, 0x5E, 0xF9, 0xF1};

	DDRA = 0xFF; // Set PORTA as output
	DDRB = 0xFF; // Set PORTB as output
	DDRC = 0xFF; // Set PORTC as output
	DDRD = 0xFF; // Set PORTD as output

	PORTB = 0xFF; // Initialize PORTB with all pins high

	for (;;)
	{
		PORTA = (1 << PA0); // Turn on green LED
		for (i = g; i >= 0; i--)
		{
			PORTC = Cseg[i % 10];
			PORTD = ~Cseg[i / 10];
			_delay_ms(t);
		}

		PORTA = (1 << PA3); // Turn on red LED
		for (i = r; i >= 0; i--)
		{
			PORTC = Cseg[i % 10];
			PORTD = ~Cseg[i / 10];
			_delay_ms(t);
		}

		PORTA = 0x00; // Turn off both LEDs
		_delay_ms(t);
	}
}
