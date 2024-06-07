#include <avr/io.h>
#include <util/delay.h>
#include "LCD20x4_4bit.h"  // Custom library for LCD

int main(void)
{
    DDRC = 0xFF;  // Set PORTC as output for LCD
    lcdinit();  // Initialize the LCD

    while (1)
    {
        _delay_ms(100);
        lcd_clear();  // Clear the LCD
        lcd_gotoxy(3, 0);
        lcd_print("My");
        _delay_ms(100);
        lcd_gotoxy(6, 0); 
        lcd_print("Name Is");  
        _delay_ms(100);
        lcd_gotoxy(5, 2);  
        lcd_print("Farid Rasidov");  
        _delay_ms(1000);
        lcd_clear();  // Clear the LCD
    }

    return 0;
}
