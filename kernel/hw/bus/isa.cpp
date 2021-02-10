#include "core/common.hpp"
#include "core/elf.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hw/bus/isa.hpp"
#include "hw/video/vga.hpp"
#include "registry/registry.hpp"

#include "hw/buzzer/pcspk.hpp"
#include "hw/clock/rtc.hpp"
#include "hw/bus/ps2.hpp"
#include "hw/audio/sb16.hpp"
#include "hw/dma/isadma.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

ISA::ISA(): Bus("ISA Bus")
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
	if (systemBuzzer == nullptr) {
		systemBuzzer = new Beep();
		systemBuzzer->detectionType = DetectionType::ISAProbe;
		addChild(systemBuzzer);
		systemBuzzer->open(0, 0, nullptr);
	}
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

void ISA::doPS2()
{
	PS2* ps2 = new PS2();
	addChild(ps2);
	ps2->open(0, 0, nullptr);
}

void ISA::doRTC()
{
	computer->clock = nullptr;

	if (computer->clock == nullptr) {
		RTC* rtc = new RTC();
		rtc->detectionType = DetectionType::ISAProbe;
		addChild(rtc);
		rtc->open(0, 0, nullptr);

		computer->clock = rtc;
	}
}

#define ISA_DEVICE_ENABLE		 0
#define ISA_DEVICE_AUTO_DETECT	-1
#define ISA_DEVICE_DISABLE		-2

DMA* isaDMAController = nullptr;

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

	struct ISATableEntry
	{
		void (ISA::*setupFunction)();
		char detectKey[16];
	};

	ISATableEntry isaTable[] = {
		{&ISA::doSpeaker		, "speaker"},
		{&ISA::doRTC			, "rtc"},
		{&ISA::doPS2			, "ps2"},
		{&ISA::doFloppy			, "floppy"},
		{&ISA::doSoundblaster	, "soundblaster"},
		{&ISA::doATA			, "isaata"},
		{&ISA::doGameport		, "gameport"},
	};

	static bool detectDone = false;

	if (detectDone) {
		return;
	}
	detectDone = true;

	bool needsSafeCheck = Registry::readBoolWithDefault((char*) "isa", (char*) "@isa:doneSafeCheck", true);

	for (int i = 0; i < sizeof(isaTable) / sizeof(ISATableEntry); ++i) {
		char key[32];
		strcpy(key, "@devices:");
		strcat(key, isaTable[i].detectKey);

		int val = Registry::readIntWithDefault((char*) "isa", (char*) key, ISA_DEVICE_AUTO_DETECT);
		if (val != ISA_DEVICE_DISABLE) {
			if (needsSafeCheck) {
				//TODO:
				// Registry::writeInt((char*) "isa", (char*) key, ISA_DEVICE_DISABLE);
			}
			
			(this->*(isaTable[i].setupFunction))();

			if (needsSafeCheck) {
				// Registry::writeInt((char*) "isa", (char*) key, val);
			}
		}
	}	

	VGA* vga = new VGA();
	addChild(vga);
	vga->open(0, 0, nullptr);
	vga->clearScreen(0x0);
}
