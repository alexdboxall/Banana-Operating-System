#include <stdint.h>

void realstart(void* _parent);

void start(void* _parent)
{
	realstart(_parent);
}

#include "main.hpp"
#include "pcspk.hpp"
#include "rtc.hpp"

#include "core/common.hpp"
#include "thr/elf.hpp"
#include "hw/ports.hpp"
#include "hal/video.hpp"
#include "hw/acpi.hpp"
#include "reg/registry.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void realstart(void* _parent)
{
	Device* parent = (Device*) _parent;

	if (systemBuzzer == nullptr) {
		Krnl::setBootMessage("Starting speaker driver...");

		systemBuzzer = new Beep();
		systemBuzzer->detectionType = DetectionType::ISAProbe;
		parent->addChild(systemBuzzer);
		systemBuzzer->open(0, 0, nullptr);
	}

	computer->clock = nullptr;

	if (computer->clock == nullptr) {
		Krnl::setBootMessage("Starting RTC driver...");

		RTC* rtc = new RTC();
		rtc->detectionType = DetectionType::ISAProbe;
		parent->addChild(rtc);
		rtc->open(0, 0, nullptr);

		computer->clock = rtc;
	}
}
