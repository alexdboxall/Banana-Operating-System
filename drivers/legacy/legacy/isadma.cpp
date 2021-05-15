
#include <stdint.h>
#include <stddef.h>

#include "isadma.hpp"

#include "core/main.hpp"
#include "hw/ports.hpp"
#include "core/physmgr.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"


#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define DMA0_ADDR			0x00
#define DMA0_COUNT			0x01
#define DMA1_ADDR			0x02
#define DMA1_COUNT			0x03
#define DMA2_ADDR			0x04
#define DMA2_COUNT			0x05
#define DMA3_ADDR			0x06
#define DMA3_COUNT			0x07

#define DMA4_ADDR			0xC0
#define DMA4_COUNT			0xC2
#define DMA5_ADDR			0xC4
#define DMA5_COUNT			0xC6
#define DMA6_ADDR			0xC8
#define DMA6_COUNT			0xCA
#define DMA7_ADDR			0xCC
#define DMA7_COUNT			0xCE

//what the hell is going on here..?
#define DMA0_PAGE			0x87
#define DMA1_PAGE			0x83
#define DMA2_PAGE			0x81
#define DMA3_PAGE			0x82
#define DMA4_PAGE			0x8F
#define DMA5_PAGE			0x8B
#define DMA6_PAGE			0x89
#define DMA7_PAGE			0x8A

#define DMA_STATUS_8		0x08
#define DMA_COMMAND_8		0x08
#define DMA_REQ_8			0x09
#define DMA_SINGLE_MASK_8	0x0A
#define DMA_MODE_8			0x0B
#define DMA_FLIP_FLOP_8		0x0C
#define DMA_INTERMEDIATE_8	0x0D
#define DMA_MASTER_RESET_8	0x0D
#define DMA_MASK_RESET_8	0x0E
#define DMA_MULTI_MASK_8	0x0F

#define DMA_STATUS_16		0xD0
#define DMA_COMMAND_16		0xD0
#define DMA_REQ_16			0xD2
#define DMA_SINGLE_MASK_16	0xD4
#define DMA_MODE_16			0xD6
#define DMA_FLIP_FLOP_16	0xD8
#define DMA_INTERMEDIATE_16	0xDA
#define DMA_MASTER_RESET_16	0xDA
#define DMA_MASK_RESET_16	0xDC
#define DMA_MULTI_MASK_16	0xDE


DMAChannel::DMAChannel(int n)
{
	//set up a few things
	num = n;
	dmaPointerToFree = 0;
	dmaPointerSize = 0;
	hasMode = false;
	startedOnce = false;
	dma16 = n >= 4;
}

DMAChannel::~DMAChannel()
{
	//free the DMA pointer if needed
	if (dmaPointerToFree) {
		Phys::freeDMA(dmaPointerToFree, dmaPointerSize);
	}
}

uint32_t DMAChannel::getAddress()
{
	return addr;
}

int DMAChannel::getChannelNum()
{
	return num;
}

char dmaLong[] = "DMA TRANSFER LENGTH TOO LONG";

void DMAChannel::setLength(uint32_t len)
{
	count = len;

	//you can have 0x10000, but no more, because we subtract 1 from it when sending
	if (len > 0x10000) {
		panic(dmaLong);
	}
}

void DMAChannel::setAddress(uint32_t a)
{
	addr = a;
}

void DMAChannel::allocateAddressAndSet(uint16_t len)
{
	//allocate the address
	dmaPointerToFree = Phys::allocateDMA(len);

	//and store things
	addr = dmaPointerToFree;
	dmaPointerSize = len;
	count = len;
}

void DMAChannel::setMode(uint8_t m)
{
	mode = m;
	hasMode = true;

	//settings will be applied when start() is called
	if (startedOnce) {
		//mask this channel so things don't change
		mask();

		//write the mode
		outb(dma16 ? DMA_MODE_16 : DMA_MODE_8, mode);

		//now the DMA will start
		unmask();
	}
}

char dmaConfused[] = "DMA IS CONFUSED";

void DMAChannel::start()
{
	uint8_t addrReg;
	uint8_t countReg;
	uint8_t pageReg;

	//find the correct registers
	switch (num) {
	case 0:
		addrReg = DMA0_ADDR;
		countReg = DMA0_COUNT;
		pageReg = DMA0_PAGE;
		break;
	case 1:
		addrReg = DMA1_ADDR;
		countReg = DMA1_COUNT;
		pageReg = DMA1_PAGE;
		break;
	case 2:
		addrReg = DMA2_ADDR;
		countReg = DMA2_COUNT;
		pageReg = DMA2_PAGE;
		break;
	case 3:
		addrReg = DMA3_ADDR;
		countReg = DMA3_COUNT;
		pageReg = DMA3_PAGE;
		break;
	case 4:
		addrReg = DMA4_ADDR;
		countReg = DMA4_COUNT;
		pageReg = DMA4_PAGE;
		break;
	case 5:
		addrReg = DMA5_ADDR;
		countReg = DMA5_COUNT;
		pageReg = DMA5_PAGE;
		break;
	case 6:
		addrReg = DMA6_ADDR;
		countReg = DMA6_COUNT;
		pageReg = DMA6_PAGE;
		break;
	case 7:
		addrReg = DMA7_ADDR;
		countReg = DMA7_COUNT;
		pageReg = DMA7_PAGE;
		break;
	default:
		panic(dmaConfused);
		return;
	}

	//so the flip-flop don't get flipped while we're not looking
	lockScheduler();

	//mask this channel so things don't change
	mask();

	//reset the flip-flop by writing any value
	outb(dma16 ? DMA_FLIP_FLOP_16 : DMA_FLIP_FLOP_8, 0);

	//write the address
	if (dma16) {
		outb(addrReg, (addr >> 1) & 0xFF);		//low
		outb(addrReg, (addr >> 9) & 0xFF);		//high

	} else {
		outb(addrReg, (addr >> 0) & 0xFF);		//low
		outb(addrReg, (addr >> 8) & 0xFF);		//high
	}

	//reset the flip-flop again writing any value
	outb(dma16 ? DMA_FLIP_FLOP_16 : DMA_FLIP_FLOP_8, 0);

	//write the count
	outb(countReg, ((count - 1) >> 0) & 0xFF);	//low
	outb(countReg, ((count - 1) >> 8) & 0xFF);	//high

	//now set the page...
	outb(pageReg, (addr >> 16) & 0xFF);

	//set the mode if needed
	if (hasMode) {
		outb(dma16 ? DMA_MODE_16 : DMA_MODE_8, mode);
	}
	startedOnce = true;

	//now the DMA will start
	unmask();

	//we can release the lock as we are done with the flip-flop
	unlockScheduler();
}

