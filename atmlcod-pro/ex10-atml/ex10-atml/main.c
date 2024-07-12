#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	// Seven-segment display codes
	unsigned char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0xFF, 0x6F,
	0xF7, 0xFC, 0xB9, 0x5E, 0xF9, 0xF1};
	uint8_t flag = 0;
	int q = 0, j = 0, i = 0;

	// Set PORTA as input and enable pull-up resistors for PA0 to PA3
	DDRA = 0x00;
	PORTA = 0x0F;

	// Set PORTC and PORTD as output
	DDRC = 0xFF;
	PORTC = 0x00;
	DDRD = 0xFF;
	PORTD = 0xFF;

	// Display each segment code on PORTC with a 500ms delay
	for (q = 0; q <= 15; q++)
	{
		PORTC = seg[q];
		_delay_ms(500);
	}

	// Set initial display on PORTD
	PORTD = seg[0];

	// Infinite loop
	while (1)
	{
		// Check if button on PINA.0 is pressed and flag is false
		if (!(PINA & (1 << PA0)) && flag == 0)
		{
			j++;
			flag = 1;
		}

		// Check if button on PINA.0 is released
		if (PINA & (1 << PA0))
		{
			flag = 0;

			// Display the segment code for the current value of j
			for (i = 0; i < 17; i++)
			{
				PORTD = seg[j];
				if (j > 16) j = 0;
			}
		}
	}

	return 0;
}
