#include "arch/i386/hal.hpp"
#include <hw/cpu.hpp>
#include "vm86/x87em.hpp"
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint64_t(*_i386_HAL_tscFunction)();

extern "C" int  avxDetect();
extern "C" void avxSave(size_t);
extern "C" void avxLoad(size_t);
extern "C" void avxInit();

extern "C" int  sseDetect();
extern "C" void sseSave(size_t);
extern "C" void sseLoad(size_t);
extern "C" void sseInit();

extern "C" int  x87Detect();
extern "C" void x87Save(size_t);
extern "C" void x87Load(size_t);
extern "C" void x87Init();

void (*coproSaveFunc)(size_t);
void (*coproLoadFunc)(size_t);

void _i386_saveCoprocessor(void* buf)
{
	size_t addr = (((size_t) buf) + 63) & ~0x3F;
	coproSaveFunc(addr);
}

void _i386_loadCoprocessor(void* buf)
{
	size_t addr = (((size_t) buf) + 63) & ~0x3F;
	coproLoadFunc(addr);
}

ThreadControlBlock* fpuOwner = nullptr;

void x87EmulHandler(regs* r, void* context)
{
	size_t cr0 = CPU::readCR0();
	bool handled;

	if (currentTaskTCB->vm86Task) {
		goto bad;
	}

	if (cr0 & 8) {
		//clear task switched
		asm volatile ("clts");

		//save previous state
		if (fpuOwner) {
			_i386_saveCoprocessor(fpuOwner->fpuState);
		}

		//check if never had state before, otherwise load state
		if (currentTaskTCB->fpuState == nullptr) {
			currentTaskTCB->fpuState = malloc(512 + 64);

		} else {
			Hal::loadCoprocessor(fpuOwner->fpuState);
		}

		fpuOwner = currentTaskTCB;
		return;
	}

	handled = Vm::x87Handler(r);
	if (handled) {
		return;
	}

bad:
	kprintf("Device not available\n");

	displayDebugInfo(r);
	displayProgramFault("Device not available");

	Thr::terminateFromIRQ();
}


namespace Hal
{
	void noCopro (size_t a)
	{

	}

	void initialiseCoprocessor()
	{
		controller->installISRHandler(ISR_DEVICE_NOT_AVAILABLE, x87EmulHandler);

		if (avxDetect()) {
			coproSaveFunc = avxSave;
			coproLoadFunc = avxLoad;
			avxInit();
			return;
		}

		if (sseDetect()) {
			coproSaveFunc = sseSave;
			coproLoadFunc = sseLoad;
			sseInit();
			return;
		}

		if (x87Detect()) {
			coproSaveFunc = x87Save;
			coproLoadFunc = x87Load;
			x87Init();
			return;
		}

		coproSaveFunc = noCopro;
		coproLoadFunc = noCopro;

		coproType = COPRO_NONE;
		CPU::current()->writeCR0(CPU::current()->readCR0() | 4);
	}

	void panic(const char* message)
	{
		Krnl::panic(message);
	}

	void* allocateCoprocessorState()
	{
		return malloc(512 + 64);
	}

	uint64_t noTSC()
	{
		return 0;
	}

	uint64_t readTSC()
	{
		uint64_t ret;
		asm volatile ("rdtsc" : "=A"(ret));
		return ret;
	}

	void initialise()
	{
		if (CPU::current()->features.hasTSC) {
			_i386_HAL_tscFunction = readTSC;

		}  else {
			_i386_HAL_tscFunction = noTSC;
		}
	}

	void makeBeep(int hertz)
	{
		if (hertz == 0) {
			uint8_t tmp = inb(0x61) & 0xFC;
			outb(0x61, tmp);

		} else {
			uint32_t div = 1193180 / hertz;

			outb(0x43, 0xB6);
			outb(0x42, (uint8_t) (div));
			outb(0x42, (uint8_t) (div >> 8));

			uint8_t tmp = inb(0x61);
			if (tmp != (tmp | 3)) {
				outb(0x61, tmp | 3);
			}
		}
	}

	extern "C" void _i386_getRDRAND();
	uint32_t getRand()
	{
		//_i386_getRDRAND()

		return 0;
	}

	void endOfInterrupt();

	void restart();
	void shutdown();
	void sleep();
}