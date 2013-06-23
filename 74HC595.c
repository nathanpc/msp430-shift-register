/**
 *	74HC595.h
 *	A 74HC595 shift register driver for the MSP430G2553.
 *
 *	@author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <msp430g2553.h>
#include <stdint.h>

#include "boolean.h"
#include "74HC595.h"
#include "delay.h"
#include "bitio.h"

// Define the shift register pins.
#define DATA BIT4
#define LATCH BIT5
#define CLOCK BIT6

/**
 * Setup the shift register pins.
 */
void shift_register_setup() {
	P1DIR |= (DATA + LATCH + CLOCK);
}

/**
 * Sends a clock pulse to the shift register.
 */
void shift_register_clock() {
	P1OUT |= CLOCK;
	P1OUT ^= CLOCK;
}

/**
 * Shifts out a value to the shift register.
 * 
 * @param value The value to be shifted.
 */
void shift_out(unsigned char value) {
	// Latch LOW to start shifting data.
	P1OUT &= ~LATCH;

	for (unsigned int i = 0; i < 8; i++) {
		// Shift every bit.
		bit_to_pin(value, i, &P1OUT, DATA);
		shift_register_clock();
	}

	// Latch the data.
	P1OUT |= LATCH;
	P1OUT &= ~LATCH;
}
