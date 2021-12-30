/*
 * Flash_interface.cpp
 *
 *  Created on: 24 Dec 2021
 *      Author: Rob Probin
 *      License: MIT
 */

#include "Flash_interface.h"
#include "pforth-master/csrc/pf_all.h"
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <Arduino.h>
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <FlashIAPBlockDevice.h>

// OVERVIEW
// ========
//
// This is a flash block style system, that writes to entire blocks.
//
// Flash blocks are 4KByte long, but we want to access 1KByte Forth blocks.
//
// The structure of the code is that we have a base read/write routine that does a 4K block
// read or write in C. Then we manage the blocks themselves with higher level Forth code that
// does the buffer management.
//
// Information about the mbed Flash block API can be found here:
//   - https://os.mbed.com/docs/mbed-os/v6.9/apis/flashiapblockdevice.html
//   - https://os.mbed.com/docs/mbed-os/v6.9/mbed-os-api-doxy/_flash_i_a_p_block_device_8h_source.html
//
//
// A different example of this is inside Pete Warden's code:
//  - Code: https://github.com/petewarden/arduino_nano_ble_write_flash
//  - Description: https://petewarden.com/2021/04/28/how-to-write-to-flash-on-an-arduino-nano-ble/
//
// Information about using Blocks
//  - https://www.complang.tuwien.ac.at/forth/gforth/Docs-html/Blocks.html
//  - https://www.forth.com/starting-forth/3-forth-editor-blocks-buffer/
//  - http://www.whtech.com/ftp/programming/Forth/LeoBrodie-StartingForth/LeoBrodie-StartingForth-10-IO.pdf
//
// MEMORY NOTES
// =============
//
// The Arduino Nano 33 BLE contains a NINA B306 which is based on Nordic nRF52480 containing a Cortex M4F.
// This has 1MByte Flash and 256KByte of RAM.
//
// There are assumptions encoded in the constants of this
//
// ALTERNATIVES
// ============
//
// The alternative is to use a file system approach.
//
// Option 1: There is a very simple file system for Nordic for this chip.
// --------
//
// https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v14.1.0%2Fgroup__fds.html
//
//   "Flash Data Storage is a minimalistic, record-oriented file system for the
//    on-chip flash. Files are stored as a collection of records of variable length.
//    FDS supports synchronous read operations and asynchronous write operations
//    (write, update, and delete). FDS can be used from multiple threads. "
//
// Typical calls involved:
//  - fds_register()
//  - fds_init()
//  - fds_record_write()
//  - fds_record_find()
//  - fds_record_open()
//  - fds_record_close()
//  - fds_record_delete()
//
// An example using this is https://github.com/Dirk-/NanoBLEFlashPrefs
//
// This specific library (NanoBLEFlashPrefs) is licensed under GPLv2, so that means
// the application would need to be GPLv2 or GPLv3 - which is ok for some uses, but
// restrictive for others.

//
// Option 2: Use a standard embedded file-system
// --------
//
// This example uses LittleFS or FATFS where the filesystem access uses normal
// POSIX APIs or mbed FileSystem APIs
//
// This example library allows LittleFS or FATFS to be used.
//
//   https://github.com/khoih-prog/FS_Nano33BLE
//
// This library is licensed under library is licensed under GPLv3, so that means
// the application would need to be GPLv3 - which is ok for some uses, but restrictive
// for others.


// basic Flash constants
const uint32_t _1K = 1024;
const uint32_t flash_block_size = 4096;		// Determined by the internal flash minimum erase size.
const uint32_t flash_size = _1K*_1K; // 1MByte Flash
const uint32_t block_system_size_in_bytes = 256*_1K;	// *must* be a multiple of flash_block_size (4096)

// calculated constants
const uint32_t block_system_start_address = flash_size - block_system_size_in_bytes;	// assumption Flash starts at 0
const uint32_t number_of_blocks = block_system_size_in_bytes / flash_block_size;


extern "C" ucell_t read_write_flash_size(void)
{
	return flash_block_size;
}
extern "C" ucell_t number_of_flash_blocks(void)
{
	return number_of_blocks;
}

//extern "C" ucell_t read_write_erase_value(void)
//{
//	return device.get_erase_value();	// do we need this, or can we guess it?
//}

// blocks while writing
extern "C" ucell_t read_write_flash_block(ucell_t address, ucell_t block_number, ucell_t read_flag)
{
	static FlashIAPBlockDevice device(block_system_start_address, block_system_size_in_bytes);

	int err = device.init();
	if(err) { return err; }		// init error is fatal, drop out early

	// sanity check
	static bool block_size_ok = (flash_block_size == device.get_erase_size());
	if(block_size_ok && block_number > 0 && block_number <= number_of_blocks)
	{
		void *buffer = (void*)address;
		mbed::bd_addr_t addr = (block_number-1) * flash_block_size;

		if(read_flag)
		{
			err = device.read(buffer, addr, flash_block_size);
		}
		else
		{
			err = device.erase(addr, flash_block_size);
			// ignore the error and try programming anyway
			int pgm_err = device.program(buffer, addr, flash_block_size);
			if(!err) { err = pgm_err; }		// return error if no previous error
		}
	}
	else if(block_size_ok)
	{
		// block number out of range
		err = 12345678;	// unlikely mbed error code
	}
	else
	{
		// block size not ok
		err = 87654321;	// unlikely mbed error code
	}

	int err_deinit = device.deinit();
	if(!err) { err = err_deinit; }		// return error if no previous error

	return err;
}


