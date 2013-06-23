#include <msp430g2553.h>

#include "boolean.h"
#include "74HC595.h"
#include "delay.h"

#define LED BIT0
#define BT_INT BIT3

unsigned char leds = 0b00000000;

void main() {
	WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer.
	P1DIR |= LED;

	P1IE |= BT_INT;    // Set the P1 interrupt for the button.
	P1IES &= ~BT_INT;  // Set the interrupt to be from LOW to HIGH.
	P1IFG &= ~BT_INT;  // P1.3 IFG cleared
	__enable_interrupt();

	// Initialize the shift register driver.
	shift_register_setup();
	shift_out(0b11110000);

	// Turn the LED OFF.
	P1OUT &= ~LED;

	while (1) {
	}
}

void set_led(unsigned int bt) {
	switch (bt) {
		case 0:
			leds ^= 0b00001000;
			break;
		case 1:
			leds ^= 0b00000100;
			break;
		case 2:
			leds ^= 0b00000010;
			break;
		case 3:
			leds = 0b00000000;
			break;
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR() {
	switch(P1IFG & BT_INT) {
		case BT_INT:
			P1OUT ^= LED;
			P1IFG &= ~BT_INT;  // P1.3 IFG cleared.
			
			for (unsigned int i = 0; i < 4; i++) {
				unsigned char tmp[] = { 0b10000000, 0b01000000, 0b00100000, 0b00010000 };
				tmp[i] |= leds;
				
				shift_out(tmp[i]);
				//delay_us(30);
				if ((P1IN & BT_INT) == BT_INT) {
					set_led(i);
				}
			}
			
			unsigned char lst = 0b11110000;
			lst |= leds;
			shift_out(lst);
			
			while ((P1IN & BT_INT) == BT_INT) {}
			P1OUT ^= LED;
			break;

		default:
			P1IFG = 0;
			break;
	}
}
