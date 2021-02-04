#include "core/common.hpp"
#include "core/physmgr.hpp"
#include "hal/vcache.hpp"
#include "hal/bus.hpp"
#include "hal/diskphys.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

VCache::VCache(PhysicalDisk* d)
{
	mutex = new Mutex();
	disk = d;

	//can be configured here, but should NOT be changed afterwards
	//this MUST be a power of 2, and it should not be 1 (as write buffering may not work correctly)
	blockSizeInSectors = 2;

	//per disk settings, should NOT be changed afterwards
	diskSectorSize = d->sectorSize;
	diskSizeKBs = d->sizeInKBs;

	sectorsPerCache = (diskSizeKBs * 1024 / diskSectorSize) / VCACHE_LINKED_LIST_COUNT;
}

VCache::~VCache()
{

}

int VCache::write(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();
	disk->write(lba, count, ptr);
	mutex->release();
	return 0;
}

int VCache::read(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();
	disk->read(lba, count, ptr);
	mutex->release();
	return 0;
}