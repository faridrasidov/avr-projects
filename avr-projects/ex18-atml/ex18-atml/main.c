#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	char Cseg[10] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	char Aseg[5] = {0xFF, 0x00, 0xFF, 0x00, 0xFF};
	int i, j, k, G = 13, R = 11, Y = 1, D = 1000;

	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTB = 0xFF;

	for (;;)
	{
		PORTA |= (1 << PA0);
		for (i = G; i >= 0; i--)
		{
			PORTC = Cseg[i % 10];
			PORTD = Cseg[i / 10];
			_delay_ms(D);
		}
		PORTC = 0x00;
		PORTD = 0x00;
		PORTA &= ~(1 << PA0);
		PORTA |= (1 << PA3);
		for (k = Y; k >= 0; k--)
		{
			PORTB = Aseg[k];
			PORTC = 0x00;
			PORTD = Cseg[8];
			PORTB = Aseg[k + 1];
			_delay_ms(D);
			PORTB = Aseg[k];
			PORTC = Cseg[8];
			PORTD = 0x00;
			PORTB = Aseg[k + 1];
			_delay_ms(D);
		}
		PORTB = 0xFF;
		PORTA &= ~(1 << PA3);
		PORTA |= (1 << PA6);
		for (j = R; j >= 0; j--)
		{
			PORTC = Cseg[j % 10];
			PORTD = Cseg[j / 10];
			_delay_ms(D);
		}
		PORTC = 0x00;
		PORTD = 0x00;
		PORTA &= ~(1 << PA6);
	}
}
