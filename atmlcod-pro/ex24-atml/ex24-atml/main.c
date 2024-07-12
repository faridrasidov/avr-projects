#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
	uint8_t F1 = 0, F2 = 0, F3 = 0;
	int i, j, G = 4, R = 2, dg = 14, dr = 12, Y = 1, T = 1000, t = 50;
	char Aseg[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0xFF};
	char Cseg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x71, 0x77, 0x00};

	DDRA = 0x07;       // Set PA0, PA1, PA2 as output
	PORTA = 0x80;      // Set PA7 high

	DDRB = 0b01111111; // Set PB0 to PB6 as output
	PORTB = 0b01111111; // Initialize PORTB

	DDRC = 0b01111111; // Set PC0 to PC6 as output
	PORTC = 0b10000000; // Initialize PORTC

	DDRD = 0b01111111; // Set PD0 to PD6 as output
	PORTD = 0b10000000; // Initialize PORTD

	for (;;)
	{
		if (!(PINA & (1 << PA6)))
		{
			if (!(PIND & (1 << PD7)))
			{
				for (i = G; i >= 0; i--)
				{
					PORTD = Cseg[i % 10];
					j = i / 10;
					PORTC = Cseg[j % 10];
					PORTB = Aseg[j / 10];
					_delay_ms(T / t);
				}
				G = 0;
			}

			if (!(PINC & (1 << PC7)))
			{
				if (G > dg)
				{
					for (i = G; i >= dg; i--)
					{
						PORTD = Cseg[i % 10];
						j = i / 10;
						PORTC = Cseg[j % 10];
						PORTB = Aseg[j / 10];
						_delay_ms(T / t);
					}
				}

				if (G < dg)
				{
					for (i = G; i <= dg; i++)
					{
						PORTD = Cseg[i % 10];
						j = i / 10;
						PORTC = Cseg[j % 10];
						PORTB = Aseg[j / 10];
						_delay_ms(T / t);
					}
				}
				G = dg;
			}

			PORTA |= (1 << PA0);
			PORTA &= ~(1 << PA2);
			PORTD = Cseg[G % 10];
			j = G / 10;
			PORTC = Cseg[j % 10];
			PORTB = Aseg[j / 10];

			if (G > 999 || G < 0)
			{
				PORTB = Aseg[10];
				_delay_ms(T / 2);
				PORTC = Cseg[10];
				_delay_ms(T / 2);
				PORTD = Cseg[11];
				_delay_ms(T / 2);
				PORTB = 0xFF;
				_delay_ms(T / 2);
				PORTC = 0x00;
				_delay_ms(T / 2);
				PORTD = 0x00;
				_delay_ms(T / 2);
				G = 0;
			}

			if (!(PINB & (1 << PB7)))
			{
				if ((PINA & (1 << PA3)) && F1 == 0) { F1 = 1; G++; }
				if (!(PINA & (1 << PA3))) { F1 = 0; }
				if ((PINA & (1 << PA4)) && F2 == 0) { F2 = 1; G += 10; }
				if (!(PINA & (1 << PA4))) { F2 = 0; }
				if ((PINA & (1 << PA5)) && F3 == 0) { F3 = 1; G += 100; }
				if (!(PINA & (1 << PA5))) { F3 = 0; }
			}

			if (PINB & (1 << PB7))
			{
				if ((PINA & (1 << PA3)) && F1 == 0) { F1 = 1; G--; }
				if (!(PINA & (1 << PA3))) { F1 = 0; }
				if ((PINA & (1 << PA4)) && F2 == 0) { F2 = 1; G -= 10; }
				if (!(PINA & (1 << PA4))) { F2 = 0; }
				if ((PINA & (1 << PA5)) && F3 == 0) { F3 = 1; G -= 100; }
				if (!(PINA & (1 << PA5))) { F3 = 0; }
			}
		}

		if (PINA & (1 << PA6))
		{
			if (!(PIND & (1 << PD7)))
			{
				for (i = R; i >= 0; i--)
				{
					PORTD = Cseg[i % 10];
					j = i / 10;
					PORTC = Cseg[j % 10];
					PORTB = Aseg[j / 10];
					_delay_ms(T / t);
				}
				R = 0;
			}

			if (!(PINC & (1 << PC7)))
			{
				if (R > dr)
				{
					for (i = R; i >= dr; i--)
					{
						PORTD = Cseg[i % 10];
						j = i / 10;
						PORTC = Cseg[j % 10];
						PORTB = Aseg[j / 10];
						_delay_ms(T / t);
					}
				}

				if (R < dr)
				{
					for (i = R; i <= dr; i++)
					{
						PORTD = Cseg[i % 10];
						j = i / 10;
						PORTC = Cseg[j % 10];
						PORTB = Aseg[j / 10];
						_delay_ms(T / t);
					}
				}
				R = dr;
			}

			PORTA |= (1 << PA2);
			PORTA &= ~(1 << PA0);
			PORTD = Cseg[R % 10];
			j = R / 10;
			PORTC = Cseg[j % 10];
			PORTB = Aseg[j / 10];

			if (R > 999 || R < 0)
			{
				PORTB = Aseg[10];
				_delay_ms(T / 2);
				PORTC = Cseg[10];
				_delay_ms(T / 2);
				PORTD = Cseg[11];
				_delay_ms(T / 2);
				PORTB = 0xFF;
				_delay_ms(T / 2);
				PORTC = 0x00;
				_delay_ms(T / 2);
				PORTD = 0x00;
				_delay_ms(T / 2);
				R = 0;
			}

			if (!(PINB & (1 << PB7)))
			{
				if ((PINA & (1 << PA3)) && F1 == 0) { F1 = 1; R++; }
				if (!(PINA & (1 << PA3))) { F1 = 0; }
				if ((PINA & (1 << PA4)) && F2 == 0) { F2 = 1; R += 10; }
				if (!(PINA & (1 << PA4))) { F2 = 0; }
				if ((PINA & (1 << PA5)) && F3 == 0) { F3 = 1; R += 100; }
				if (!(PINA & (1 << PA5))) { F3 = 0; }
			}

			if (PINB & (1 << PB7))
			{
				if ((PINA & (1 << PA3)) && F1 == 0) { F1 = 1; R--; }
				if (!(PINA & (1 << PA3))) { F1 = 0; }
				if ((PINA & (1 << PA4)) && F2 == 0) { F2 = 1; R -= 10; }
				if (!(PINA & (1 << PA4))) { F2 = 0; }
				if ((PINA & (1 << PA5)) && F3 == 0) { F3 = 1; R -= 100; }
				if (!(PINA & (1 << PA5))) { F3 = 0; }
			}
		}

		if (!(PINA & (1 << PA7)))
		{
			for (;;)
			{
				PORTA |= (1 << PA0);
				PORTA &= ~(1 << PA2);
				for (i = G; i >= 0; i--)
				{
					PORTD = Cseg[i % 10];
					j = i / 10;
					PORTC = Cseg[j % 10];
					PORTB = Aseg[j / 10];
					_delay_ms(T / t);
				}
				G = 0;

				PORTA |= (1 << PA2);
				PORTA &= ~(1 << PA0);
				for (i = R; i >= 0; i--)
				{
					PORTD = Cseg[i % 10];
					j = i / 10;
					PORTC = Cseg[j % 10];
					PORTB = Aseg[j / 10];
					_delay_ms(T / t);
				}
				R = 0;
			}
		}
	}
}
