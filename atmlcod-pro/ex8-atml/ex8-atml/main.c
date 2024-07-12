#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int i = 0;

	DDRA = 0xFF; // Set PORTA as output
	DDRB = 0xFF; // Set PORTB as output
	DDRC = 0xFF; // Set PORTC as output
	DDRD = 0x7F; // Set PORTD as output except for PD7

	PORTA = 0x4E; // Initialize PORTA with 0b01001110
	PORTB = 0xBF; // Initialize PORTB with 0b10111111
	PORTC = 0xFE; // Initialize PORTC with 0b11111110

	while (1)
	{
		if (i == 0)
		PORTD = 0x3F;
		else if (i == 1)
		PORTD = 0x06;
		else if (i == 2)
		PORTD = 0xDB;
		else if (i == 3)
		PORTD = 0x4F;
		else if (i == 4)
		PORTD = 0x66;
		else if (i == 5)
		PORTD = 0x6D;
		else if (i == 6)
		PORTD = 0x7D;
		else if (i == 7)
		PORTD = 0x27;
		else if (i == 8)
		PORTD = 0xFF;
		else if (i == 9)
		PORTD = 0x6F;
		else if (i == 10)
		PORTD = 0xF7;
		else if (i == 11)
		PORTD = 0xFC;
		else if (i == 12)
		PORTD = 0xB9;
		else if (i == 13)
		PORTD = 0x5E;
		else if (i == 14)
		PORTD = 0xF9;
		else if (i == 15)
		PORTD = 0xF1;
		else if (i == 16)
		{
			PORTD = 0x00;
			i = -1;
			_delay_ms(500);
		}

		_delay_ms(500);
		i = i + 1;
	}

	return 0;
}
