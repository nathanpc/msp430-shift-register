#include <msp430g2553.h>

#include "boolean.h"
#include "74HC595.h"
#include "delay.h"

#define LED BIT0
#define BUTTON BIT3

void main() {
	WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer.
	P1DIR |= LED;

	P1IE |= BUTTON;    // Set the P1 interrupt for the button.
	P1IES &= ~BUTTON;  // Set the interrupt to be from LOW to HIGH.
	P1IFG &= ~BUTTON;  // P1.3 IFG cleared
	__enable_interrupt();

	// Initialize the shift register driver.
	shift_register_setup();

	// Turn the LED OFF.
	P1OUT &= ~LED;

	while (1) {
		// Turn the ON indicator.
		//P1OUT ^= LED;
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR() {
	switch(P1IFG & BUTTON) {
		case BUTTON:
			P1OUT ^= LED;
			P1IFG &= ~BUTTON;  // P1.3 IFG cleared.
			
			while ((P1IN & BUTTON) == BUTTON) {}
			P1OUT ^= LED;
			break;

		default:
			P1IFG = 0;
			break;
	}
}
