#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <stdint.h>

#include "hal/device.hpp"
#include "hal/nic.hpp"

class RTL8139: public NIC
{
private:

protected:
	friend void rtl8139IRQHandler(regs* r, void* ctxt);

	uint32_t base;
	size_t rxBufferPhys;
	size_t rxBufferVirt;
	uint64_t mac;

	int transmitCycle = 0;
	void reset();

public:
	RTL8139();

	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands

	int open_(int, int, void*);			//Opens the device (init code).

	virtual uint64_t getMAC();
	virtual int write(int len, uint8_t* data, int* br);
};

#endif