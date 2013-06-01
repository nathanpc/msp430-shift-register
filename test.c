#include <msp430g2553.h>

#include "boolean.h"
#include "74HC595.h"
#include "delay.h"

#define LED BIT0

void main() {
	WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer.
	P1DIR |= LED;
	
	// Initialize the shift register driver.
	shift_register_setup();

	// Do stuff.

	while (1) {
		// Turn the ON indicator.
		P1OUT ^= LED;
	}
}
