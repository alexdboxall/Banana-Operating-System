
#ifndef _ATAPI_HPP_
#define _ATAPI_HPP_

#include <stdint.h>
#include "hal/diskphys.hpp"
#include "hw/diskctrl/ide.hpp"

class ATAPI: public PhysicalDisk
{
private:

protected:

	IDE* ide;
	int channel;
	int drive;

	int ideDeviceNum;

	bool diskIn;

	int sendPacket(uint8_t* packet, int maxTransferSize, bool write, uint16_t* data, int numTransfers);
	bool readyForCommand();

	void diskRemoved();
	void diskInserted();

	LogicalDisk* logi;

public:
	ATAPI();

	virtual int open(int channel, int drive, void* ide);
	virtual int read(uint64_t, int, void*);	
	virtual int write(uint64_t, int, void*);
	virtual int close(int, int, void*);

	void detectMedia();

	int eject();
};

#endif