
#ifndef _PCI_HPP_
#define _PCI_HPP_

#include <stdint.h>
#include "hal/bus.hpp"

#ifndef JUMPER32
class PCI : public Bus
{
private:

protected:

public:
	PCI();

	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands

	static char* pciDetailsToFilepath(PCIDeviceInfo pciInfo);
	void pciWriteWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t word);
	uint16_t pciReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

	uint16_t getVendorID(uint8_t bus, uint8_t slot, uint8_t function);
	uint16_t getHeaderType(uint8_t bus, uint8_t slot, uint8_t function);
	uint16_t getClassCode(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getProgIF(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getRevisionID(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getInterruptNumber(uint8_t bus, uint8_t slot, uint8_t function);
	uint32_t getBARAddress(uint8_t barNo, uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getSecondaryBus(uint8_t bus, uint8_t slot, uint8_t function);
	
	void checkBus(uint8_t bus); 
	void checkDevice(uint8_t bus, uint8_t device);
	void getDeviceData(uint8_t bus, uint8_t slot, uint8_t function); 
	void foundDevice(PCIDeviceInfo info);

	uint8_t readBAR8(uint32_t addr, int offset = 0);
	uint16_t readBAR16(uint32_t addr, int offset = 0);
	uint32_t readBAR32(uint32_t addr, int offset = 0);

	void writeBAR8(uint32_t addr, uint8_t val, int offset = 0);
	void writeBAR16(uint32_t addr, uint16_t val, int offset = 0);
	void writeBAR32(uint32_t addr, uint32_t val, int offset = 0);

	virtual void detect();						//Detect any children
};
#endif

#endif