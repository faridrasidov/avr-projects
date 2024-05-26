#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set initial state of PORTA and configure it as output
	PORTA = 0x01;
	DDRA = 0xFF;
	
	// Set PINB.0 as input with pull-up resistor enabled
	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);

	while (1)
	{
		// Check if PINB.0 is low
		if (!(PINB & (1 << PB0)))
		{
			// Increment PORTA from 0x01 to 0x08
			while (PORTA <= 0x08)
			{
				// Check if PINB.0 is still low
				if (!(PINB & (1 << PB0)))
				{
					_delay_ms(500);
					PORTA <<= 1;
				}
				else
				{
					break;
				}
			}
		}
		
		// Check if PINB.0 is high
		if (PINB & (1 << PB0))
		{
			// Decrement PORTA from 0x08 to 0x01
			while (PORTA >= 0x01)
			{
				// Check if PINB.0 is still high
				if (PINB & (1 << PB0))
				{
					_delay_ms(500);
					PORTA >>= 1;
				}
				else
				{
					break;
				}
			}
		}
		
		// Set PORTA to 0x08 at the end of the loop
		PORTA = 0x08;
	}
	
	return 0;
}
