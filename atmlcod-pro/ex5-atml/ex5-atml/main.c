#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
	// Declare flags as boolean
	bool dir = false;
	bool flag = false;

	// Initialize PORTA and set it as input
	PORTA = 0xFF;
	DDRA = 0x00;

	// Initialize PORTB and set it as output
	PORTB = 0x01;
	DDRB = 0xFF;

	// Infinite loop
	while (1)
	{
		// Check if PA0 is low and flag is false
		if (!(PINA & (1 << PA0)) && !flag)
		{
			// Toggle direction
			dir = !dir;
			flag = true;
		}

		// Reset flag if PA0 is high
		if (PINA & (1 << PA0))
		{
			flag = false;
		}

		// Shift left if direction is false
		if (!dir)
		{
			_delay_ms(500);
			PORTB <<= 1;
			if (PORTB == 0x00)
			{
				PORTB = 0x01;
			}
		}

		// Shift right if direction is true
		if (dir)
		{
			_delay_ms(500);
			PORTB >>= 1;
			if (PORTB == 0x00)
			{
				PORTB = 0x80;
			}
		}
	}

	return 0;
}
