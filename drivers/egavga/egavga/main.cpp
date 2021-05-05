#include <stdint.h>

class Device;
void start(Device* parent);
void begin(Device* s)
{
	start(s);
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

#pragma GCC optimize ("Og")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void start(Device* parent)
{
	EGAVGA* dev = new EGAVGA();
	parent->addChild(dev);

	dev->init();
}

EGAVGA::EGAVGA(): Video ("EGA / VGA Compatible Video Card")
{
	//claim ports
	ports[noPorts].rangeStart = 0x3B0;
	ports[noPorts].rangeLength = 0x30;
	ports[noPorts++].width = 0;
}

int EGAVGA::open(int, int, void*)
{
	return 0;
}

int EGAVGA::close(int, int, void*)
{
	return 0;
}

uint8_t EGAVGA::vinb(uint16_t port)
{
	uint8_t v = inb(port);
	asm volatile ("outb %%al, $0x80" : : "a"(0));
	asm volatile ("outb %%al, $0x80" : : "a"(0));
	return v;
}

void EGAVGA::voutb(uint16_t port, uint8_t val)
{
	outb(port, val);
	asm volatile ("outb %%al, $0x80" : : "a"(0));
	asm volatile ("outb %%al, $0x80" : : "a"(0));
}

uint8_t EGAVGA::accessSeqGfxCRTC(int offsetReg, int addrReg, int dataReg, uint8_t writeVal, bool write)
{
	int retries = 0;
retry:
	uint8_t oldAddr = vinb(addrReg);
	voutb(addrReg, (int) offsetReg);

	uint8_t oldData = vinb(dataReg);

	if (write) {
		voutb(dataReg, writeVal);
	}

	voutb(addrReg, oldAddr);

	if (write) {
		uint8_t newData = vinb(dataReg);
		if (newData != writeVal) {
			++retries;
			if (retries == 5) {
				panic("EGAVGA::accessSeqGfxCRTC 5 retries");
			}
			goto retry;
		}
	}

	return oldData;
}

uint8_t EGAVGA::readRegister(GfxReg reg)
{
	return accessSeqGfxCRTC((int) reg, REG_GFX_ADDR, REG_GFX_DATA, 0, false);
}

uint8_t EGAVGA::readRegister(SeqReg reg)
{
	return accessSeqGfxCRTC((int) reg, REG_SEQ_ADDR, REG_SEQ_DATA, 0, false);
}

uint8_t EGAVGA::accessAttrib(int offsetReg, uint8_t writeVal, bool write)
{
	lockScheduler();

	if (hasUndocumentedFlopFlopStatus && !getUndocumentedCRTC24Bit()) {
		//the flip-flop is already clear

	} else {
		//clear the flip-flop
		(void) readRegister(ExtReg::InputStatus1);
	}
	
	//get old contents
	uint8_t oldAddr = vinb(REG_ATTRIB_ADDR_READ);

	//set register we want
	voutb(REG_ATTRIB_ADDR_WRITE, offsetReg);

	//perform read/write
	uint8_t oldData = vinb(REG_ATTRIB_DATA_READ);
	if (write) {
		voutb(REG_ATTRIB_DATA_WRITE, writeVal);
	}
	voutb(REG_ATTRIB_ADDR_WRITE, oldAddr);

	//clear the flip-flop
	(void) readRegister(ExtReg::InputStatus1);

	unlockScheduler();

	return oldData;
}

uint8_t EGAVGA::readRegister(AttribReg reg)
{
	return accessAttrib((int) reg, 0, false);
}

uint8_t EGAVGA::readRegister(CRTCReg reg)
{
	return accessSeqGfxCRTC((int) reg, \
							ioAddressSelect ? REG_CRTC_ADDR_1 : REG_CRTC_ADDR_0, \
							ioAddressSelect ? REG_CRTC_DATA_1 : REG_CRTC_DATA_0, \
							0, false);
}

uint8_t EGAVGA::readRegister(ColReg reg)
{
	return 0xFE;
}

uint8_t EGAVGA::readRegister(ExtReg reg)
{
	if (reg == ExtReg::InputStatus1) {
		return vinb(gotColour ? REG_EXT_INPUT_STATUS_1_COLOUR : REG_EXT_INPUT_STATUS_1_MONO);

	} else {
		panic("EGAVGA::readRegister NOT IMPLEMENTED");
		return 0xFE;
	}
}


void EGAVGA::writeRegister(GfxReg reg, uint8_t val)
{
	accessSeqGfxCRTC((int) reg, REG_GFX_ADDR, REG_GFX_DATA, val, true);
}

void EGAVGA::writeRegister(SeqReg reg, uint8_t val)
{
	accessSeqGfxCRTC((int) reg, REG_SEQ_ADDR, REG_SEQ_DATA, val, true);
}

void EGAVGA::writeRegister(AttribReg reg, uint8_t val)
{
	accessAttrib((int) reg, val, true);
}

void EGAVGA::writeRegister(CRTCReg reg, uint8_t val)
{
	accessSeqGfxCRTC((int) reg, \
							ioAddressSelect ? REG_CRTC_ADDR_1 : REG_CRTC_ADDR_0, \
							ioAddressSelect ? REG_CRTC_DATA_1 : REG_CRTC_DATA_0, \
							val, true);
}

void EGAVGA::writeRegister(ColReg reg, uint8_t val)
{

}

void EGAVGA::writeRegister(ExtReg reg, uint8_t val)
{
	if (reg == ExtReg::InputStatus1) {
		panic("Cannot write to ExtReg::InputStatus1");

	} else {
		panic("EGAVGA::readRegister NOT IMPLEMENTED");
	}
}

bool EGAVGA::getUndocumentedCRTC24Bit()
{
	return readRegister((CRTCReg) 0x24) >> 7;
}

void EGAVGA::detectUndocumentedCRTC24()
{
	kprintf("'ello!\n");
	hasUndocumentedFlopFlopStatus = false;

	lockScheduler();

	//clear flip-flop
	(void) readRegister(ExtReg::InputStatus1);

	//verify the bit is zero
	if (getUndocumentedCRTC24Bit()) goto end;

	//flip the flip-flop
	voutb(REG_ATTRIB_ADDR_WRITE, 0x55);

	//verify the bit is one
	if (!getUndocumentedCRTC24Bit()) goto end;

	//clear the flip-flop
	(void) readRegister(ExtReg::InputStatus1);

	//verify the bit is zero
	if (getUndocumentedCRTC24Bit()) goto end;

	hasUndocumentedFlopFlopStatus = true;
	kprintf("Has undocumented bit on CRTC index 0x24.\n");

end:
	unlockScheduler();
}

void EGAVGA::init()
{
	/*
	TODO:
	bool ioAddressSelect = false;
	bool gotColour = true;
	
	*/

	detectUndocumentedCRTC24();

	
}