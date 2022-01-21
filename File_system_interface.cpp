/*
 * File_system_interface.cpp
 *
 *  Created on: 16 Jan 2022
 *      Author: Rob Probin
 */

#include "File_system_interface.h"

#include "mbed.h"
#include "LittleFileSystem.h"
#include "Dir.h"
#include <new>
extern mbed::LittleFileSystem& get_FileSystem(void);
#include <stdio.h>

using mbed::Dir;

ucell_t filesystem_mkdir(ucell_t c_name_ptr, ucell_t mode)
{
	mbed::FileSystem* fs = mbed::FileSystem::get_default_instance();
	return fs->mkdir((const char*)c_name_ptr, (mode_t) mode);
}

ucell_t filesystem_opendir(ucell_t c_name_ptr)
{
	Dir* d = new(std::nothrow) Dir(&get_FileSystem(), (char*)c_name_ptr);
	return (ucell_t)d;
}

cell_t filesystem_readdir(ucell_t dir_ptr, ucell_t direntry_ptr)
{
	if(dir_ptr == 0) { return 0; }
	Dir* d = (Dir*)dir_ptr;
	return d->read((struct dirent *)direntry_ptr);
}

ucell_t filesystem_sizedirentry(ucell_t select)
{
	ucell_t result = 0;
	switch(select) {
		case 0:
			result = sizeof(struct dirent);
			break;
		case 1:
			result = offsetof(dirent, d_name);
			break;
		case 2:
			result = NAME_MAX;
			break;
		case 3:
			result = offsetof(dirent, d_type);
			break;
		case 4:
		{
			struct dirent d;
			result = sizeof(d.d_name);
			break;
		}
		case 5:
		{
			struct dirent d;
			result = sizeof(d.d_type);
			break;
		}
		default:
			result = -1;
			break;
	}
	return result;
}

cell_t filesystem_closedir(ucell_t dir_ptr)
{
	if(dir_ptr == 0) { return 0; }
	Dir* d = (Dir*)dir_ptr;
	return d->close();
}

ucell_t filesystem_sizedir(ucell_t dir_ptr)
{
	if(dir_ptr == 0) { return 0; }
	Dir* d = (Dir*)dir_ptr;
	return d->size();
}


ucell_t filesystem_fsstat(ucell_t c_name_ptr, ucell_t output_buff)
{
	mbed::FileSystem* fs = mbed::FileSystem::get_default_instance();
	return fs->stat((const char*)c_name_ptr, (struct stat *) output_buff);
}

ucell_t filesystem_statvfs(ucell_t c_name_ptr, ucell_t output_buff)
{
	mbed::FileSystem* fs = mbed::FileSystem::get_default_instance();
	return fs->statvfs((const char*)c_name_ptr, (struct statvfs *) output_buff);
}

ucell_t filesystem_XFSSTAT(ucell_t select)
{
	ucell_t result = 0;
	switch(select) {
		case 0:
			result = sizeof(struct stat);
			break;
		default:
			result = -1;
			break;
	}
	return result;
}
ucell_t filesystem_XSTATVFS(ucell_t select)
{
	ucell_t result = 0;
	switch(select) {
		case 0:
			result = sizeof(struct statvfs);
			break;
		default:
			result = -1;
			break;
	}
	return result;
}


#ifdef SEPERATE_REMOVE_RENAME

cell_t filesystem_fsremove(ucell_t c_name_ptr)
{
	return remove((char*)c_name_ptr);
}

cell_t filesystem_fsrename(ucell_t old_c_name_ptr, ucell_t new_c_name_ptr)
{
	return rename((char*)old_c_name_ptr,	(char*)new_c_name_ptr);
}


#endif