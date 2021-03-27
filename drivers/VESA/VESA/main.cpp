#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "vm86/vm8086.hpp"

extern "C" {
#include "libk/string.h"
}


void start(void* parent)
{
	Device* rootDevice = (Device*) parent;

	VESA* dev = new VESA();

	rootDevice->addChild(dev);

	dev->open(0, 0, nullptr);

	extern Video* screen;
	screen = dev;
}


#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

VESA::VESA(): Video("VESA Display")
{

}

int VESA::close(int a, int b, void* c)
{
	return 0;
}

ModeInfo VESA::getModeStruct(int mode)
{
	int ogmode = mode;

	ModeInfo modeInfo;
	mode |= 0x8000;

	Vm::start8086("C:/Banana/System/VESA.COM", 0x0000, 0x90, mode, mode);
	uint8_t* addr = (uint8_t*) &modeInfo;
	int totalGot = 0;
	while (1) {
		int outBytes = Vm::getOutput8086(addr);
		totalGot += outBytes;
		addr += outBytes;
		kprintf("Got %d bytes back... total %d\n", outBytes, totalGot);
		if (totalGot == 12) break;
		nanoSleep(1000 * 1000);
	}
	Vm::finish8086();
	modeInfo.number = ogmode;
	return modeInfo;
}

void VESA::setMode(int mode)
{
	ModeInfo modeInfo;
	int ogmode = mode;

	Vm::start8086("C:/Banana/System/VESA.COM", 0x0000, 0x90, mode, mode);
	uint8_t* addr = (uint8_t*) &modeInfo;
	int totalGot = 0;
	while (1) {
		int outBytes = Vm::getOutput8086(addr);
		totalGot += outBytes;
		addr += outBytes;
		kprintf("Got %d bytes back... total %d\n", outBytes, totalGot);
		if (totalGot == 12) break;
		nanoSleep(1000 * 1000);
	}
	Vm::finish8086();
	modeInfo.number = ogmode;
	width = modeInfo.width;
	height = modeInfo.height;
	bpp = modeInfo.bpp;
	pitch = modeInfo.pitch / ((bpp + 7) / 8);
	vramPhys = (uint8_t*) modeInfo.lfb;
	vram = (uint8_t*) 0xC3000000;

	if (width == 0 && height == 0 && pitch == 0) {
		panic("UNSUPPORTED VESA MODE");
	}

	kprintf("%dx%d (%d). pitch %d. lfb = 0x%X. bytes = 0x%X\n", width, height, bpp, pitch, vramPhys);

	Virt::getAKernelVAS()->mapRange((size_t) vramPhys, (size_t) vram, pitch * height * bpp / 8 / 4096, PAGE_PRESENT | PAGE_WRITABLE | PAGE_SUPERVISOR);

}

ModeInfo modes[256];
int numModes = 0;

void VESA::getModes()
{
	if (gotModes) {
		return;
	}
	gotModes = true;

	File* fil = new File("C:/Banana/System/vesamode.dat", kernelProcess);
	if (fil->exists()) {
		FileStatus res = fil->open(FileOpenMode::Read);
		int br;
		if (res == FileStatus::Success) {
			uint16_t count = 0;
			fil->read(2, &count, &br);
			if (br != 2) {
				fil->close();
				fil->unlink();
			} else {
				fil->read(sizeof(ModeInfo) * ((int) count), modes, &br);
				fil->close();
				if (br != sizeof(ModeInfo) * ((int) count)) {
					fil->unlink();
				} else {
					numModes = count;
					return;
				}
			}

		} else {
			fil->unlink();
		}
	}

	for (int i = 0x4100; i < 0x41FF; ++i) {
		ModeInfo mode = getModeStruct(i);
		//filter out invalid modes and very bad modes
		if (mode.width >= 640 && mode.height >= 480) {
			//filter out modes we don't support
			if (mode.bpp == 15 || mode.bpp == 16 || mode.bpp == 32) {
				modes[numModes++] = mode;
				if (numModes == 256) break;
			}
		}
	}

	for (int i = 0; i < numModes; ++i) {
		char ratioString[8] = "?";
		modes[i].ratioEstimation = RATIO_UNKNOWN;

		if (modes[i].width / 4 * 3 == modes[i].height) {
			strcpy(ratioString, "4:3");
			modes[i].ratioEstimation = RATIO_43;

		} else if (modes[i].width / 16 * 9 == modes[i].height) {
			strcpy(ratioString, "16:9");
			modes[i].ratioEstimation = RATIO_169;

		} else if (modes[i].width / 16 * 10 == modes[i].height) {
			strcpy(ratioString, "16:10");
			modes[i].ratioEstimation = RATIO_1610;
		}
	}

	FileStatus res = fil->open(FILE_OPEN_WRITE_NORMAL);
	if (res == FileStatus::Success) {
		uint16_t count = numModes;
		int br;
		fil->write(2, &count, &br);
		fil->write(count * sizeof(ModeInfo), modes, &br);
		fil->close();
	}
}

