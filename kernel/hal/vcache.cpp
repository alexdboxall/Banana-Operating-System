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

#define WRITE_BUFFER_MAX_SECTORS	16

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

	writeCacheValid = false;
	writeCacheBuffer = (uint8_t*) malloc(d->sectorSize * WRITE_BUFFER_MAX_SECTORS);
}

VCache::~VCache()
{
	kprintf("VCACHE CLOSE!\n");
	if (writeCacheValid) {
		writeWriteBuffer();
	}
	free(writeCacheBuffer);
}

/*
uint64_t writeCacheLBA = 0;
int writeCacheSectors = 0;
uint8_t* writeCacheBuffer;
bool writeCacheValid = false;
*/

void VCache::writeWriteBuffer()
{
	disk->write(writeCacheLBA, writeCacheSectors, writeCacheBuffer);
	kprintf("vcache writing %d sectors\n", writeCacheSectors);

	writeCacheLBA = 0;
	writeCacheValid = false;
	writeCacheSectors = 0;
}

int VCache::write(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();

	if (writeCacheValid && lba == writeCacheLBA + ((uint64_t) writeCacheSectors) && count == 1) {
		//add to cache
		kprintf("Adding to VCACHE WRITE. lba = %d, count = %d\n", (int) lba, count);
		memcpy(writeCacheBuffer + writeCacheSectors * disk->sectorSize, ptr, disk->sectorSize);
		++writeCacheSectors;

		kprintf("%d sectors cached.\n", writeCacheSectors);

		//write if limit reached
		if (writeCacheSectors == WRITE_BUFFER_MAX_SECTORS) {
			writeWriteBuffer();
		}

	} else {
		//write existing cache
		if (writeCacheValid) {
			writeWriteBuffer();
		}

		//if it will fit in the cache, start a new cache
		if (count < WRITE_BUFFER_MAX_SECTORS) {
			writeCacheLBA = lba;
			writeCacheSectors = count;
			writeCacheValid = true;
			memcpy(writeCacheBuffer, ptr, disk->sectorSize);

			kprintf("Adding to VCACHE WRITE (2). lba = %d, count = %d\n", (int) lba, count);
			kprintf("%d sectors cached.\n", writeCacheSectors);

		//otherwise, just write it
		} else {
			kprintf("DIRECT WRITE TO LBA %d, count = %d\n", (int) lba, count);
			disk->write(lba, count, ptr);
		}
	}

	mutex->release();
	return 0;
}

int VCache::read(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();

	//NOTE: this is very inefficient, we should check if it is in the cache
	//		and if it is, just memcpy the data
	if (writeCacheValid) {
		writeWriteBuffer();
	}

	disk->read(lba, count, ptr);
	mutex->release();
	return 0;
}