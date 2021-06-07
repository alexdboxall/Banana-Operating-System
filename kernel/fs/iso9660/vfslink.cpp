#include "fs/iso9660/vfslink.hpp"
#include "core/main.hpp"
#include "core/kheap.hpp"
#include "hal/logidisk.hpp"

/*
The old ISO 9660 driver was 'sketchy as hell'
It was based on code I wrote at an athletics carnival (!) a few years ago.

A badly formatted disk would cause array indices to exceed boundaries,
and crashing the OS.
*/

extern "C" {
	#include <fs/iso9660/iso9660.h>
	#include "libk/string.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint8_t recentBuffer[2048];
uint32_t recentSector = 0;
char recentDriveletter = '0';

int readSectorFromCDROM(uint32_t sector, uint8_t* data, char driveletter)
{
	if (sector != recentSector || recentDriveletter != driveletter) {
		int fail = disks[driveletter - 'A']->read(sector, 1, recentBuffer);
		if (!fail) {
			recentSector = sector;
			recentDriveletter = driveletter;
		} else {
			memset(data, 0, 2048);
			return 1;
		}
	}

	memcpy(data, recentBuffer, 2048);
	return 0;
}

ISO9660::ISO9660() : Filesystem()
{
	fs_iso9660_init();
}

ISO9660::~ISO9660()
{

}

FileStatus ISO9660::format(LogicalDisk* disk, int disknum, const char* type, int allocationUnit)
{
	return FileStatus::FormatNotSupported;
}

bool ISO9660::tryMount(LogicalDisk* disk, int diskNum)
{
	recentSector = 0xDEADBEEF;
	char recentDriveletter = '0';

	char bf[2048];
	int res = readSectorFromCDROM(16, (uint8_t*) bf, diskNum + 'A');
	if (res) return false;
	if (bf[1] != 'C') return false;
	if (bf[2] != 'D') return false;
	if (bf[3] != '0') return false;
	if (bf[4] != '0') return false;
	if (bf[5] != '1') return false;

	int status = init_percd(diskNum + 'A');
	if (status == -1) {
		return false;
	}

	return true;
}

char iso9660Owner = 0;

FileStatus ISO9660::open(const char* __fn, void** ptr, FileOpenMode mode)
{
	if (__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	if (mode != FileOpenMode::Read) {
		return FileStatus::WriteProtect;
	}

	if (iso9660Owner != __fn[0]) {
		int status = init_percd(__fn[0]);
		if (status == -1) {
			return FileStatus::NoFilesystem;
		}

		if (iso9660Owner) {
			KePanic("CD OWNER CHANGE");
		}
		iso9660Owner = __fn[0];
	}
	init_percd(iso9660Owner);

	int fd = iso_open(__fn + 3, 0);

	if (fd == -1) {
		return FileStatus::Failure;
	}

	*ptr = (void*)(fd + 100);
	return FileStatus::Success;
}

FileStatus ISO9660::read(void* ptr, size_t bytes, void* bf, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;
	
	int64_t br = iso_read(((int) ptr) - 100, bf, bytes);
	*bytesRead = br;

	if (br == 0) {
		return FileStatus::Failure;
	}

	return FileStatus::Success;
}

bool ISO9660::exists(const char* file)
{
	KePanic("ISO9660::exists UNIMPLEMENTED");

	return false;
}

FileStatus ISO9660::seek(void* ptr, uint64_t offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	uint64_t pos = iso_seek(((int) ptr) - 100, offset, 0);

	if (pos == offset) {
		return FileStatus::Success;
	}

	return FileStatus::Failure;
}

FileStatus ISO9660::tell(void* ptr, uint64_t* offset)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (offset == nullptr) return FileStatus::InvalidArgument;

	uint64_t pos = iso_tell(((int) ptr) - 100);
	*offset = pos;

	return FileStatus::Success;
}

char* ISO9660::getName()
{
	return (char*) "ISO 9660 Filesystem Driver";
}

FileStatus ISO9660::stat(void* ptr, uint64_t* size)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;

	size_t sz = iso_total(((int) ptr) - 100);
	*size = sz;

	return FileStatus::Success;
}

FileStatus ISO9660::stat(const char* path, uint64_t* size, bool* directory)
{
	if (path == nullptr) return FileStatus::InvalidArgument;
	if (size == nullptr) return FileStatus::InvalidArgument;
	if (directory == nullptr) return FileStatus::InvalidArgument;

	*directory = 0;
	*size = 0;

	if (iso9660Owner != path[0]) {
		int status = init_percd(path[0]);
		if (status == -1) {
			return FileStatus::NoFilesystem;
		}

		if (iso9660Owner) {
			KePanic("CD OWNER CHANGE");
		}
		iso9660Owner = path[0];
	}

	int fd = iso_open(path + 3, 0);
	if (fd == -1) {
		fd = iso_open(path + 3, 1);
		*directory = 1;
		return FileStatus::Success;
	}

	if (fd == -1) {
		return FileStatus::NotExist;
	}

	*size = iso_total(fd);
	iso_close(fd);

	return FileStatus::Success;
}

FileStatus ISO9660::close(void* ptr)
{
	if (ptr == nullptr) return FileStatus::InvalidArgument;

	iso_close(((int) ptr) - 100);

	return FileStatus::Success;
}

FileStatus ISO9660::openDir(const char* __fn, void** ptr)
{
	if(__fn == nullptr || ptr == nullptr) return FileStatus::InvalidArgument;

	if (iso9660Owner != __fn[0]) {
		int status = init_percd(__fn[0]);
		if (status == -1) {
			return FileStatus::NoFilesystem;
		}

		if (iso9660Owner) {
			KePanic("CD OWNER CHANGE");
		}
		iso9660Owner = __fn[0];
	}
	init_percd(iso9660Owner);

	int fd = iso_open(__fn + 3, 1);

	if (fd == -1) {
		return FileStatus::Failure;
	}

	*ptr = (void*) (fd + 100);
	return FileStatus::Success;
}

FileStatus ISO9660::readDir(void* ptr, size_t bytes, void* where, int* bytesRead)
{
	if (ptr == nullptr || bytesRead == nullptr) return FileStatus::InvalidArgument;

	struct dirent dent;

	struct direntX* ddd = iso_readdir(((int)ptr)-100);
	if (!ddd) {
		memset(where, 0, sizeof(dent));
		return FileStatus::Failure;
	}

	dent.d_ino = 0;
	dent.d_namlen = strlen(ddd->d_name);
	dent.d_type = ddd->d_reclen == -1 ? DT_DIR : DT_REG;
	strcpy(dent.d_name, ddd->d_name);

	memcpy(where, &dent, bytes);
	*bytesRead = sizeof(dent);
	return FileStatus::Success;
}

FileStatus ISO9660::closeDir(void* ptr)
{
	return close(ptr);
}

FileStatus ISO9660::chfatattr(const char* path, uint8_t andMask, uint8_t orFlags)
{
	return FileStatus::Failure;
}

FileStatus ISO9660::unlink(const char* file)
{
	return FileStatus::Failure;
}

FileStatus ISO9660::write(void* ptr, size_t bytes, void* where, int* bytesWritten)
{
	return FileStatus::WriteProtect;
}

FileStatus ISO9660::rename(const char* old, const char* _new)
{	
	return FileStatus::Failure;
}

FileStatus ISO9660::mkdir(const char* file)
{
	return FileStatus::Failure;
}