struct EDIDRecord
{
	uint8_t padding[8];
	uint16_t manufactureIDBigEndian;
	uint16_t edidID;
	uint32_t serialNumber;
	uint8_t manufactureWeek;
	uint8_t manufactureYear;
	uint8_t edidVersion;
	uint8_t edidRevision;
	uint8_t videoInputType;
	uint8_t maxHzSizeCm;
	uint8_t maxVtSizeCm;
	uint8_t gamaFactor;
	uint8_t dpmsFlags;
	uint8_t chromaInfo[10];
	uint8_t establishedTimings1;
	uint8_t establishedTimings2;
	uint8_t manufacturesReservedTimings;
	uint16_t standardTimingIdentification[8];
	uint8_t detailedTiming[4][18];
	uint8_t reserved;
	uint8_t checksum;

} __attribute__((packed));


ModeInfo VESA::calculateBestMode()
{
	getModes();

	uint8_t defaultMonitorEDID[128];

	/*uint8_t addr[32];
	Vm::start8086("C:/Banana/System/EDID.COM", 0x0000, 0x90, 0, 0);
	int totalGot = 0;
	while (1) {
		int outBytes = Vm::getOutput8086(addr);
		if (outBytes) break;
		nanoSleep(1000 * 1000 * 10);
	}

	uint8_t* ptr = (uint8_t*) 0x900;
	memcpy(&defaultMonitorEDID, (const void*) 0x900, 128);

	uint16_t* axPtr = (uint16_t*) 0x980;
	uint16_t ax = *axPtr;
	Vm::finish8086();

	bool biosEDIDSupported = ((ax & 0xFF) == 0x4F) && ((ax >> 8) == 0);
	kprintf("EDID: %d. status = 0x%X\n", biosEDIDSupported, ax);*/
	bool biosEDIDSupported = false;

	int monitorResolution = RATIO_43;
	int monitorWidth = 800;
	int monitorHeight = 600;

	EDIDRecord* edid = (EDIDRecord*) defaultMonitorEDID;
	if (biosEDIDSupported) {
		monitorWidth  = edid->detailedTiming[0][0x38 - 0x36] | ((int) (edid->detailedTiming[0][0x3A - 0x36] & 0xF0) << 4);
		monitorHeight = edid->detailedTiming[0][0x3B - 0x36] | ((int) (edid->detailedTiming[0][0x3D - 0x36] & 0xF0) << 4);
	}

	kprintf("Best resolution: %dx%d\n", monitorWidth, monitorHeight);

	ModeInfo bestMode;
	int bestScore = 0;


	for (int i = 0; i < numModes; ++i) {
		int score = modes[i].width + modes[i].height;

		score *= (modes[i].bpp + 12);

		if (modes[i].width > monitorWidth || modes[i].height > monitorHeight) {
			score /= 16;
			score -= monitorWidth * 2;
			score -= monitorHeight * 2;

		} else if (modes[i].ratioEstimation == monitorResolution) {
			score *= 2;

		} else if (modes[i].ratioEstimation == RATIO_UNKNOWN) {
			if (modes[i].ratioEstimation == RATIO_43) score *= 2;
			if (modes[i].ratioEstimation == RATIO_169) score *= 4;
			if (modes[i].ratioEstimation == RATIO_1610) score *= 4;
		}
		
		if (modes[i].width == monitorWidth || modes[i].height == monitorHeight) {
			score *= 2;
		}

		if (score > bestScore) {
			bestScore = score;
			bestMode = modes[i];
		}

		kprintf("0x%X: %d %dx%d @ %dbpp. %d\n", modes[i].number, score, modes[i].width, modes[i].height, modes[i].bpp, modes[i].ratioEstimation);
	}

	return bestMode;
}

int VESA::open(int a, int b, void* c)
{
	ModeInfo best = calculateBestMode();

	setMode(best.number);
	return 0;
}

uint32_t colTo15(uint32_t col)
{
	uint8_t red = col >> 16;
	uint8_t green = col >> 8;
	uint8_t blue = col;

	red >>= 3;
	green >>= 3;
	blue >>= 3;

	return ((uint32_t) blue) | (((uint32_t) green) << 5) | (((uint32_t) red) << 10);
}

uint32_t colTo16(uint32_t col)
{
	uint8_t red = col >> 16;
	uint8_t green = col >> 8;
	uint8_t blue = col;

	red >>= 3;
	green >>= 2;
	blue >>= 3;

	return ((uint32_t) blue) | (((uint32_t) green) << 5) | (((uint32_t) red) << 11);
}

void VESA::putpixel(int x, int y, uint32_t colour)
{
	if (bpp == 15) {
		colour = colTo15(colour);
		((uint16_t*) vram)[y * pitch + x] = colour;

	} else if (bpp == 16) {
		colour = colTo16(colour);
		((uint16_t*) vram)[y * pitch + x] = colour;

	} else if (bpp == 32) {
		((uint32_t*) vram)[y * pitch + x] = colour;

	}
}