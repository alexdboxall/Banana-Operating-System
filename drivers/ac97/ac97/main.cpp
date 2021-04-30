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
#include "hal/sound/sndhw.hpp"

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

uint8_t buf[4096];
void start(Device* _dvl)
{
	Device* driverless = _dvl;
	Device* parent = driverless->getParent();

	AC97* dev = new AC97();
	parent->addChild(dev);
	dev->preOpenPCI(driverless->pci.info);
	dev->_open(0, 0, nullptr);
	return;

	SoundChannel* c = new SoundChannel(8000, 16, 90);

	File* f = new File("C:/ac97test.wav", kernelProcess);
	f->open(FileOpenMode::Read);

	bool playedYet = false;

	while (1) {
		int bytesRead = 0;
		kprintf("reading...\n");
		FileStatus st = f->read(4096, buf, &bytesRead);
		if (bytesRead == 0 || st != FileStatus::Success) {
			kprintf("SONG SHOULD BE DONE.\n");
			return;
		}
		kprintf("read...\n");

		lockScheduler();
		schedule();
		unlockScheduler();

		while (c->getBufferUsed() + bytesRead >= c->getBufferSize()) {
			sleep(1);
		}
		kprintf("A...\n");

		c->buffer8(buf, bytesRead);
		kprintf("B...\n");

		if (!playedYet) {
			dev->addChannel(c);
			kprintf("C...\n");
			//c->play();
			kprintf("D...\n");
			playedYet = true;
		}

		kprintf("E...\n");
	}
}

AC97::AC97(): SoundDevice("Intel AC'97 Audio Device")
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

uint32_t bdlPhysAddr;
uint32_t bdlVirtAddr;

float* tempBuffer = nullptr;
float* outputBuffer = nullptr;

void AC97::handleIRQ()
{
	if (tempBuffer == nullptr) {
		tempBuffer = (float*) malloc(65536);
		outputBuffer = (float*) malloc(65536);
	}

	thePCI->writeBAR16(nabm, 0x1C, 0x16);

	uint16_t index = thePCI->readBAR16(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_CUR_ENTRY_VAL);
	uint8_t civ = index & 0xFF;
	uint8_t lvi = (index >> 8);
	if (lvi == civ) {
		lvi = (civ - 1) & 0x1F;
		thePCI->writeBAR8(nabm, lvi, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);
	}

	/*kprintf("reading samples to 0x%X and 0x%X...\n", tempBuffer, outputBuffer);
	int samplesGot = getAudio(4096, tempBuffer, outputBuffer);
	kprintf("%d samples got.\n", samplesGot);

	uint16_t* dma = (uint16_t*) (bdlVirtAddr + 0x1000 + 0x8000 * 2 * 2 * ((l + 2) & 31));
	kprintf("the destination address is 0x%X\n", dma);
	floatTo16(outputBuffer, dma, samplesGot);*/
}

void AC97::setSampleRate(int hertz)
{
	thePCI->writeBAR16(nam, thePCI->readBAR16(nam, 0x2A) | 1, 0x2A);
	nanoSleep(1000 * 1000 * 10);
	thePCI->writeBAR16(nam, hertz, 0x2C);
	thePCI->writeBAR16(nam, hertz, 0x32);
	nanoSleep(1000 * 1000 * 10);
}

int AC97::_open(int a, int b, void* c)
{
	nam = pci.info.bar[0];
	nabm = pci.info.bar[1];

	//register ports
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

	//do a reset
	thePCI->writeBAR32(nabm, 0x3, NABM_GLOBAL_CTL);
	thePCI->writeBAR16(nam, 0x55AA, NAM_RESET);

	//check capabilities
	uint32_t capabilities = thePCI->readBAR32(nabm, NABM_GLOBAL_STS);
	kprintf("AC97 channels: %d\n", 2 + 2 * ((capabilities >> 20) & 3));
	if (((capabilities >> 22) & 3) == 1) {
		kprintf("20 bit sound supported.\n");
	}

	//reset output channel
	uint8_t val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	thePCI->writeBAR8(nabm, val | 2, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	nanoSleep(1000 * 1000 * 250);
	if (thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT) & 2) {
		kprintf("Bit could not be cleared.\n");
	}

	setVolume(15, 50);

	bdlPhysAddr = Phys::allocateContiguousPages(410);		//dummy data
	bdlVirtAddr = Virt::allocateKernelVirtualPages(410);
	Virt::getAKernelVAS()->mapRange(bdlPhysAddr, bdlVirtAddr, 410, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);
	uint8_t lastValidEntry = 4;

	uint8_t* test = (uint8_t*) bdlVirtAddr;
	for (int i = 0; i < 32; ++i) {
		*test++ = ((bdlPhysAddr + 0x1000 + 0x8000 * 2 * 2 * i) >> 0) & 0xFF;
		*test++ = ((bdlPhysAddr + 0x1000 + 0x8000 * 2 * 2 * i) >> 8) & 0xFF;
		*test++ = ((bdlPhysAddr + 0x1000 + 0x8000 * 2 * 2 * i) >> 16) & 0xFF;
		*test++ = ((bdlPhysAddr + 0x1000 + 0x8000 * 2 * 2 * i) >> 24) & 0xFF;
		*test++ = 0x00;
		*test++ = 0x80;
		*test++ = 0;
		*test++ = 0x80;
	}

	uint16_t* test2 = (uint16_t*) (bdlVirtAddr + 0x1000);
	uint16_t lfsr = 0;
	for (int i = 0; i < 0x8000 / 80 / 8; ++i) {
		for (int j = 0; j < 40; ++j) *test2++ = 0x0;
		for (int j = 0; j < 40; ++j) *test2++ = 0x2222;
	}
	for (int i = 0; i < 0x8000 / 80 / 8; ++i) {
		for (int j = 0; j < 20; ++j) *test2++ = 0x0;
		for (int j = 0; j < 20; ++j) *test2++ = 0x2222;
		for (int j = 0; j < 20; ++j) *test2++ = 0x0;
		for (int j = 0; j < 20; ++j) *test2++ = 0x2222;
	}
	for (int i = 0; i < 0x8000 / 80 / 8; ++i) {
		for (int j = 0; j < 40; ++j) *test2++ = 0x0;
		for (int j = 0; j < 40; ++j) *test2++ = 0x2222;
	}
	for (int i = 0; i < 0x8000 / 80 / 8; ++i) {
		for (int j = 0; j < 20; ++j) *test2++ = 0x0;
		for (int j = 0; j < 20; ++j) *test2++ = 0x2222;
		for (int j = 0; j < 20; ++j) *test2++ = 0x0;
		for (int j = 0; j < 20; ++j) *test2++ = 0x2222;
	}

	setSampleRate(8000);

	//write physical address of BDL
	thePCI->writeBAR32(nabm, bdlPhysAddr, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_DSC_ADDR);
	thePCI->writeBAR8(nabm, lastValidEntry, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);

	interrupt = addIRQHandler(pci.info.interrrupt, ac97IRQHandler, true, (void*) this);

	//start transfer
	val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	thePCI->writeBAR8(nabm, val | 0x15, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);

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