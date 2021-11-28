
#ifndef _ATA_HPP_
#define _ATA_HPP_

#include <stdint.h>
#include "hal/diskphys.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hal/partition.hpp"

class ATA: public PhysicalDisk
{
private:

protected:

	IDE* ide;
	int channel;
	int drive;
	int ideDeviceNum;

	size_t ataPhysAddr;
	size_t ataVirtAddr;

	size_t prdtPhysAddr;
	size_t prdtVirtAddr;

	int access(uint64_t sector, int count, void* buffer, bool write);
	bool readyForCommand();
	void flush(bool lba48);

	void detectCHS();

public:
	ATA();

	int open(int channel, int drive, void* ide);
	int read(uint64_t, int, void*);	
	int write(uint64_t, int, void*);
	int close(int, int, void*);

	virtual void powerSaving(PowerSavingLevel level) override;
};

#endif