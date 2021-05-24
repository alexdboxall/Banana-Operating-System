#include "arch/i386/hal.hpp"
#include "arch/i386/pic.hpp"
#include <hw/cpu.hpp>
#include "vm86/x87em.hpp"
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>

#define ISR_DIV_BY_ZERO 0x00
#define ISR_DEBUG 0x01
#define ISR_NMI 0x02
#define ISR_BREAKPOINT 0x03
#define ISR_OVERFLOW 0x04
#define ISR_BOUNDS 0x05
#define ISR_INVALID_OPCODE 0x06
#define ISR_DEVICE_NOT_AVAILABLE 0x07
#define ISR_DOUBLE_FAULT 0x08
#define ISR_COPROCESSOR_SEGMENT_OVERRUN 0x09
#define ISR_INVALID_TSS 0x0A
#define ISR_SEGMENT_NOT_PRESENT 0x0B
#define ISR_STACK_SEGMENT 0x0C
#define ISR_GENERAL_PROTECTION 0x0D
#define ISR_PAGE_FAULT 0x0E
#define ISR_RESERVED 0x0F
#define ISR_FPU_EXCEPTION 0x10
#define ISR_ALIGNMENT_CHECK 0x11
#define ISR_MACHINE_CHECK 0x12
#define ISR_SIMD_EXCEPTION 0x13
#define ISR_VIRTULIZATION_EXCEPTION 0x14
#define ISR_SECURITY_EXCEPTION 0x1E

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

void i386SaveCoprocessor(void* buf)
{
	size_t addr = (((size_t) buf) + 63) & ~0x3F;
	coproSaveFunc(addr);
}

void i386LoadCoprocessor(void* buf)
{
	size_t addr = (((size_t) buf) + 63) & ~0x3F;
	coproLoadFunc(addr);
}

ThreadControlBlock* fpuOwner = nullptr;

void x87EmulHandler(regs* r, void* context)
{
	kprintf("x87EmulHandler\n");

	if (currentTaskTCB->vm86Task) {
		panic("VM86 CANNOT USE FPU");
	}

	size_t cr0 = CPU::readCR0();

	if (cr0 & 8) {
		//clear task switched
		asm volatile ("clts");

		//save previous state
		if (fpuOwner) {
			i386SaveCoprocessor(fpuOwner->fpuState);
		}

		//check if never had state before, otherwise load state
		if (currentTaskTCB->fpuState == nullptr) {
			currentTaskTCB->fpuState = malloc(512 + 64);

		} else {
			i386LoadCoprocessor(fpuOwner->fpuState);
		}

		fpuOwner = currentTaskTCB;
		return;
	}

	if (Vm::x87Handler(r)) {
		return;
	}

	kprintf("Device not available\n");
	Thr::terminateFromIRQ();
}


namespace Hal
{
	void noCopro (size_t a)
	{

	}

	void initialiseCoprocessor()
	{
		fpuOwner = nullptr;
		CPU::current()->intCtrl->installISRHandler(ISR_DEVICE_NOT_AVAILABLE, x87EmulHandler);

		if (avxDetect()) {
			kprintf("AVX.\n");
			coproSaveFunc = avxSave;
			coproLoadFunc = avxLoad;
			avxInit();
			return;
		}

		if (sseDetect()) {
			kprintf("SSE.\n");
			coproSaveFunc = sseSave;
			coproLoadFunc = sseLoad;
			sseInit();
			return;
		}

		if (x87Detect()) {
			kprintf("X87.\n");
			coproSaveFunc = x87Save;
			coproLoadFunc = x87Load;
			x87Init();
			return;
		}

		kprintf("NO FPU.\n");

		coproSaveFunc = noCopro;
		coproLoadFunc = noCopro;

		CPU::current()->writeCR0(CPU::current()->readCR0() | 4);
	}

	void panic(const char* message)
	{
		Krnl::panic(message);
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

	bool apic = false;
	void initialise()
	{
		if (CPU::current()->features.hasTSC) {
			_i386_HAL_tscFunction = readTSC;

		}  else {
			_i386_HAL_tscFunction = noTSC;
		}

		/*if (CPU::getNumber() != 0) {
			//start an APIC
			InterruptController* controller = new APIC();
			controller->open(0, 0, nullptr);
			computer->addChild(controller);

			return controller;
		}*/

		//check if the APIC exists
		if (ioapicDiscoveryNumber == 0) {
			computer->features.hasAPIC = false;
		}

		apic = computer->features.hasAPIC;

		InterruptController* controller = new PIC();
		controller->open(0, 0, nullptr);

		if (apic) {
			//disable the PIC
			controller->close(0, 0, nullptr);

			//delete the PIC
			delete controller;

			//start an APIC
			controller = new APIC();
			controller->open(0, 0, nullptr);
		}

		computer->addChild(controller);

		controller->installISRHandler(ISR_DIV_BY_ZERO, otherISRHandler);
		controller->installISRHandler(ISR_DEBUG, otherISRHandler);
		controller->installISRHandler(ISR_NMI, nmiHandler);
		controller->installISRHandler(ISR_BREAKPOINT, otherISRHandler);
		controller->installISRHandler(ISR_OVERFLOW, otherISRHandler);
		controller->installISRHandler(ISR_BOUNDS, otherISRHandler);
		controller->installISRHandler(ISR_INVALID_OPCODE, opcodeFault);
		controller->installISRHandler(ISR_DOUBLE_FAULT, doubleFault);
		controller->installISRHandler(ISR_COPROCESSOR_SEGMENT_OVERRUN, otherISRHandler);
		controller->installISRHandler(ISR_INVALID_TSS, otherISRHandler);
		controller->installISRHandler(ISR_SEGMENT_NOT_PRESENT, otherISRHandler);
		controller->installISRHandler(ISR_STACK_SEGMENT, otherISRHandler);
		controller->installISRHandler(ISR_GENERAL_PROTECTION, gpFault);
		controller->installISRHandler(ISR_PAGE_FAULT, pgFault);
		controller->installISRHandler(ISR_RESERVED, otherISRHandler);
		controller->installISRHandler(ISR_FPU_EXCEPTION, otherISRHandler);
		controller->installISRHandler(ISR_ALIGNMENT_CHECK, otherISRHandler);
		controller->installISRHandler(ISR_MACHINE_CHECK, otherISRHandler);
		controller->installISRHandler(ISR_SIMD_EXCEPTION, otherISRHandler);
		controller->installISRHandler(ISR_VIRTULIZATION_EXCEPTION, otherISRHandler);
		controller->installISRHandler(ISR_SECURITY_EXCEPTION, otherISRHandler);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
		controller->installISRHandler(96, reinterpret_cast<void(*)(regs*, void*)>(Sys::systemCall));
#pragma GCC diagnostic pop

		return controller;
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

	extern "C" void i386GetRDRAND();
	uint32_t getRand()
	{
		//i386GetRDRAND()

		return 0;
	}

#define IA32_APIC_BASE_MSR 0x1B

	void endOfInterrupt(int irqNum)
	{
		if (apic) {
			uint64_t ret = computer->rdmsr(IA32_APIC_BASE_MSR);
			uint32_t* ptr = (uint32_t*) (size_t) ((ret & 0xfffff000) + 0xb0);
			*ptr = 1;

		} else {
			picEOI(irqNum);
		}
	}

	void restart();
	void shutdown();
	void sleep();
}