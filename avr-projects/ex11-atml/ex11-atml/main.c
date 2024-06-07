#include <avr/io.h>
#include <stdint.h>

#define F_CPU 1000000UL // Define clock speed for delay
#include <util/delay.h>

int main(void)
{
	// Constants and variables
	const int num = 9;
	unsigned char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F, 0xF7, 0xFC, 0xB9, 0x5E, 0xF9, 0xF1};
	uint8_t afa = 0;
	int j = -1, i = 0;

	// Port configuration
	DDRD = 0xFF; // Set PORTD as output
	DDRC = 0xFF; // Set PORTC as output
	DDRA = 0x00; // Set PORTA as input
	PORTA = 0xFF; // Enable pull-up resistors on PORTA

	// Infinite loop
	while (1)
	{
		if (!(PINA & (1 << PA0)) && afa == 0)
		{
			afa = 1;
			j++;
			if (j > num) i++;
		}

		if (PINA & (1 << PA0))
		{
			afa = 0;
			PORTD = seg[j];
			PORTC = seg[i];
			if (j > num) j = 0;
			if (i > num) i = 0;
		}
	}

	return 0;
}
