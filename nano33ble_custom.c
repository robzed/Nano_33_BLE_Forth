/*
 * nano33ble_custom.cpp
 *
 *  Created on: 23 Dec 2021
 *      Author: RobP Probin
 *      License: MIT
 *
 */


#include "pforth-master/csrc/pf_all.h"
#include "Neopixel_interface.h"
#include "BLE_interface.h"
#include "Arduino_interface.h"
#include "Flash_interface.h"
#include "IMU_interface.h"
#include "File_system_interface.h"

#undef MIN
#undef MAX
#undef CODE_SIZE
#if ARDUINO_ARDUINO_NANO33BLE
#include <mbed_stats.h>
#endif
#undef MIN
#undef MAX
#undef CODE_SIZE

static cell_t Arduino_IFVer(void)
{
	// This version is the version of this interface.
	//
	// This allows user programs to check the version for compatibility, and
	// potentially support more than one version.
	//
	// Bump the version whenever the interface to any function changes or
	// extra functions are added
	return 1;
}

static ucell_t heap_stats(void)
{
	// Grab the heap statistics
#if ARDUINO_ARDUINO_NANO33BLE
 static mbed_stats_heap_t heap_stats;
 mbed_stats_heap_get(&heap_stats);
#else
 static int heap_stats = 0;
#endif
 return (ucell_t)&heap_stats;
}

const CFunc0 CustomFunctionTable[];

#define X(func, name_str, ret, params, comment) (CFunc0) func,


const CFunc0 CustomFunctionTable[]=
{
	#include "nano33ble_custom_function_list.inc"
};

#undef X
#define X(func, name_str, ret, params, comment) err = CreateGlueToC( name_str, i++, ret, params); if( err < 0 ) return err;

Err CompileCustomFunctions( void )
{
    Err err;
    int i = 0;

    #include "nano33ble_custom_function_list.inc"

    return 0;
}

