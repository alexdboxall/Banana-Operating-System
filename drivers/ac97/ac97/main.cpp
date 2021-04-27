class Device;
void start(Device* _dvl);
void begin(void* b)
{
	start((Device*) b);
}

#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/bus/pci.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

#define NAM_RESET				0x00
#define NAM_MASTER_VOL			0x02
#define NAM_MIC_VOL				0x0E
#define NAM_PCM_VOL				0x18
#define NAM_REC_SLC				0x1A
#define NAM_REC_GAIN			0x1C
#define NAM_MIC_GAIN			0x1E
#define NAM_EXT_ID				0x28
#define NAM_EXT_CTRL			0x2A
#define NAM_EXT_FRONT_RATE		0x2C

#define NABM_PCM_INPUT_BASE		0x00
#define NABM_PCM_OUTPUT_BASE	0x10
#define NABM_MIC_INPUT_BASE		0x20
#define NABM_GLOBAL_CTL			0x2C
#define NABM_GLOBAL_STS			0x30

#define NABM_OFFSET_BUFFER_DSC_ADDR			0x00
#define NABM_OFFSET_CUR_ENTRY_VAL			0x04
#define NABM_OFFSET_LAST_VALID_ENTRY		0x05
#define NABM_OFFSET_TRANSFER_STS			0x06
#define NABM_OFFSET_CUR_IDX_PROC_SAMPLES	0x08
#define NABM_OFFSET_PRCSD_ENTRY				0x0A
#define NABM_OFFSET_BUFFER_CNT				0x0B

#define GLOBAL_CTL_GLOBAL_INT_ENABLE		0x0001
#define GLOBAL_CTL_COLD_RESET				0x0002
#define GLOBAL_CTL_WARM_RESET				0x0004
#define GLOBAL_CTL_SHUTDOWN					0x0008

extern "C" {
#include "libk/string.h"
}

void start(Device* _dvl)
{
	Device* driverless = _dvl;
	Device* parent = driverless->getParent();

	AC97* dev = new AC97();
	parent->addChild(dev);
	dev->preOpenPCI(driverless->pci.info);
	dev->_open(0, 0, nullptr);
}

AC97::AC97(): SoundDevice("AC97 Audio Device")
{

}

AC97::~AC97()
{

}

void AC97::setVolume(int leftPercent, int rightPercent)
{
	int left = leftPercent * 10 / 32;
	int right = rightPercent * 10 / 32;

	uint16_t vol = left | (right << 8);
	thePCI->writeBAR16(nam, vol, NAM_MASTER_VOL);
	thePCI->writeBAR16(nam, 0x0, NAM_PCM_VOL);
}

int AC97::open(int a, int b, void* c)
{
	return 0;
}

void ac97IRQHandler(regs* r, void* context)
{
	AC97* ac97 = (AC97*) context;
	ac97->handleIRQ();
}

void AC97::handleIRQ()
{
	kprintf("GOT AC97 IRQ.\n");

	uint8_t pi, po, mc;

	pi = thePCI->readBAR8(nabm, 0x06) & 0x1C;
	po = thePCI->readBAR8(nabm, 0x16) & 0x1C;
	mc = thePCI->readBAR8(nabm, 0x26) & 0x1C;

	kprintf("pi 0x%X, po 0x%X, mc 0x%X\n", pi, po, mc);

	thePCI->writeBAR8(nabm, pi, 0x06);
	thePCI->writeBAR8(nabm, po, 0x16);
	thePCI->writeBAR8(nabm, mc, 0x26);
}

int AC97::_open(int a, int b, void* c)
{
	nam = pci.info.bar[0];
	nabm = pci.info.bar[1];

	if (nam & 1) {
		ports[noPorts].rangeStart = nam & ~3;
		ports[noPorts].rangeLength = 0x40;
		ports[noPorts++].width = 0;
	}
	if (nabm & 1) {
		ports[noPorts].rangeStart = nabm & ~3;
		ports[noPorts].rangeLength = 0x40;
		ports[noPorts++].width = 0;
	}

	//set bit 0 and bit 2 in the PCI command register

	uint16_t w = thePCI->pciReadWord(pci.info.bus, pci.info.slot, pci.info.function, 0x4);
	thePCI->pciWriteWord(pci.info.bus, pci.info.slot, pci.info.function, 0x4, w | 5);

	thePCI->writeBAR32(nabm, 0x3, NABM_GLOBAL_CTL);
	thePCI->writeBAR16(nam, 0x55AA, NAM_RESET);

	uint32_t capabilities = thePCI->readBAR32(nabm, NABM_GLOBAL_STS);
	kprintf("AC97 channels: %d\n", 2 + 2 * ((capabilities >> 20) & 3));
	if (((capabilities >> 22) & 3) == 1) {
		kprintf("20 bit sound supported.\n");
	}

	//reset output channel
	uint8_t val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	kprintf("0x1B valA = 0x%X\n", val);
	val |= 0x2;
	kprintf("0x1B valB = 0x%X\n", val);
	thePCI->writeBAR8(nabm, val, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	nanoSleep(1000 * 1000 * 250);
	if (thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT) & 2) {
		kprintf("Bit could not be cleared.\n");
	}

	setVolume(15, 50);

	//write physical address of BDL
	uint32_t bdlPhysAddr = Phys::allocateContiguousPages(48);		//dummy data
	uint32_t bdlVirtAddr = Virt::allocateKernelVirtualPages(48);
	Virt::getAKernelVAS()->mapRange(bdlPhysAddr, bdlVirtAddr, 48, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);
	kprintf("phys addr = 0x%X\n", bdlPhysAddr);
	kprintf("virt addr = 0x%X\n", bdlVirtAddr);
	uint8_t lastValidEntry = 0;

	uint8_t* test = (uint8_t*) bdlVirtAddr;
	*test++ = ((bdlPhysAddr + 0x8000) >> 0) & 0xFF;
	*test++ = ((bdlPhysAddr + 0x8000) >> 8) & 0xFF;
	*test++ = ((bdlPhysAddr + 0x8000) >> 16) & 0xFF;
	*test++ = ((bdlPhysAddr + 0x8000) >> 24) & 0xFF;
	*test++ = 0x00;
	*test++ = 0x80;
	*test++ = 0;
	*test++ = 0x80;

	uint16_t* test2 = (uint16_t*) (bdlVirtAddr + 0x100);
	for (int i = 0; i < 0x8000 / 2 / 20; ++i) {
		for (int j = 0; j < 20; ++j) *test2++ = 0x0;
		for (int j = 0; j < 20; ++j) *test2++ = 0x3333;
	}

	thePCI->writeBAR32(nabm, bdlPhysAddr, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_DSC_ADDR);
	thePCI->writeBAR8(nabm, lastValidEntry, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);

	interrupt = addIRQHandler(pci.info.interrrupt, ac97IRQHandler, true, (void*) this);

	//start transfer
	val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	kprintf("0x1B valC = 0x%X\n", val);
	kprintf("0x1B valD = 0x%X\n", val | 0x1);
	thePCI->writeBAR8(nabm, val | 0x1, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);

	kprintf("interrupt = %d\n", pci.info.interrrupt);
	kprintf("intPIN    = %d\n", pci.info.intPIN);

	return 0;
}

int AC97::close(int a, int b, void* c)
{
	return 0;
}


void AC97::beginPlayback(int sampleRate, int bits)
{

}

int AC97::getNumHwChannels()
{
	return 2;
}

void AC97::stopPlayback()
{

}