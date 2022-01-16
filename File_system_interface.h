/*
 * File_system_interface.h
 *
 *  Created on: 16 Jan 2022
 *      Author: Rob Probin
 */

#ifndef FILE_SYSTEM_INTERFACE_H_
#define FILE_SYSTEM_INTERFACE_H_


#include "pforth-master/csrc/pf_all.h"
#undef MIN
#undef MAX
#undef CODE_SIZE

#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

//ucell_t filesystem_mkdir(ucell_t c_name_ptr);
ucell_t filesystem_opendir(ucell_t c_name_ptr);
cell_t filesystem_readdir(ucell_t dir_ptr, ucell_t direntry_ptr);
cell_t filesystem_closedir(ucell_t dir_ptr);
ucell_t filesystem_sizedir(ucell_t dir_ptr);

ucell_t filesystem_sizedirentry(ucell_t select);
//ucell_t filesystem_fssize(void);
cell_t filesystem_fsremove(ucell_t c_name_ptr);
cell_t filesystem_fsrename(ucell_t old_c_name_ptr, ucell_t new_c_name_ptr);

// filesystem_statvfs
// filesystem_stat


// stubs for PC build
#ifndef ARDUINO_ARDUINO_NANO33BLE

ucell_t filesystem_opendir(ucell_t c_name_ptr) { return 0; }
cell_t filesystem_readdir(ucell_t dir_ptr, ucell_t direntry_ptr) { return 0; }
cell_t filesystem_closedir(ucell_t dir_ptr) { return 0; }
ucell_t filesystem_sizedir(ucell_t dir_ptr) { return 0; }

ucell_t filesystem_sizedirentry(ucell_t select) { return 0; }
cell_t filesystem_fsremove(ucell_t c_name_ptr) { return 0; }
cell_t filesystem_fsrename(ucell_t old_c_name_ptr, ucell_t new_c_name_ptr) { return 0; }

#endif


#ifdef __cplusplus
}
#endif


#endif /* FILE_SYSTEM_INTERFACE_H_ */
