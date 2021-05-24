#include "core/common.hpp"
#include "krnl/panic.hpp"
#include "sys/syscalls.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/pic.hpp"
#include "hw/intctrl/apic.hpp"
#include "hal/device.hpp"
#include "hw/acpi.hpp"
#include "krnl/hal.hpp"
#include "hw/cpu.hpp"
#include "vm86/vm8086.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

extern "C" uint64_t int_handler(struct regs* r)
{
	while (Krnl::kernelInPanic) {
		asm("cli; hlt");
	}

	InterruptController* intCtrl = CPU::current()->intCtrl;

	int num = r->int_no;

	//send EOI command for IRQs
	//this is done now because the handler could cause a task switch, which
	//would mean the EOI never gets called, and so the system basically locks up
	if (num >= 32 && num < 32 + 24) {
		Hal::endOfInterrupt(num - 32);
	}

	auto handleList = intCtrl->handlers[num];
	auto contextList = intCtrl->contexts[num];

	//call handler if it exists
	for (int i = 0; i < 4; ++i) {
		if (handleList[i]) {
			if (unlikely(r->int_no == 96)) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
				return reinterpret_cast<uint64_t(*)(regs*, void*)>(handleList[i])(r, contextList[i]);		//this has got to be the world's worst line of code, ever
#pragma GCC diagnostic pop
			} else {
				handleList[i](r, contextList[i]);
			}
		}
	}

	return 0;
}

void InterruptController::installISRHandler(int num, void (*handler)(regs*, void*), void* context)
{
	for (int i = 0; i < 4; ++i) {
		if (handlers[num][i] == nullptr) {
			//set handler
			handlers[num][i] = handler;
			contexts[num][i] = context;
			return;
		}
	}

	panic("[intctrl] A!");
}

int InterruptController::installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	if (legacy && this->getName()[0] == 'A') {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[intctrl] B!");
		}
	}

	//IRQs start at 32
	num += 32;

	for (int i = 0; i < 4; ++i) {
		if (handlers[num][i] == nullptr) {
			//set handler
			handlers[num][i] = handler;
			contexts[num][i] = context;

			return num - 32;
		}
	}

	panic("[intctrl] C!");
	return -1;
}

void InterruptController::uninstallISRHandler(int num, void (*handler)(regs*, void*))
{
	for (int i = 0; i < 4; ++i) {
		if (handler == handlers[num][i]) {
			handlers[num][i] = nullptr;
			contexts[num][i] = nullptr;
		}
	}
}

void InterruptController::clearAllHandlers(int num, bool legacy)
{
	if (legacy && this->getName()[0] == 'A') {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[intctrl] D!");
		}
	}

	num += 32;
	for (int i = 0; i < 4; ++i) {
		handlers[num][i] = nullptr;
		contexts[num][i] = nullptr;
	}
}

void InterruptController::uninstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy)
{
	if (legacy && this->getName()[0] == 'A') {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[intctrl] E!");
		}
	}

	num += 32;
	for (int i = 0; i < 4; ++i) {
		if (handler == handlers[num][i]) {
			handlers[num][i] = nullptr;
			contexts[num][i] = nullptr;
		}
	}
}

InterruptController::InterruptController(const char* name): Device(name)
{
	deviceType = DeviceType::Intctrl;

	//set all handlers to null so they don't get called
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 4; ++j) {
			handlers[i][j] = nullptr;
			contexts[i][j] = nullptr;		//not needed, but just to keep a consistant startup state
		}
	}
}

InterruptController::~InterruptController()
{
	//should have a virtual destructor
}

int InterruptController::convertLegacyIRQNumber(int num)
{
	if (this->getName()[0] == 'A') {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[installIRQHandler] Legacy IRQ with number 16 or higher");
		}
	}

	return num;
}