#ifndef _VCACHE_HPP_
#define _VCACHE_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "thr/prcssthr.hpp"
#include "coreobjs/linkedlist.hpp"

class PhysicalDisk;

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

	uint64_t writeCacheLBA = 0;
	int writeCacheSectors = 0;
	uint8_t* writeCacheBuffer;
	bool writeCacheValid = false;

	void writeWriteBuffer();		//what a stupid name

public:	
	VCache(PhysicalDisk* disk);
	virtual ~VCache();

	int read(uint64_t lba, int count, void* ptr);
	int write(uint64_t lba, int count, void* ptr);
};

#endif