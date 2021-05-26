#include "arch/i386/hal.hpp"
#include "arch/i386/pic.hpp"
#include "arch/i386/rtc.hpp"

#include <hw/cpu.hpp>
#include "vm86/x87em.hpp"
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"


namespace Krnl
{
	/*char exceptionNames[][32] = {
		"Division by zero error",
		"Debug",
		"Non-maskable interrupt",
		"Breakpoint",
		"Overflow",
		"Bound range exceeded",
		"Invalid opcode",
		"Device not available",
		"Dobule fault",
		"Coprocessor segment",
		"Invalid TSS",
		"Segment not present",
		"Stack segment fault",
		"General protection fault",
		"Page fault",
		"Reserved",
		"Floating point exception",
		"Alignment check",
		"Machine check",
		"SIMD floating-point exception",
		"Virtualisation exception",
	};*/
}

void displayDebugInfo(regs* r)
{
	size_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r"(cr0));
	size_t cr2;
	asm volatile ("mov %%cr2, %0" : "=r"(cr2));
	size_t cr3;
	asm volatile ("mov %%cr3, %0" : "=r"(cr3));
	size_t cr4;
	asm volatile ("mov %%cr4, %0" : "=r"(cr4));

	kprintf("ESP: 0x%X\n", r->esp);
	kprintf("EBP: 0x%X\n", r->ebp);
	kprintf("USERESP: 0x%X\n", r->useresp);
	kprintf("EIP: 0x%X\n", r->eip);
	kprintf("ERR: 0x%X\n", r->err_code);

	kprintf("CR2: 0x%X\n", (uint32_t) cr2);
	kprintf("CR3: 0x%X\n", cr3);

	setActiveTerminal(kernelProcess->terminal);

	kernelProcess->terminal->puts("\n TASK: ");
	kernelProcess->terminal->puts(currentTaskTCB->processRelatedTo->taskname);
	kernelProcess->terminal->puts("\n EIP: ");
	kernelProcess->terminal->putx(r->eip);
	kernelProcess->terminal->puts("\n ESP: ");
	kernelProcess->terminal->putx(r->esp);
	kernelProcess->terminal->puts("\nUESP: ");
	kernelProcess->terminal->putx(r->useresp);
	kernelProcess->terminal->puts("\n  CS: ");
	kernelProcess->terminal->putx(r->cs);
	kernelProcess->terminal->puts("\n ERR: ");
	kernelProcess->terminal->putx((uint32_t) r->err_code);
	kernelProcess->terminal->puts("\n EFL: ");
	kernelProcess->terminal->putx((uint32_t) r->eflags);
	kernelProcess->terminal->puts("\n\n CR0: ");
	kernelProcess->terminal->putx((uint32_t) cr0);
	kernelProcess->terminal->puts("\n CR2: ");
	kernelProcess->terminal->putx((uint32_t) cr2);
	kernelProcess->terminal->puts("\n CR3: ");
	kernelProcess->terminal->putx((uint32_t) cr3);

	asm("cli;hlt;");
	while (1);
}

void displayProgramFault(const char* text)
{
	kprintf(text);
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(text, VgaColour::White, VgaColour::Maroon);
	}
}

bool (*gpFaultIntercept)(regs* r) = nullptr;

void gpFault(regs* r, void* context)
{
	gpFaultIntercept = Vm::faultHandler;
	if (gpFaultIntercept) {
		bool handled = gpFaultIntercept(r);
		if (handled) {
			return;
		}
	}

	displayDebugInfo(r);
	displayProgramFault("General protection fault");

	Thr::terminateFromIRQ();
}

void pgFault(regs* r, void* context)
{
	if (currentTaskTCB->processRelatedTo->vas->tryLoadBackOffDisk(CPU::readCR2())) {
		return;
	}

	displayDebugInfo(r);
	displayProgramFault("Page fault");

	Thr::terminateFromIRQ();
}

void nmiHandler(regs* r, void* context)
{
	computer->handleNMI();
}

void otherISRHandler(regs* r, void* context)
{
	displayDebugInfo(r);
	displayProgramFault("Unhandled exception - CHECK KERNEL LOGS");

	Thr::terminateFromIRQ();
}

#pragma GCC diagnostic push
#pragma GCC optimize ("O0")


