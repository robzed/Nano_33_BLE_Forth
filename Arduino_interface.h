/*
 * Arduino_interface.h
 *
 *  Created on: 23 Dec 2021
 *      Author: Rob Probin
 *      License: MIT
 *
 */

#ifndef ARDUINO_INTERFACE_H_
#define ARDUINO_INTERFACE_H_

#include "pforth-master/csrc/pf_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void ARDUINO_delay( cell_t val );
void ARDUINO_delayMicroseconds(cell_t val);
cell_t ARDUINO_micros(void);
cell_t ARDUINO_millis(void);


// stubs for PC build
#ifndef ARDUINO_ARDUINO_NANO33BLE
void ARDUINO_delay( cell_t val ) { }
void ARDUINO_delayMicroseconds(cell_t val) { }
cell_t ARDUINO_micros(void) { return 0; }
cell_t ARDUINO_millis(void) { return 0; }
#endif


#ifdef __cplusplus
}
#endif




#endif /* ARDUINO_INTERFACE_H_ */
