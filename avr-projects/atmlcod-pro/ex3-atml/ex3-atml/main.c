#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
	// Declare flags as boolean
	bool flag = false;
	bool FLAG = false;

	// Initialize PORTA with 0xCC (11001100)
	PORTA = 0xCC;
	
	// Set PA0, PA2, PA4, and PA6 as output (binary 01010101)
	DDRA = 0x55;

	// Infinite loop
	while (1)
	{
		// Check if PA1 is high and flag is true
		if ((PINA & (1 << PA1)) && flag)
		{
			// Toggle PA0
			PORTA ^= (1 << PA0);
			flag = false;
		}

		// Reset flag if PA1 is low
		if (!(PINA & (1 << PA1)))
		{
			flag = true;
		}

		// Check if PA3 is high and FLAG is true
		if ((PINA & (1 << PA3)) && FLAG)
		{
			// Toggle PA2
			PORTA ^= (1 << PA2);
			FLAG = false;
		}

		// Reset FLAG if PA3 is low
		if (!(PINA & (1 << PA3)))
		{
			FLAG = true;
		}
	}

	return 0;
}
