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

/*
uint64_t writeCacheLBA = 0;
int writeCacheSectors = 0;
uint8_t* writeCacheBuffer;
bool writeCacheValid = false;
*/

void VCache::invalidateReadBuffer()
{
	if (READ_BUFFER_BLOCK_SIZE >= 8) {
		READ_BUFFER_BLOCK_SIZE /= 2;
	}
	kprintf("DECREASING BLOCK SIZE TO %d\n", READ_BUFFER_BLOCK_SIZE);
	kprintf("   ** invalidating the read buffer.\n");
	readCacheValid = false;
	increaseNextTime = false;
	hitBlockEnd = false;
}

void VCache::writeWriteBuffer()
{
	disk->write(writeCacheLBA, writeCacheSectors, writeCacheBuffer);

	writeCacheLBA = 0;
	writeCacheValid = false;
	writeCacheSectors = 0;
}

int VCache::write(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();

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
			disk->write(lba, count, ptr);
		}
	}

	mutex->release();
	return 0;
}

uint8_t testBuffer[512 * READ_BUFFER_MAX_SECTORS];

int VCache::read(uint64_t lba, int count, void* ptr)
{
	mutex->acquire();

	bool clearBlockEnd = true;

	//NOTE: this is very inefficient, we should check if it is in the cache
	//		and if it is, just memcpy the data
	if (writeCacheValid) {
		writeWriteBuffer();
	}

	kprintf("    VCACHE::READ 0x%X - ", (uint32_t) lba);
	if (count == 1 && !disk->removable) {
		if (!(readCacheValid && (lba & ~(READ_BUFFER_BLOCK_SIZE - 1)) == readCacheLBA)) {
			kprintf("caching now... ");
			readCacheValid = true;
			readCacheLBA = lba & ~(READ_BUFFER_BLOCK_SIZE - 1);

			//first in block AND you hit the last in block last time
			if ((lba & (READ_BUFFER_BLOCK_SIZE - 1)) == 0 && hitBlockEnd) {
				if (increaseNextTime) {
					increaseNextTime = false;

					READ_BUFFER_BLOCK_SIZE *= 2;
					if (READ_BUFFER_BLOCK_SIZE >= READ_BUFFER_MAX_SECTORS) {
						READ_BUFFER_BLOCK_SIZE = READ_BUFFER_MAX_SECTORS;
					}
					kprintf("INCREASING BLOCK SIZE TO %d\n", READ_BUFFER_BLOCK_SIZE);
					hitBlockEnd = false;

				} else {
					increaseNextTime = true;

				}
			}

			//used the last in block?
			if (((lba - 1) & (READ_BUFFER_BLOCK_SIZE - 1)) == 0) {
				hitBlockEnd = true;
				clearBlockEnd = false;
			}

			//both disk drivers somehow fail the multicount reads
			//SATA does it subtly
			//ATA does it blatantly

			disk->read((lba & ~(READ_BUFFER_BLOCK_SIZE - 1)), READ_BUFFER_BLOCK_SIZE, readCacheBuffer /*testBuffer*/);
			//memcpy((void*) readCacheBuffer, (const void*) testBuffer, READ_BUFFER_BLOCK_SIZE * 512);
		}

		kprintf("from cache (offset = 0x%X)\n", (lba - readCacheLBA) * disk->sectorSize);
		memcpy(ptr, readCacheBuffer + (lba & (READ_BUFFER_BLOCK_SIZE - 1)) * disk->sectorSize, disk->sectorSize);

	} else {
		kprintf("uncached (%d).\n", count);
		invalidateReadBuffer();
		disk->read(lba, count, ptr);
	}

	if (clearBlockEnd) {
		hitBlockEnd = false;
	}

	mutex->release();
	return 0;
}