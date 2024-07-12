#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	const int num = 6;
	char Cseg[] = {0x3F, 0x06, 0xDB, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0xFF, 0x6F};
	char Aseg[] = {0xFF, 0x00, 0xFF, 0x00};
	int i = 0, j = 0, k = 0;

	DDRA = 0xFF; // LED
	DDRB = 0xFF; // Yellow segment
	DDRC = 0xFF; // Green segment
	DDRD = 0xFF; // Red segment

	PORTB = 0xFF;

	while (1)
	{
		PORTA |= (1 << PA0); // Green lamp is on

		for (i = num - 1; i >= 0; i--) // Select delay time for green
		{
			PORTC = Cseg[i];
			_delay_ms(1000);
		}

		PORTC = 0x00;             // Green segment is empty
		PORTA &= ~(1 << PA0);     // Green lamp is off
		PORTA |= (1 << PA3);      // Yellow lamp is on

		for (k = num - 5; k >= 0; k--) // Select delay time for yellow
		{
			PORTB = Aseg[k];
			_delay_ms(500);
		}

		PORTB = 0xFF;             // Yellow segment is empty
		PORTA &= ~(1 << PA3);     // Yellow lamp is off
		PORTA |= (1 << PA6);      // Red lamp is on

		for (j = num - 4; j >= 0; j--) // Select delay time for red
		{
			PORTD = Cseg[j];
			_delay_ms(1000);
		}

		PORTD = 0x00;             // Red segment is empty
		PORTA &= ~(1 << PA6);     // Red lamp is off
	}
}
