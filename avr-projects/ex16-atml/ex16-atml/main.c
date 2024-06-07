#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int T = 1;
	char Aseg[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	while (1)
	{
		PORTC = 0b00000001;
		PORTD = Aseg[8];
		_delay_ms(T);
		PORTC = 0b00000010;
		PORTD = Aseg[3];
		_delay_ms(T);
		PORTC = 0b00000100;
		PORTD = Aseg[3];
		_delay_ms(T);
		PORTC = 0b00001000;
		PORTD = Aseg[4];
		_delay_ms(T);
	}
	return 0;
}
