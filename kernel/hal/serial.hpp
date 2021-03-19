#ifndef _SERIAL_PORT_HPP_
#define _SERIAL_PORT_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class Serial: public Device
{
private:

protected:

public:
	Serial(const char* name);
	virtual ~Serial();

	virtual void setBaud(int baud) = 0;
	virtual int getBaud() = 0;
	virtual bool readyToRead() = 0;
	virtual bool readyToWrite() = 0;
	virtual uint8_t read() = 0;
	virtual void write(uint8_t) = 0;
};

#endif