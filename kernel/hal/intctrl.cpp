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
#include "vm86/x87em.hpp"
#include "vm86/vm8086.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Krnl
{
	ThreadControlBlock* fpuOwner = nullptr;

	char exceptionNames[][32] = {
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
	};
}



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
		intCtrl->eoi(num - 32);
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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

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

	kprintf("EAX: 0x%X\n", r->eax);
	kprintf("EBX: 0x%X\n", r->ebx);
	kprintf("ECX: 0x%X\n", r->ecx);
	kprintf("EDX: 0x%X\n", r->edx);
	kprintf("ESI: 0x%X\n", r->esi);
	kprintf("EDI: 0x%X\n", r->edi);
	kprintf("ESP: 0x%X\n", r->esp);
	kprintf("EBP: 0x%X\n", r->ebp);
	kprintf("USERESP: 0x%X\n", r->useresp);
	kprintf("EIP: 0x%X\n", r->eip);
	kprintf("ERR: 0x%X\n", r->err_code);

	kprintf("CR2: 0x%X\n", (uint32_t) cr2);
	kprintf("CR3: 0x%X\n", cr3);

	setActiveTerminal(kernelProcess->terminal);

	kernelProcess->terminal->puts(Krnl::exceptionNames[r->int_no]);
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
	kernelProcess->terminal->puts("\n CR4: ");
	kernelProcess->terminal->putx((uint32_t) cr4);

	kernelProcess->terminal->puts("\n\n DR0: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR0());
	kernelProcess->terminal->puts("\n DR1: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR1());
	kernelProcess->terminal->puts("\n DR2: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR2());
	kernelProcess->terminal->puts("\n DR3: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR3());
	kernelProcess->terminal->puts("\n DR6: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR6());
	kernelProcess->terminal->puts("\n DR7: ");
	kernelProcess->terminal->putx((uint32_t) CPU::readDR7());

	char* drvName = Thr::getDriverNameFromAddress((size_t) r->eip);
	if (drvName) {
		kprintf("\n DRIVER: %s\n", drvName);
		kernelProcess->terminal->puts("\n\n DRIVER: ");
		kernelProcess->terminal->puts(drvName);
		kernelProcess->terminal->puts("\n\n OFFSET: ");
		kernelProcess->terminal->putx((uint32_t) Thr::getDriverOffsetFromAddress((size_t) r->eip));
		kprintf("\n OFFSET: 0x%X\n", drvName);
	}

	asm("cli;hlt;");
	while (1);

	kprintf("'0x%X'\n", __builtin_return_address(1));
	kprintf("'0x%X'\n", __builtin_return_address(2));
	kprintf("'0x%X'\n", __builtin_return_address(3));

	kernelProcess->terminal->puts("\n 1: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(1));
	kernelProcess->terminal->puts("\n 2: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(2));
	kernelProcess->terminal->puts("\n 3: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(3));
}

void displayProgramFault(const char* text)
{
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(text, VgaColour::White, VgaColour::Maroon);
	}
}

bool (*gpFaultIntercept)(regs* r) = nullptr;

void x87EmulHandler(regs* r, void* context)
{
	kprintf("x87 EMUL HANDLER CALLED.\n");
	size_t cr0 = CPU::readCR0();
	bool handled;

	if (currentTaskTCB->vm86Task) {
		goto bad;
	}

	if (sysBootSettings & 16384) {
		asm volatile ("clts");
		return;
	}

	//no emulation and task switch bit set
	if (cr0 & 8) {
		kprintf("clutzing...\n");

		//clear task switched
		asm volatile ("clts");

		//save previous state
		if (Krnl::fpuOwner) {
			Hal::saveCoprocessor(Krnl::fpuOwner->fpuState);
		}

		//check if never had state before, otherwise load state
		if (currentTaskTCB->fpuState == nullptr) {
			currentTaskTCB->fpuState = Hal::allocateCoprocessorState();

		} else {
			Hal:loadCoprocessor(Krnl::fpuOwner->fpuState);
		}

		Krnl::fpuOwner = currentTaskTCB;
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

void gpFault(regs* r, void* context)
{
	gpFaultIntercept = Vm::faultHandler;
	if (gpFaultIntercept) {
		bool handled = gpFaultIntercept(r);
		if (handled) {
			return;
		}
	}

	kprintf("General Protection Fault!\n");

	displayDebugInfo(r);
	displayProgramFault("General protection fault");

	Thr::terminateFromIRQ();
}

void pgFault(regs* r, void* context)
{
	kprintf("pgFault. EIP = 0x%X\n", r->eip);
	if (currentTaskTCB->processRelatedTo->vas->tryLoadBackOffDisk(CPU::readCR2())) {
		return;
	}

	kprintf("Page Fault!\n");

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
	kprintf("UNHANDLED EXCEPTION 0x%X/%d\n", r->int_no, r->int_no);

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

InterruptController* setupInterruptController()
{
	if (CPU::getNumber() != 0) {
		//start an APIC
		InterruptController* controller = new APIC();
		controller->open(0, 0, nullptr);
		computer->addChild(controller);

		return controller;
	}

	//check if the APIC exists
	if (ioapicDiscoveryNumber == 0) {
		computer->features.hasAPIC = false;
	}

	bool hasAPIC = computer->features.hasAPIC;

	//start a PIC (even if it is just so it gets disabled)
	InterruptController* controller = new PIC();
	controller->open(0, 0, nullptr);

	if (hasAPIC) {
		//disable the PIC
		controller->close(0, 0, nullptr);

		//delete the PIC
		delete controller;

		//start an APIC
		controller = new APIC();
		controller->open(0, 0, nullptr);
	}

	computer->addChild(controller);

	Krnl::fpuOwner = nullptr;

	controller->installISRHandler(ISR_DIV_BY_ZERO, otherISRHandler);
	controller->installISRHandler(ISR_DEBUG, otherISRHandler);
	controller->installISRHandler(ISR_NMI, nmiHandler);
	controller->installISRHandler(ISR_BREAKPOINT, otherISRHandler);
	controller->installISRHandler(ISR_OVERFLOW, otherISRHandler);
	controller->installISRHandler(ISR_BOUNDS, otherISRHandler);
	controller->installISRHandler(ISR_INVALID_OPCODE, opcodeFault);
	controller->installISRHandler(ISR_DEVICE_NOT_AVAILABLE, x87EmulHandler);
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