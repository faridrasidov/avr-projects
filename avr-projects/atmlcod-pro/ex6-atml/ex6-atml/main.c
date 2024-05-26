#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	int num[] = {1, 2, 4, 8, 16, 32, 64, 128};
	int i;
	uint16_t t = 500; // Use uint16_t for portability and clarity
	DDRA = 0xFF; // Set Port A as output

	while (1)
	{
		for (i = 0; i < 8; i++) // i < 8 instead of i <= 7 for clarity
		{
			PORTA = num[i];
			_delay_ms(t);
		}
	}
}
