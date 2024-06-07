#include <avr/io.h>

#define NUM 10

int main(void)
{
	char seg[NUM] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	uint8_t flag = 0;
	int i = 0;
	
	// Set PORTC and PORTD as output
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	// Infinite loop
	while(1)
	{
		PORTD = seg[i % 10]; // Display units digit
		PORTC = seg[i / 10]; // Display tens digit
		
		// Check if PINA0 is high and flag is 0
		if ((PINA & (1 << PINA0)) && flag == 0)
		{
			flag = 1;
			i++;
		}
		
		// Reset flag if PINA0 is low
		if (!(PINA & (1 << PINA0)))
		{
			flag = 0;
		}
		
		// Reset i if it reaches 100
		if (i == 100)
		{
			i = 0;
		}
	}

	return 0;
}
