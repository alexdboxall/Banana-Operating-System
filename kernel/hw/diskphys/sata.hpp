
#ifndef _SATA23_HPP_
#define _SATA23_HPP_

#include <stdint.h>
#include "hal/diskphys.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hal/partition.hpp"

class SATA: public PhysicalDisk
{
private:

protected:
	int deviceNum;
	SATABus* sbus;

public:
	SATA();
	
	int access(uint64_t lba, int count, void* buffer, bool write);

	int open(int channel, int drive, void* ide);
	int read(uint64_t, int, void*);	
	int write(uint64_t, int, void*);
	int close(int, int, void*);

	virtual void powerSaving(PowerSavingLevel level) override;
};

#endif