void opcodeFault(regs* r, void* context)
{
	kprintf("OPFAULT 0x%X\n", r->eip);

	if (CPU::current()->opcodeDetectionMode) {
		kprintf("Opcode detection: invalid opcode.\n");
		r->eip += 25;
		return;
	}

	//emulate instructions added to the 486 and Pentium

	/*
	uint8_t* eip = (uint8_t*) r->eip;

	//lock prefix
	bool hasNonLockPrefix = false;

	size_t originalEIP = r->eip;

	if (eip[0] == 0xF0) {
		eip++;
		r->eip++;

	} else if (eip[0] == 0xF2 || eip[0] == 0xF3) {
		hasNonLockPrefix = true;
		eip++;
		r->eip++;

	} else if (eip[0] == 0x66) {						//operand size
		hasNonLockPrefix = true;
		eip++;
		r->eip++;

	} else if (eip[0] == 0x67) {						//address size
		hasNonLockPrefix = true;
		eip++;
		r->eip++;

	} else if (eip[0] == 0x2E || eip[0] == 0x3E) {		//branch prediction, CS/DS override
		hasNonLockPrefix = true;
		eip++;
		r->eip++;

	} else if (eip[0] == 0x36 || eip[0] == 0x26 || \
			   eip[0] == 0x64 || eip[0] == 0x65) {		//segment overrides
		hasNonLockPrefix = true;
		eip++;
		r->eip++;
	}

	//CMPXHG8B	introduced with Pentium
	if (eip[0] == 0x0F && eip[1] == 0xC7) {
		eip++;			//CPU::decodeAddress only allows one byte before the MOD/RM byte
		r->eip++;		//ditto

		int instrLen;
		bool regOnly;
		uint8_t middleDigit;

		//get the memory address
		uint64_t* ptr = (uint64_t*) CPU::decodeAddress(r, &instrLen, &regOnly, &middleDigit);

		if (!regOnly && middleDigit == 1 && !hasNonLockPrefix) {
			//get the pseudo-64 bit regs
			uint64_t edxeax = r->edx;
			edxeax <<= 32;
			edxeax |= (uint64_t) r->eax;

			uint64_t ecxebx = r->ecx;
			ecxebx <<= 32;
			ecxebx |= (uint64_t) r->ebx;

			lockScheduler();
			if (*ptr == edxeax) {
				//if equal, load ECX:EBX to memory
				*ptr = ecxebx;

				//set the zero flag
				r->eflags |= 0x0040;

			} else {
				//otherwise, load memory to EDX:EAX
				edxeax = *ptr;
				r->eax = (edxeax & 0xFFFFFFFFU);
				r->edx = edxeax >> 32;

				//clear the zero flag
				r->eflags &= ~0x0040;
			}
			unlockScheduler();

			//change EIP
			r->eip += instrLen;

			kprintf("Handled CMPXCHG8B\n");
			//don't terminate the program
			return;

		} else {
			//you're not allowed register encodings,
			//in fact, this is what caused the F00F bug on early Pentiums!

			//and the middle digit needs to be 1 for this instruction
		}
	}

	kprintf("Invalid Opcode!\n");
	kprintf("OPCODE vm86: 0x%X (then 0x%X %X %X)\n", *((uint8_t*) (0 + r->eip + r->cs * 16)), *((uint8_t*) (1 + r->eip + r->cs * 16)), *((uint8_t*) (2 + r->eip + r->cs * 16)), *((uint8_t*) (3 + r->eip + r->cs * 16)));
	kprintf("OPCODE i386: 0x%X (then 0x%X %X %X)\n", *((uint8_t*) (0 + r->eip)), *((uint8_t*) (1 + r->eip)), *((uint8_t*) (2 + r->eip)), *((uint8_t*) (3 + r->eip)));
	*/

	displayDebugInfo(r);
	displayProgramFault("Opcode fault");

	Thr::terminateFromIRQ();
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic pop

void doubleFault(regs* r, void* context)
{
	panic("DOUBLE FAULT");
}


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

extern void setupINTS();

namespace Hal
{
	void noCopro (size_t a)
	{

	}

	void initialiseCoprocessor()
	{
		fpuOwner = nullptr;
		installISRHandler(ISR_DEVICE_NOT_AVAILABLE, x87EmulHandler);

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
			open(0, 0, nullptr);
			computer->addChild(controller);

			return controller;
		}*/

		setupINTS();

		//check if the APIC exists
		if (ioapicDiscoveryNumber == 0) {
			computer->features.hasAPIC = false;
		}

		apic = computer->features.hasAPIC;

		picOpen();

		if (apic) {
			picDisable();

			apicOpen();
		}

		installISRHandler(ISR_DIV_BY_ZERO, otherISRHandler);
		installISRHandler(ISR_DEBUG, otherISRHandler);
		installISRHandler(ISR_NMI, nmiHandler);

		installISRHandler(ISR_BREAKPOINT, otherISRHandler);
		installISRHandler(ISR_OVERFLOW, otherISRHandler);
		installISRHandler(ISR_BOUNDS, otherISRHandler);

		installISRHandler(ISR_INVALID_OPCODE, opcodeFault);
		installISRHandler(ISR_DOUBLE_FAULT, doubleFault);

		for (int i = ISR_COPROCESSOR_SEGMENT_OVERRUN; i < ISR_STACK_SEGMENT; ++i) {
			installISRHandler(i, otherISRHandler);
		}

		installISRHandler(ISR_GENERAL_PROTECTION, gpFault);
		installISRHandler(ISR_PAGE_FAULT, pgFault);

		for (int i = ISR_RESERVED; i < ISR_SECURITY_EXCEPTION; ++i) {
			installISRHandler(i, otherISRHandler);
		}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
		installISRHandler(96, reinterpret_cast<void(*)(regs*, void*)>(Sys::systemCall));
#pragma GCC diagnostic pop

		computer->clock = nullptr;

		if (computer->clock == nullptr) {
			RTC* rtc = new RTC();
			rtc->detectionType = DetectionType::ISAProbe;
			computer->addChild(rtc);
			rtc->open(0, 0, nullptr);

			computer->clock = rtc;
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