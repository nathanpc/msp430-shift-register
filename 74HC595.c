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

// Define the shift register pins.
#define DATA BIT4
#define LATCH BIT5
#define CLOCK BIT6

// Private function declarations.
unsigned int get_byte(char b, unsigned int pos);
void bit_to_pin(char c, unsigned int pos, unsigned int pin);


/**
 * Get a single bit from a byte.
 * 
 * @param b A byte.
 * @param pos The bit position to be extracted.
 * @return A bit.
 */
unsigned int get_byte(char b, unsigned int pos) {
	return (b & (1 << pos));
}

/**
 * Puts the desired bit into a pin. It's used to get the bits in a char
 * to send to the LCD.
 * 
 * @param c The character.
 * @param pos Bit position.
 * @param pin The pin to be set.
 */
void bit_to_pin(char c, unsigned int pos, unsigned int pin) {
	if (get_byte(c, pos)) {
		P1OUT |= pin;
	} else {
		P1OUT &= ~pin;
	}
}

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

void shift_out(unsigned char value) {
	// Latch LOW to start shifting data.
	P1OUT &= ~LATCH;

	for (unsigned int i = 0; i < 8; i++) {
		// Shift every bit.
		bit_to_pin(value, i, DATA);
		shift_register_clock();
	}

	// Latch the data.
	P1OUT |= LATCH;
	P1OUT &= ~LATCH;
}
