
#ifndef _SATAPI3_HPP_
#define _SATAPI3_HPP_

#include <stdint.h>
#include "hal/diskphys.hpp"
#include "hw/diskctrl/satabus.hpp"
#include "hal/partition.hpp"

class SATAPI: public PhysicalDisk
{
private:

protected:
	int deviceNum;
	SATABus* sbus;
	
	bool diskIn;

	void diskRemoved();
	void diskInserted();

public:
	SATAPI();

	size_t sataPhysAddr;
	size_t sataVirtAddr;
	
	int sendPacket(uint8_t* packet, int maxTransferSize, uint64_t lba, uint16_t* data, int count);

	int open(int channel, int drive, void* ide);
	int read(uint64_t, int, void*);	
	int write(uint64_t, int, void*);
	int close(int, int, void*);

	void detectMedia();
	void eject();
};

#endif