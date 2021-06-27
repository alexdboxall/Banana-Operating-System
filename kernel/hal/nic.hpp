#ifndef _NIC_HPP
#define _NIC_HPP

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

#define NS_SUCCESS			0
#define NS_UNIMPLEMENTED	1
#define NS_FAILURE			2
#define NS_HARDFAIL			3

class NIC: public Device
{
private:

protected:

public:
	NIC(const char* name);
	virtual ~NIC();

	virtual uint64_t getMAC();
	virtual int havePackets();
	virtual int write(int len, uint8_t* data, int* br);
	virtual int read(int len, uint8_t* data, int* br);
};

#endif