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
#include "hal/sound/sndport.hpp"
#include "hal/sound/sndcard.hpp"

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

int16_t buf[4096];

void playThread(void* __);
void start(Device* _dvl)
{
	Device* driverless = _dvl;
	Device* parent = driverless->getParent();

	AC97* dev = new AC97();
	parent->addChild(dev);
	dev->preOpenPCI(driverless->pci.info);
	dev->_open(0, 0, nullptr);

	kernelProcess->createThread(playThread, dev, 30);

}

void playThread(void* __)
{
	unlockScheduler();

	SoundCard* card = (SoundCard*) __;

	SoundPort* port = new SoundPort(8000, 16, 2, 65536 * 6);
	bool started = false;

	File* f = new File("C:/fuguestereo.wav", kernelProcess);
	f->open(FileOpenMode::Read);

	while (1) {
		int bytesRead = 0;
		FileStatus st = f->read(4096 * 2, buf, &bytesRead);

		if (bytesRead == 0 || st != FileStatus::Success) {
			kprintf("SONG SHOULD BE DONE.\n");
			break;
		}

		kprintf("buffer has %d samples in it.\n", port->getBufferUsed());

		while (port->getBufferUsed() + bytesRead * 3 >= port->getBufferSize()) {
			if (!started) {
				card->configureRates(8000, 16, 2);
				card->addChannel(port);
				port->unpause();
				card->beginPlayback();
				started = true;
			}
			lockScheduler();
			schedule();
			unlockScheduler();
		}

		port->buffer16(buf, bytesRead / 2);
	}

	terminateTask(0);
}

AC97::AC97(): SoundCard("Intel AC'97 Audio Device")
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

int handles = 0;
void AC97::handleIRQ()
{
	kprintf("AC97 IRQ.\n");
	uint8_t civ = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_CUR_ENTRY_VAL);
	uint8_t lvi = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);
	lvi = lvi;
	kprintf("currently on '%d'. civ - 1 = %d, civ + 1 = %d\n", civ, civ - 1, ((civ + 1) % 3));
	kprintf("lvi =  %d\n", lvi);
	thePCI->writeBAR8(nabm, lvi, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);

	/*int samplesGot = getAudio(65534, tempBuffer, oBuffer);
	kprintf("samples got = %d\n", samplesGot);
	int16_t* dma = (int16_t*) buffVirt[((civ + 2) % 3)];
	kprintf("actually writing data to buffer number %d\n", ((civ + 2) % 3));
	++v;
	++v;
	*v = (((civ + 2) % 3) + '0') | 0xF000;
	floatTo16(oBuffer, dma, samplesGot);
	kprintf("STATUS = 0x%X\n", thePCI->readBAR16(nabm, 0x16));*/

	int16_t* dma = (int16_t*) buffVirt[((civ + 1) % 3)];
	int sgot = getSamples16(65534, dma);
	kprintf("we got %d samples to 0x%X\n", sgot, dma);

	thePCI->writeBAR16(nabm, 0x1C, 0x16);
	++handles;
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

	//allocate BDL
	bdlPhys = Phys::allocateContiguousPages(1);
	bdlVirt = Virt::allocateKernelVirtualPages(1);

	kprintf("bdl at phys 0x%X and virt 0x%X\n", bdlPhys, bdlVirt);
	Virt::getAKernelVAS()->mapRange(bdlPhys, bdlVirt, 1, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);

	//allocate buffers
	for (int i = 0; i < 3; ++i) {
		int pages = 65536 * 2 / 4096;

		buffPhys[i] = Phys::allocateContiguousPages(pages);
		buffVirt[i] = Virt::allocateKernelVirtualPages(pages);
		kprintf("buffer at phys 0x%X and virt 0x%X\n", buffPhys[i], buffVirt[i]);
		Virt::getAKernelVAS()->mapRange(buffPhys[i], buffVirt[i], pages, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);

		memset((void*) buffVirt[i], 0, pages * 4096);
	}

	//fill BDL
	uint32_t* ptr = (uint32_t*) bdlVirt;
	ptr[0] = buffPhys[0];
	ptr[1] = 0x80000000U | 0x8000U;
	ptr[2] = buffPhys[1];
	ptr[3] = 0x80000000U | 0x8000U;
	ptr[4] = buffPhys[2];
	ptr[5] = 0x80000000U | 0x8000U;

	//fill buffers
	for (int i = 0; i < 3; ++i) {
		uint16_t* data = (uint16_t*) buffVirt[i];
		for (int j = 0; j < 65535; ++j) {
			*data++ = (j >> (4 + i)) & 1 ? 0x2222 : 0x0000;
		}
	}

	//write physical address of BDL
	thePCI->writeBAR32(nabm, bdlPhys, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_DSC_ADDR);
	thePCI->writeBAR8(nabm, 3, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_LAST_VALID_ENTRY);

	kprintf("interrupt = %d\n", pci.info.interrrupt);
	interrupt = addIRQHandler(pci.info.interrrupt, ac97IRQHandler, true, (void*) this);

	return 0;
}

int AC97::close(int a, int b, void* c)
{
	return 0;
}


void AC97::beginPlayback()
{
	kprintf("beginning playback...\n");

	//set sample rate
	setSampleRate(currentSampleRate);

	if (currentBits != 16) {
		panic("AC97::beginPlayback bits != 16 NOT SUPPORTED!");
	}

	if (currentChannels != 2) {
		panic("AC97::beginPlayback channels != 2 NOT SUPPORTED!");
	}

	//start transfer
	uint8_t val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	val = (val & ~0x1F) | 0x1D;
	kprintf("VAL = 0x%X\n", val);
	thePCI->writeBAR8(nabm, val, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);

	playing = true;
}

void AC97::stopPlayback()
{
	uint8_t val = thePCI->readBAR8(nabm, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);
	thePCI->writeBAR8(nabm, val & ~0x1F, NABM_PCM_OUTPUT_BASE + NABM_OFFSET_BUFFER_CNT);

	playing = false;
}