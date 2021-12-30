/*
 * IMU_interface.cpp
 *
 *  Created on: 25 Dec 2021
 *      Author: Rob Probin
 */

#include "IMU_interface.h"
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <Arduino_LSM9DS1.h>
#undef MIN
#undef MAX
#undef CODE_SIZE

// https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/

cell_t IMU_begin(void)
{
	return IMU.begin()?-1:0;
}

void IMU_end(void)
{
	IMU.end();
}

cell_t IMU_readAcceleration(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz)
{
	float* fx_ptr = (float*)ptr_fx;
	float* fy_ptr = (float*)ptr_fy;
	float* fz_ptr = (float*)ptr_fz;
	return IMU.readAcceleration(*fx_ptr, *fy_ptr, *fz_ptr);
}

cell_t IMU_readGyroscope(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz)
{
	float* fx_ptr = (float*)ptr_fx;
	float* fy_ptr = (float*)ptr_fy;
	float* fz_ptr = (float*)ptr_fz;
	return IMU.readGyroscope(*fx_ptr, *fy_ptr, *fz_ptr);
}

cell_t IMU_accelerationAvailable(void)
{
	return IMU.accelerationAvailable()?-1:0;
}

cell_t IMU_gyroscopeAvailable(void)
{
	return IMU.gyroscopeAvailable()?-1:0;
}

void IMU_accelerationSampleRate(cell_t sample_rate_float_ptr)
{
	// can't return float, so use pointer to FP variable
	float* fp = (float*)sample_rate_float_ptr;
	*fp = IMU.magneticFieldAvailable();
}

void IMU_gyroscopeSampleRate(cell_t sample_rate_float_ptr)
{
	// can't return float, so use pointer to FP variable
	float* fp = (float*)sample_rate_float_ptr;
	*fp = IMU.magneticFieldAvailable();
}

cell_t IMU_readMagneticField(cell_t ptr_fx, cell_t ptr_fy, cell_t ptr_fz)
{
	float* fx_ptr = (float*)ptr_fx;
	float* fy_ptr = (float*)ptr_fy;
	float* fz_ptr = (float*)ptr_fz;
	return IMU.readMagneticField(*fx_ptr, *fy_ptr, *fz_ptr);
}


void IMU_magneticFieldSampleRate(cell_t rate_float_ptr)
{
	// can't return float, so use pointer to FP variable
	float* fp = (float*)rate_float_ptr;
	*fp = IMU.magneticFieldAvailable();
}

cell_t IMU_magneticFieldAvailable(void)
{
	return IMU.magneticFieldAvailable()?-1:0;
}

