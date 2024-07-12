#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Initialize PORTA: Set all pins to low
	PORTA = 0x00;
	
	// Set PA0 as output (DDRA: Data Direction Register for Port A)
	DDRA = 0x01;

	// Infinite loop
	while (1)
	{
		// Set PA0 high
		PORTA |= (1 << PA0);
		_delay_ms(500);

		// Set PA0 low
		PORTA &= ~(1 << PA0);
		_delay_ms(500);
	}
	
	return 0;
}
