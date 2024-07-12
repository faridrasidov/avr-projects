#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int i = 0;
	
	// Set all PORTA pins as output
	DDRA = 0xFF;
	// Set all PORTD pins as output
	DDRD = 0xFF;

	// Infinite loop
	while (1)
	{
		// ****************Part 01 - Shift Left
		// Set PA0 high
		PORTA |= (1 << PA0);
		_delay_ms(500);

		// Shift PORTA left
		for (i = 0; i < 7; i++)
		{
			PORTA <<= 1;
			_delay_ms(500);
		}

		// ****************Part 02 (WHILE) - Shift Right
		// Set PD7 high
		PORTD |= (1 << PD7);
		_delay_ms(50);

		// Initialize PORTD with 0x80 (10000000)
		PORTD = 0x80;
		// Shift PORTD right until it equals 0x01
		while (PORTD != 0x01)
		{
			PORTD >>= 1;
			_delay_ms(50);
		}
		// Set PD0 low
		PORTD &= ~(1 << PD0);
	}

	return 0;
}
