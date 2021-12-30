/*
 * IMU_interface.h
 *
 *  Created on: 25 Dec 2021
 *      Author: Rob Probin
 */

#ifndef IMU_INTERFACE_H_
#define IMU_INTERFACE_H_

// https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/

#include "pforth-master/csrc/pf_all.h"

#ifdef __cplusplus
extern "C" {
#endif

cell_t IMU_begin(void);
void IMU_end(void);
cell_t IMU_readAcceleration(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz);
cell_t IMU_readGyroscope(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz);
cell_t IMU_accelerationAvailable(void);
cell_t IMU_gyroscopeAvailable(void);
void IMU_accelerationSampleRate(cell_t sample_rate_float_ptr);
void IMU_gyroscopeSampleRate(cell_t sample_rate_float_ptr);
cell_t IMU_readMagneticField(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz);
void IMU_magneticFieldSampleRate(cell_t rate_float_ptr);
cell_t IMU_magneticFieldAvailable(void);

#ifdef __cplusplus
}
#endif

#endif /* IMU_INTERFACE_H_ */
