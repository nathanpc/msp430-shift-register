/**
 *	74HC595.h
 *	A 74HC595 shift register driver for the MSP430G2553.
 *
 *	@author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _74HC595_SHIFT_REGISTER_H_
#define _74HC595_SHIFT_REGISTER_H_

#include <stdint.h>
#include "boolean.h"

void shift_register_setup();

void shift_register_clock();
void shift_out(unsigned char value);

#endif  // _74HC595_SHIFT_REGISTER_H_
