
#ifndef _PS2PORT_HPP_
#define _PS2PORT_HPP_

#include <stdint.h>
#include "hal/bus.hpp"
#include "hw/bus/ps2.hpp"

/*
class PS2Port: public Bus
{
private:

protected:
	int portNum;
	PS2* controller;

public:
	PS2Port();

	int open(int prtNum, int, void* ctrl);
	int close(int, int, void*);

	void detect();

	bool deviceWrite(uint8_t command);
	uint8_t deviceRead();
};
*/

#endif