#include "core/common.hpp"
#include "core/syscalls.hpp"
#include "core/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/pic.hpp"
#include "hw/intctrl/apic.hpp"
#include "hal/device.hpp"
#include "hw/acpi.hpp"
#include "hw/ports.hpp"
#include "hw/cpu.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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
	extern bool kernelInPanic;
	while (kernelInPanic) {
		asm("cli; hlt");
	}

	InterruptController* intCtrl = thisCPU()->intCtrl;

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

	panic("[intctrl] Could not install ISR handler, too many already!");
}

int InterruptController::installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	if (legacy && this->getName()[0] == 'A') {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[installIRQHandler] Legacy IRQ with number 16 or higher");
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

	panic("[intctrl] Could not install IRQ handler, too many already!");
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
			panic("[uninstallIRQHandler] Legacy IRQ with number 16 or higher");
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
			panic("[uninstallIRQHandler] Legacy IRQ with number 16 or higher");
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

InterruptController::InterruptController(const char* name) : Device(name)
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
	asm volatile ("mov %%cr2, %0" : "=r"(cr0)); 
	size_t cr2;
	asm volatile ("mov %%cr2, %0" : "=r"(cr2));
	size_t cr3;
	asm volatile ("mov %%cr3, %0" : "=r"(cr3));
	size_t cr4;
	asm volatile ("mov %%cr4, %0" : "=r"(cr4));

	setActiveTerminal(kernelProcess->terminal);

	kernelProcess->terminal->puts(exceptionNames[r->int_no]);
	kernelProcess->terminal->puts("\n EIP: ");
	kernelProcess->terminal->putx(r->eip);
	kernelProcess->terminal->puts("\n CR0: ");
	kernelProcess->terminal->putx((uint32_t) cr0);
	kernelProcess->terminal->puts("\n CR1: ");
	kernelProcess->terminal->putx((uint32_t) cr1);
	kernelProcess->terminal->puts("\n CR2: ");
	kernelProcess->terminal->putx((uint32_t) cr2);
	kernelProcess->terminal->puts("\n CR3: ");
	kernelProcess->terminal->putx((uint32_t) cr3);
	kernelProcess->terminal->puts("\n ERR: ");
	kernelProcess->terminal->putx((uint32_t) r->err_code);

	kernelProcess->terminal->puts("\n DR0: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR0());
	kernelProcess->terminal->puts("\n DR1: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR1());
	kernelProcess->terminal->puts("\n DR2: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR2());
	kernelProcess->terminal->puts("\n DR3: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR3());
	kernelProcess->terminal->puts("\n DR6: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR6());
	kernelProcess->terminal->puts("\n DR7: ");
	kernelProcess->terminal->putx((uint32_t) thisCPU()->readDR7());
	asm("cli;hlt;");
	while (1);

	kernelProcess->terminal->puts("\n 1: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(1));
	kernelProcess->terminal->puts("\n 2: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(2));
	kernelProcess->terminal->puts("\n 3: ");
	kernelProcess->terminal->putx((uint32_t) __builtin_return_address(3));

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

	kprintf("'0x%X'\n", __builtin_return_address(1));
	kprintf("'0x%X'\n", __builtin_return_address(2));
	kprintf("'0x%X'\n", __builtin_return_address(3));
}

void displayProgramFault(const char* text)
{
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(text, VgaColour::White, VgaColour::Maroon);
	}
}

bool (*gpFaultIntercept)(regs* r) = nullptr;
void gpFault(regs* r, void* context)
{
	extern bool vm8086FaultHandler(regs * r);
	gpFaultIntercept = vm8086FaultHandler;
	if (gpFaultIntercept) {
		bool handled = gpFaultIntercept(r);
		if (handled) {
			return;
		}
	}

	kprintf("General Protection Fault!\n");

	displayDebugInfo(r);
	displayProgramFault("General protection fault");

	terminateTask();
}

size_t* pf0 = 0;
size_t* pf1 = 0;
size_t* pf2 = 0;
size_t* pf3 = 0;
size_t* pf4 = 0;
size_t* pf5 = 0;

void pgFault(regs* r, void* context)
{
	kprintf("Page Fault!\n");

	displayDebugInfo(r);
	displayProgramFault("Page fault");

	terminateTask();
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

	terminateTask();
}

void opcodeFault(regs* r, void* context)
{
	if (thisCPU()->opcodeDetectionMode) {
		kprintf("Opcode detection: invalid opcode.\n");
		r->eip += 64;
		return;
	}

	kprintf("Invalid Opcode!\n");
	kprintf("OPCODE: 0x%X (then 0x%X %X %X)\n", *((uint8_t*)(0 + r->eip + r->cs * 16)), *((uint8_t*) (1 + r->eip + r->cs * 16)), *((uint8_t*) (2 + r->eip + r->cs * 16)), *((uint8_t*) (3 + r->eip + r->cs * 16)));
	
	displayDebugInfo(r);
	displayProgramFault("Opcode fault");

	terminateTask();
}

#pragma GCC diagnostic pop

void doubleFault(regs* r, void* context)
{
	panic("DOUBLE FAULT");
}

InterruptController* setupInterruptController()
{
	if (getCPUNumber() != 0) {
		//start an APIC
		InterruptController* controller = new APIC();
		controller->open(0, 0, nullptr);
		computer->addChild(controller);

		return controller;
	}

	//check if the APIC exists
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

	controller->installISRHandler(ISR_DIV_BY_ZERO, otherISRHandler);
	controller->installISRHandler(ISR_DEBUG, otherISRHandler);
	controller->installISRHandler(ISR_NMI, nmiHandler);
	controller->installISRHandler(ISR_BREAKPOINT, otherISRHandler);
	controller->installISRHandler(ISR_OVERFLOW, otherISRHandler);
	controller->installISRHandler(ISR_BOUNDS, otherISRHandler);
	controller->installISRHandler(ISR_INVALID_OPCODE, opcodeFault);
	controller->installISRHandler(ISR_DEVICE_NOT_AVAILABLE, otherISRHandler);
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
	controller->installISRHandler(96, reinterpret_cast<void(*)(regs*, void*)>(systemCall));
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