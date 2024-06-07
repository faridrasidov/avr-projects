#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

int main(void)
{
	const int num = 16;
	unsigned char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F, 0xF7, 0xFC, 0xB9, 0x5E, 0xF9, 0xF1};
	uint8_t afa = 0;
	int j = -1, i = 0;

	// Set PORTD and PORTC as output
	DDRD = 0xFF;
	DDRC = 0xFF;

	// Set PORTA as input with pull-up resistors enabled
	DDRA = 0x00;
	PORTA = 0xFF;

	while (1)
	{
		if (!(PINA & (1 << PA0)) && afa == 0)
		{
			afa = 1;
		}

		if (PINA & (1 << PA0))
		{
			afa = 0;
			if (j >= 0) // Ensure j is within valid range before accessing the array
			{
				PORTD = seg[j];
			}
			PORTC = seg[i];

			j++;
			if (j >= num) i++;
			if (j >= num) j = 0;
			if (i >= num) i = 0;

			_delay_ms(1000); // Add 1-second delay
		}
	}

	return 0;
}
