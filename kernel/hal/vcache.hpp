#ifndef _VCACHE_HPP_
#define _VCACHE_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "core/prcssthr.hpp"
#include "coreobjs/linkedlist.hpp"

class PhysicalDisk;

#define VCACHE_LINKED_LIST_COUNT 1024
#define VCACHE_WRITE_BUFFER_SECTOR_COUNT 64

//how many pointers to VCACHES are stored in an array so that they can very quickly be purged if needed
//if more vcaches than this number, the ones past this number won't be purged
//memory cost on 32 bit: VCACHE_QUICK_PURGE_ARRAY_MAX * 4 bytes
#define VCACHE_PURGE_ARRAY_MAX 256

class VCache
{
private:

protected:
	friend void vcacheDispatcher(void* context);

	Mutex* mutex;

	PhysicalDisk* disk;

	int diskSectorSize = 512;
	int blockSizeInSectors = 4;

	uint64_t diskSizeKBs = 64;
	int sectorsPerCache = 0;

public:	
	VCache(PhysicalDisk* disk);
	virtual ~VCache();

	int read(uint64_t lba, int count, void* ptr);
	int write(uint64_t lba, int count, void* ptr);
};

#endif