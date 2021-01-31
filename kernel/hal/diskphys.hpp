#ifndef _PHYSDISK_HPP_
#define _PHYSDISK_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "fs/vfs.hpp"

enum class DiskError : int
{
	Success,
	Failure,
	NotReady,
	WriteProtected,
	BadSectorCount,
	BadLBA,
	BadBuffer,
	ParitionBoundError,
};

class VCache;
class LogicalDisk;

class PhysicalDisk : public Device
{
private:

protected:
	friend class VCache;
	friend class LogicalDisk;
	VCache* cache;

public:		
	int sectorSize;
	uint64_t sizeInKBs;

	bool removable = false;
	bool floppy = false;

	PhysicalDisk(const char* name, int sectorSize);
	void startCache();
	virtual ~PhysicalDisk();

	virtual int read(uint64_t lba, int count, void* ptr) = 0;			//Perform a read command
	virtual int write(uint64_t lba, int count, void* ptr) = 0;			//Perform a write command
};

#endif