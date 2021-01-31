#ifndef _DSIKCTRL_HPP_
#define _DSIKCTRL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class HardDiskController: public Device
{
private:

protected:

public:
	HardDiskController(const char* name);
	virtual ~HardDiskController();
};

#endif