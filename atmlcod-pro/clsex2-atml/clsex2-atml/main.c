#include <avr/io.h>
#include <util/delay.h>

#define SHIFT_DELAY 1000 // 1 second delay for visibility

void init_ports(void) {
	// Set all PORTA, PORTB, PORTC, and PORTD pins as output
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	// Initialize all ports to 0
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
}

void shift_sequence(void) {
	uint8_t portA_patterns[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	uint8_t portB_patterns[] = {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01};
	uint8_t portC_patterns[] = {0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x01, 0x02};
	uint8_t *patterns[] = {portA_patterns, portB_patterns, portC_patterns};

	while (1) {
		for (int i = 0; i < 8; i++) {
			// Clear all ports
			PORTA = 0x00;
			PORTB = 0x00;
			PORTC = 0x00;

			// Set the current pattern
			PORTA = portA_patterns[i];
			_delay_ms(SHIFT_DELAY);

			PORTA = 0x00;
			PORTB = portB_patterns[i];
			_delay_ms(SHIFT_DELAY);

			PORTB = 0x00;
			PORTC = portC_patterns[i];
			_delay_ms(SHIFT_DELAY);

		}
	}
}

int main(void) {
	init_ports();
	shift_sequence();
	return 0;
}
