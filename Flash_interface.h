/*
 * Flash_interface.h
 *
 *  Created on: 24 Dec 2021
 *      Author: Rob Probin
 *      License: MIT
 *
 */

#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

#include "pforth-master/csrc/pf_all.h"

#ifdef __cplusplus
extern "C" {
#endif

ucell_t read_write_flash_size(void);
ucell_t number_of_flash_blocks(void);
ucell_t read_write_flash_block(ucell_t address, ucell_t block_number, ucell_t read_flag);

#ifdef __cplusplus
}
#endif


#endif /* FLASH_INTERFACE_H_ */
