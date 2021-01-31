#ifndef _BUS_HPP_
#define _BUS_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class Bus : public Device
{
private:

protected:

public:
	Bus(const char* name);
	virtual ~Bus();
};

#endif