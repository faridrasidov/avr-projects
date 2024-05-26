#include <avr/io.h>
#include <util/delay.h>

#define NUM 16

int main(void)
{
	unsigned char seg[NUM] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F,
	0xF7, 0xFC, 0xB9, 0x5E, 0xF9, 0xF1};
	uint8_t afa = 0;
	int j = -1;

	DDRD = 0xFF; // Set PORTD as output
	DDRA &= ~(1 << DDA0); // Set PINA.0 as input

	while (1)
	{
		if ((PINA & (1 << PINA0)) == 0 && afa == 0)
		{
			afa = 1;
			j++;
			if (j >= NUM)
			{
				j = 0;
			}
		}

		if (PINA & (1 << PINA0))
		{
			afa = 0;
			if (j >= 0 && j < NUM)
			{
				PORTD = seg[j];
			}
		}

		_delay_ms(50); // Debounce delay
	}

	return 0;
}
