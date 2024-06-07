#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    int i, j, T = 6;
    char Aseg[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
    
    // Set all ports A, B, C, D as output
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
    
    PORTA = 0x02;  // Initialize PORTA with a value

    while (1)
    {
        for (i = T; i >= 0; i--)
        {
            PORTD = Aseg[i % 10];     // Display units digit
            j = i / 10;
            PORTC = Aseg[j % 10];     // Display tens digit
            PORTB = Aseg[j / 10];     // Display hundreds digit
            _delay_ms(500);

            if (i == 0)
            {
                while (1)
                {
                    PORTA = PORTA << 1;
                    _delay_ms(133);
                    if (PORTA == 0x80)
                    {
                        PORTA = PORTA >> 1;
                        _delay_ms(133);
                    }
                }
            }
        }
    }

    return 0;
}
