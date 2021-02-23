#include <stdint.h>

void realstart(void* _parent);

void start(void* _parent)
{
	realstart(_parent);
}

#include "main.hpp"
#include "isadma.hpp"
#include "sb16.hpp"
#include "ps2.hpp"

#include "core/common.hpp"
#include "thr/elf.hpp"
#include "hw/ports.hpp"
#include "hal/video.hpp"
#include "hw/acpi.hpp"
#include "registry/registry.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void realstart(void* _parent)
{
	kprintf("string test.\n");

	Device* parent = (Device*) _parent;

	ISA* dev = new ISA();
	parent->addChild(dev);

	dev->open(0, 0, nullptr);
}

char busname[] = "ISA Bus";

ISA::ISA(): Bus(busname)
{

}

int ISA::open(int a, int b, void* c)
{
	detect();
	return 0;
}

int ISA::close(int a, int b, void* c)
{
	return 0;
}

void ISA::doSpeaker()
{

}

void ISA::doSoundblaster()
{
	return;

	outb(0x226, 1);
	nanoSleep(1000 * 1000 * 3);
	outb(0x226, 0);

	if (inb(0x22A) == 0xAA) {
		SoundBlaster16* sb = new SoundBlaster16();
		addChild(sb);
		sb->open(0, 0, nullptr);

		extern void sb16Demo(void*);
		kernelProcess->createThread(sb16Demo, (void*) sb, 111);
	}
}

void ISA::doSerial()
{

}

void ISA::doParallel()
{

}

void ISA::doGameport()
{

}

void ISA::doFloppy()
{
	uint16_t* biosDataArea = (uint16_t*) (size_t) 0x410;
	if ((*biosDataArea) & 1) {
		//executeDLL(loadDLL("C:/Banana/Drivers/floppy.sys"), this);
	}
}

void ISA::doATA()
{

}

char str_isa[] = "isa";
char str_isadonesafe[] = "@isa:doneSafeCheck";
char str_spk[] = "speaker";
char str_rtc[] = "rtc";
char str_ps2[] = "ps2";
char str_floppy[] = "floppy";
char str_sb16[] = "soundblaster";
char str_isaata[] = "isaata";
char str_gp[] = "gameport";
char str_devices[] = "@devices:";

void ISA::doPS2()
{
	kprintf(str_ps2);
	kprintf(str_ps2);
	kprintf(str_ps2);
	kprintf(str_ps2);

	PS2* ps2 = new PS2();
	addChild(ps2);
	ps2->open(0, 0, nullptr);
}

void ISA::doRTC()
{
	
}

#define ISA_DEVICE_ENABLE		 0
#define ISA_DEVICE_AUTO_DETECT	-1
#define ISA_DEVICE_DISABLE		-2

DMA* isaDMAController = nullptr;

bool detectDone = false;

void ISA::detect()
{
	//DMA needs to be setup first
	isaDMAController = new DMA();
	addChild(isaDMAController);
	isaDMAController->open(0, 0, nullptr);

	//serial ports
	doSerial();

	//parallel ports
	doParallel();

	if (detectDone) {
		return;
	}

	detectDone = true;

	bool needsSafeCheck = Reg::readBoolWithDefault((char*) str_isa, (char*) str_isadonesafe, true);

	for (int i = 0; i < 7; ++i) {
		char key[32];
		strcpy(key, str_devices);

		if (i == 0) strcat(key, str_spk);
		if (i == 1) strcat(key, str_rtc);
		if (i == 2) strcat(key, str_ps2);
		if (i == 3) strcat(key, str_floppy);
		if (i == 4) strcat(key, str_sb16);
		if (i == 5) strcat(key, str_isaata);
		if (i == 6) strcat(key, str_gp);

		int val = Reg::readIntWithDefault((char*) str_isa, (char*) key, ISA_DEVICE_AUTO_DETECT);
		if (val != ISA_DEVICE_DISABLE) {
			if (needsSafeCheck) {
				//TODO:
				// Reg::writeInt((char*) str_isa, (char*) key, ISA_DEVICE_DISABLE);
			}

			if (i == 0) doSpeaker();
			if (i == 1) doRTC();
			if (i == 2) doPS2();
			if (i == 3) doFloppy();
			if (i == 4) doSoundblaster();
			if (i == 5) doATA();
			if (i == 6) doGameport();

			if (needsSafeCheck) {
				// Reg::writeInt((char*) str_isa, (char*) key, val);
			}
		}
	}
}
