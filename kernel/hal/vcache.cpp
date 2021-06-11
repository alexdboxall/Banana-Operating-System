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

//must be a power of 2
#define READ_BUFFER_MAX_SECTORS 16

#define WRITE_BUFFER_MAX_SECTORS 64

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

	readCacheValid = false;
	readCacheBuffer = (uint8_t*) malloc(d->sectorSize * READ_BUFFER_MAX_SECTORS + 4096);
	READ_BUFFER_BLOCK_SIZE = 4;

	writeCacheValid = false;
	writeCacheBuffer = (uint8_t*) malloc(d->sectorSize * WRITE_BUFFER_MAX_SECTORS);
}

VCache::~VCache()
{
	if (writeCacheValid) {
		writeWriteBuffer();
	}
	free(writeCacheBuffer);
	free(readCacheBuffer);
}

void VCache::invalidateReadBuffer()
{
	readCacheValid = false;
	increaseNextTime = false;
	hitBlockEnd = false;
}

void VCache::writeWriteBuffer()
{
	if (writeCacheValid) {
		disk->write(writeCacheLBA, writeCacheSectors, writeCacheBuffer);
	}

	writeCacheLBA = 0;
	writeCacheValid = false;
	writeCacheSectors = 0;
}

int VCache::write(uint64_t lba, int count, void* ptr)
{
	///TODO:	get all touchy-feely AND LOCK THE MEMORY (aka. ensure the buffer is in actual RAM, not the swapfile)

	for (int i = 0; i < count; ++i) {
		unsigned int* abc = (unsigned int*) (((uint8_t*) ptr) + i * disk->sectorSize);
		asm volatile ("" : "=m" (*abc) : "r" (*abc));
	}

	//mutex->acquire();

	if (readCacheValid) {
		invalidateReadBuffer();
	}

	if (writeCacheValid && lba == writeCacheLBA + ((uint64_t) writeCacheSectors) && count == 1) {
		//add to cache
		memcpy(writeCacheBuffer + writeCacheSectors * disk->sectorSize, ptr, disk->sectorSize);
		++writeCacheSectors;

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

		//otherwise, just write it
		} else {
			return disk->write(lba, count, ptr);
		}
	}

	//mutex->release();
	return 0;
}

int VCache::read(uint64_t lba, int count, void* ptr)
{	
	///TODO:	get all touchy-feely AND LOCK THE MEMORY (aka. ensure the buffer is in actual RAM, not the swapfile)

	//mutex->acquire();

	//NOTE: this is very inefficient, we should check if it is in the cache
	//		and if it is, just memcpy the data
	if (writeCacheValid) {
		writeWriteBuffer();
	}

	/*if (count == 1 && !disk->removable) {
		if (!(readCacheValid && (lba & ~(READ_BUFFER_BLOCK_SIZE - 1)) == readCacheLBA)) {

			readCacheValid = true;
			readCacheLBA = lba & ~(READ_BUFFER_BLOCK_SIZE - 1);

			//both disk drivers somehow fail the multicount reads
			//SATA does it subtly
			//ATA does it blatantly

			int retV = disk->read((lba & ~(READ_BUFFER_BLOCK_SIZE - 1)), READ_BUFFER_BLOCK_SIZE, readCacheBuffer);
			if (retV) return retV;
		}

		memcpy(ptr, readCacheBuffer + (lba & (READ_BUFFER_BLOCK_SIZE - 1)) * disk->sectorSize, disk->sectorSize);
		return 0;

	} else {*/
		invalidateReadBuffer();
		memset(ptr, 0, disk->sectorSize);
		return disk->read(lba, count, ptr);
	/*}*/

	//mutex->release();
	return 0;
}