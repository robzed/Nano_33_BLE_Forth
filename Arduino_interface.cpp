/*
 * Arduino_interface.cpp
 *
 *  Created on: 23 Dec 2021
 *      Author: Rob Probin
 */

#include "Arduino_interface.h"
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <Arduino.h>
#undef MIN
#undef MAX
#undef CODE_SIZE

extern "C" void ARDUINO_delay( cell_t val )
{
	delay(val);
}

extern "C" void ARDUINO_delayMicroseconds(cell_t val)
{
	delayMicroseconds(val);
}

extern "C" cell_t ARDUINO_micros(void)
{
	return micros();
}

extern "C" cell_t ARDUINO_millis(void)
{
	return millis();
}