void DMAChannel::stop()
{

}

void DMAChannel::mask(bool m)
{
	outb(dma16 ? DMA_SINGLE_MASK_16 : DMA_SINGLE_MASK_8, (num & 3) | (m ? 4 : 0));
}

void DMAChannel::unmask()
{
	mask(false);
}

char dmaCtrlName[] = "ISA DMA Controller";
DMA::DMA(): Device(dmaCtrlName)
{
	//8 bit ports
	ports[noPorts].rangeStart = 0x00;
	ports[noPorts].rangeLength = 16;
	ports[noPorts++].width = 0;

	//16 bit ports
	ports[noPorts].rangeStart = 0xC0;
	ports[noPorts].rangeLength = 32;
	ports[noPorts++].width = 1;

	//8 bit page registers
	ports[noPorts].rangeStart = 0x81;
	ports[noPorts].rangeLength = 3;
	ports[noPorts++].width = 0;
	ports[noPorts].rangeStart = 0x87;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	//16 bit page registers
	ports[noPorts].rangeStart = 0x89;
	ports[noPorts].rangeLength = 3;
	ports[noPorts++].width = 0;
	ports[noPorts].rangeStart = 0x8F;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
}

int DMA::getAvailable()
{
	//lock so that nothing changes
	lockScheduler();

	//check all 8 to find one that is available
	for (int i = 0; i < 8; ++i) {
		if (available & (1 << i)) {
			unlockScheduler();
			return i;
		}
	}

	unlockScheduler();
	return -1;
}

int DMA::open(int a, int b, void* c)
{
	//channel 0 and 4 cannot be used
	available = 0b11101110;

	//reset things by sending any value
	outb(DMA_MASTER_RESET_8, 0);
	outb(DMA_MASTER_RESET_16, 0);

	return 0;
}

int DMA::close(int a, int b, void* c)
{
	return 0;
}

DMAChannel* DMA::tryLockChannelWithBase(int base)
{
	//we don't want race conditions
	lockScheduler();

	//try the 4 channels at that base
	for (int num = base; num < base + 4; ++num) {
		//check if it is available
		if (available & (1 << num)) {
			//if it is, claim it
			available &= ~(1 << num);

			//create the channel object
			DMAChannel* ch = new DMAChannel(num);

			//unlock and return
			unlockScheduler();
			return ch;
		}
	}

	//unlock and return
	unlockScheduler();
	return nullptr;
}

DMAChannel* DMA::lockChannelWithBase(int base)
{
	//try until you get it
	while (1) {
		DMAChannel* ch = tryLockChannelWithBase(base);
		if (ch) {
			return ch;
		}
	}

	return nullptr;
}

DMAChannel* DMA::tryLockChannel8()
{
	//8 bit uses channels 0-3, so use a base of 0
	return tryLockChannelWithBase(0);
}

DMAChannel* DMA::tryLockChannel16()
{
	//16 bit uses channels 4-7, so use a base of 4
	return tryLockChannelWithBase(4);
}

DMAChannel* DMA::tryLockChannel(int num)
{
	//check that it is in range
	if (num < 0 || num > 7) {
		kprintf("Not in range.\n");
		return nullptr;
	}

	//we don't want race conditions
	lockScheduler();

	//check if it is available
	if (available & (1 << num)) {
		//if it is, claim it
		available &= ~(1 << num);

		//create the channel object
		DMAChannel* ch = new DMAChannel(num);

		//unlock and return
		unlockScheduler();
		return ch;
	}

	//unlock and return
	unlockScheduler();
	return nullptr;
}

DMAChannel* DMA::lockChannel8()
{
	//8 bit uses channels 0-3, so use a base of 0
	return lockChannelWithBase(0);
}

DMAChannel* DMA::lockChannel16()
{
	//16 bit uses channels 4-7, so use a base of 4
	return lockChannelWithBase(4);
}

DMAChannel* DMA::lockChannel(int num)
{
	//try until you get it
	while (1) {
		DMAChannel* ch = tryLockChannel(num);
		if (ch) {
			return ch;
		}
	}

	return nullptr;
}

char badDma[] = "DMA UNLOCK BAD CHANNEL";
char badBook[] = "DMA CORRUPT BOOKKEEPING";
void DMA::unlockChannel(DMAChannel* channel)
{
	//check for null channel
	if (channel == nullptr) {
		panic(badDma);
	}

	lockScheduler();

	//ensure it was actually claimed
	if (!(available & (1 << channel->num))) {
		//make it as available
		available |= 1 << channel->num;

		//delete the channel
		delete channel;

	} else {
		panic(badBook);
	}

	unlockScheduler();
}