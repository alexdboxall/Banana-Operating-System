#ifndef _BIOS_HPP_
#define _BIOS_HPP_

#include <stdint.h>

#include "hal/device.hpp"

class BIOS: public Device
{
private:

protected:

public:
	BIOS();

	virtual int open(int, int, void*);
	virtual int close(int, int, void*);
};

#endif