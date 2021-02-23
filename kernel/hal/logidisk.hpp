#ifndef _LOGIDISK_HPP_
#define _LOGIDISK_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include "fs/vfs.hpp"
#include "dbg/kconsole.hpp"

#define MAX_DISK_COUNT 26

class Filesystem;
class PhysicalDisk;

class LogicalDisk : public Device
{
private:

protected:
	uint64_t partitionLBA;
	uint64_t partitionLength;

	char mounted = 0;

public:		
	PhysicalDisk* physDisk;

	Filesystem* fs;

	uint64_t absoluteToRelative(uint64_t abs);
	uint64_t relativeToAbsolute(uint64_t rel);

	LogicalDisk(const char* name, PhysicalDisk* phys, uint64_t lowLBA, uint64_t sectors);
	virtual ~LogicalDisk();
	
	char assignDriveLetter();
	void unassignDriveLetter();

	bool mount();
	void unmount();

	int open(int a, int b, void* c);
	int close(int a, int b, void* c);

	int read(uint64_t lba, int count, void* ptr);
	int write(uint64_t lba, int count, void* ptr);
};

extern LogicalDisk* disks[MAX_DISK_COUNT];

void detectPartitions(PhysicalDisk* phys);

#endif