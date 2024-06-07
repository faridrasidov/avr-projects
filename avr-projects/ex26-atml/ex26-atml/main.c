#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD20x4_4bit.h"

// Buffer to store the formatted time string
char timeString[20];


// Main function
int main(void) {
	// Time variables
	int hours = 22, minutes = 59, seconds = 22;
	int delayTime = 1000;  // Delay in milliseconds

	// Initialize LCD
	lcdinit();

	// Main loop
	while (1) {
		// Format the time as a string
		sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);
		
		// Display the time string on the LCD
		lcd_print(timeString);
		
		// Wait for 1 second
		_delay_ms(delayTime);
		
		// Clear the LCD
		lcd_clear();
		
		// Increment the seconds
		seconds++;
		
		// Handle overflow of seconds to minutes
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
		
		// Handle overflow of minutes to hours
		if (minutes == 60) {
			minutes = 0;
			hours++;
		}
		
		// Handle overflow of hours to a new day
		if (hours == 24) {
			hours = minutes = seconds = 0;
			PORTA |= (1 << PA3);  // Set PA3 high
		}
	}

	return 0;
}
