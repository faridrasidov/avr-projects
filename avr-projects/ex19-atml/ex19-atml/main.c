#include <avr/io.h>
#include <util/delay.h>

#define green (PORTA = (PORTA & ~(1 << PA6)) | (1 << PA0))
#define red (PORTA = (PORTA & ~(1 << PA0)) | (1 << PA6))

void main(void)
{
	char seg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	int i, g = 13, r = 6, t = 1000;
	
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	for (;;)
	{
		green;
		for (i = g; i >= 0; i--)
		{
			PORTC = seg[i % 10];
			PORTD = seg[i / 10];
			_delay_ms(t);
		}
		
		red;
		for (i = r; i >= 0; i--)
		{
			PORTC = seg[i % 10];
			PORTD = seg[i / 10];
			_delay_ms(t);
		}
		// You might need to set the corresponding bit to turn off the LEDs
		// For now, I'm assuming you're handling this elsewhere in your code.
	}
}
