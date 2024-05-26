#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Initialize PORTA with 0x0A
	PORTA = 0x0A;
	
	// Set PA0, PA2, and PA4 as output, PA1 and PA3 as input
	DDRA = 0x15;

	// Infinite loop
	while (1)
	{
		// Set PA4 high
		PORTA |= (1 << PA4);

		// Check the status of PA1
		if (PINA & (1 << PA1))
		{
			// Set PA0 low if PA1 is high
			PORTA &= ~(1 << PA0);
		}
		else
		{
			// Set PA0 high if PA1 is low
			PORTA |= (1 << PA0);
		}

		// Check the status of PA3
		if (PINA & (1 << PA3))
		{
			// Set PA2 low if PA3 is high
			PORTA &= ~(1 << PA2);
		}
		else
		{
			// Set PA2 high if PA3 is low
			PORTA |= (1 << PA2);
			_delay_ms(5000); // Wait for 5000 ms
			PORTA &= ~(1 << PA2); // Set PA2 low
		}
	}

	return 0;
}
