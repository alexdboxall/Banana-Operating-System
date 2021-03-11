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
#include "hw/ports.hpp"
#include "hw/cpu.hpp"
#include "vm86/vm8086.hpp"

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
	while (Krnl::kernelInPanic) {
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

	kernelProcess->terminal->puts(exceptionNames[r->int_no]);
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

bool (*x87FaultIntercept)(regs* r) = nullptr;
bool (*gpFaultIntercept)(regs* r) = nullptr;

#include <stdint.h>


#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/cpu.hpp"
#include "hw/acpi.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "fs/vfs.hpp"

extern "C" {
#include "libk/string.h"
}

typedef uint64_t Float80;

typedef struct _FPUState
{
	union
	{
		struct
		{
			uint16_t invalidOperation : 1;
			uint16_t denormalisedOperand : 1;
			uint16_t zeroDivide : 1;
			uint16_t overflow : 1;
			uint16_t underflow : 1;
			uint16_t precision : 1;
			uint16_t stackFault : 1;
			uint16_t errSummaryStatus : 1;
			uint16_t c0 : 1;
			uint16_t c1 : 1;
			uint16_t c2 : 1;
			uint16_t stackTop : 3;
			uint16_t c3 : 1;
			uint16_t fpuBusy : 1;
		};

		uint16_t status;
	};

	union
	{
		struct
		{
			uint16_t maskInvalidOperation : 1;
			uint16_t maskDenormalisedOperand : 1;
			uint16_t maskZeroDivide : 1;
			uint16_t maskOverflow : 1;
			uint16_t maskUnderflow : 1;
			uint16_t maskPrecision : 1;
			uint16_t : 2;
			uint16_t precisionControl : 2;
			uint16_t roundingControl : 2;
			uint16_t infinityControl : 1;
			uint16_t : 3;
		};

		uint16_t control;
	};

	Float80 regs[8];
	int valuesOnStack = 0;

} FPUState;

FPUState fpuState;


uint32_t fpuInternalTo32(Float80 flt)
{
	//double -> float

	uint32_t out = 0;
	if (flt >> 63) {
		out |= (1ULL << 31ULL);
	}

	uint64_t significand = flt & 0xFFFFFFFFFFFFFULL;
	uint64_t expo = ((flt >> 52) & 0x7FF) - 1023 + 127;
	if (expo < 0 || expo > 255) {
		//underflow / overflow
		return 0;
	}

	significand >>= 52 - 23;
	out |= significand;
	out |= expo << 23;
	return out;
}

uint64_t fpuInternalTo64(Float80 flt)
{
	// double -> double
	return flt;
}

Float80 fpu32ToInternal(uint32_t flt)
{
	// float -> double
	uint32_t out = 0;
	if (flt >> 31) {
		out |= (1ULL << 63ULL);
	}

	uint64_t significand = flt & 0x7FFFFF;
	uint64_t expo = ((flt >> 23) & 0xFF) - 127 + 1023;

	significand <<= 52 - 23;
	out |= significand;
	out |= expo << 52;
	return out;
}

Float80 fpu64ToInternal(uint64_t flt)
{
	// double -> double
	return flt;
}

int64_t fpuFloatToLong(Float80 flt)
{
	// double -> int

	int expo = ((flt >> 52) & 0x7FF) - 1023;
	if (expo < 0) {
		return 0;
	}

	int64_t significand = flt & 0xFFFFFFFFFFFFFULL;
	significand |= (1ULL << 52ULL);
	significand >>= 52 - expo;

	if (flt >> 63) {
		significand = -significand;
	}

	return significand;
}

Float80 fpuULongToFloat(uint64_t significand)
{
	// unsigned long -> double

	int shifts = 0;
	while ((significand & (1ULL << 52ULL)) == 0) {
		significand <<= 1;
		shifts++;
	}

	uint64_t exponent = 1023 + 52 - shifts;
	return (exponent << 52ULL) | (significand & 0xFFFFFFFFFFFFFULL);
}

Float80 fpuLongToFloat(int64_t signedSignificand)
{
	// long -> double

	int shifts = 0;
	bool neg = false;

	uint64_t significand;
	if (signedSignificand > 0) {
		significand = signedSignificand;
	} else {
		significand = -signedSignificand;
		neg = true;
	}

	while ((significand & (1ULL << 52ULL)) == 0) {
		significand <<= 1;
		shifts++;
	}

	uint64_t exponent = 1023 + 52 - shifts;
	uint64_t merged = (exponent << 52ULL) | (significand & 0xFFFFFFFFFFFFFULL);
	if (neg) {
		merged |= (1ULL << 63ULL);
	}
	return merged;
}

Float80 fpuGet0()
{
	return 0;
}

Float80 fpuGet1()
{
	return 1.0;

}

Float80 fpuGetPi()
{
	return 3.141592;
}

Float80 fpuGetLog2E()
{
	return 0xDEADBEEF;
}

Float80 fpuGetLogE2()
{
	return 0xDEADBEEF;
}

Float80 fpuGetLog210()
{
	return 0xDEADBEEF;
}

Float80 fpuGetLog102()
{
	return 0xDEADBEEF;
}

bool fpuIsSecondLarger(Float80 x, Float80 y)
{
	return y > x;
}

bool fpuAreEqual(Float80 x, Float80 y)
{
	return x == y;
}

void fpuUnorderedCompare(Float80 x, Float80 y)
{
	fpuState.c0 = !fpuAreEqual(x, y) && fpuIsSecondLarger(x, y);
	fpuState.c2 = 0;
	fpuState.c3 = fpuAreEqual(x, y);
}

Float80 fpuNormalise(Float80 flt)
{
	return flt;
}

Float80 fpuAdd(Float80 x, Float80 y)
{
	return x + y;
}

Float80 fpuAbs(Float80 x)
{
	if (x < 0.0) {
		x = -x;
	}
	return x;
}

Float80 fpuChs(Float80 x)
{
	return -x;
}

Float80 fpuSub(Float80 x, Float80 y)
{
	return fpuAdd(x, -y);
}

Float80 fpuMultiply(Float80 x, Float80 y)
{
	return x * y;
}

Float80 fpuDivide(Float80 x, Float80 y)
{
	return x / y;
}

Float80 fpuSquare(Float80 flt)
{
	return fpuMultiply(flt, flt);
}

Float80 fpuGetReg(int num)
{
	if (num < 0 || num > 7) {
		panic("em8087 bad reg set");
	}
	return fpuState.regs[(fpuState.stackTop + num) % 8];
}

void fpuSetReg(int num, Float80 flt)
{
	if (num < 0 || num > 7) {
		panic("em8087 bad reg set");
	}
	fpuState.regs[(fpuState.stackTop + num) % 8] = flt;
}

void fpuPush(Float80 flt)
{
	fpuState.stackTop = (fpuState.stackTop + 7) % 8;
	fpuState.regs[fpuState.stackTop] = flt;
	if (fpuState.valuesOnStack == 8) {
		fpuState.stackFault = 1;
	} else {
		fpuState.valuesOnStack++;
	}
}

Float80 fpuPop()
{
	Float80 v = fpuState.regs[fpuState.stackTop];
	fpuState.stackTop = (fpuState.stackTop + 1) % 8;
	if (fpuState.valuesOnStack) {
		--fpuState.valuesOnStack;
	} else {
		fpuState.stackFault = 1;
	}
	return v;
}

bool x87Handler(regs* r)
{
	uint8_t* eip = (uint8_t*) r->eip;

	uint8_t* ptr = 0;
	bool registerOnly = false;
	int instrLen = 2;
	uint8_t middleDigit;

	ptr = CPU::decodeAddress(r, &instrLen, &registerOnly, &middleDigit);

	//kprintf("x87 0x%X\n", eip);

	kprintf("r->esp = 0x%X\n", r->esp);
	kprintf("x87: %X %X %X %X\n", *eip, *(eip + 1), *(eip + 2), *(eip + 3));
	kprintf("decoded address = 0x%X\n", ptr);

	if (eip[0] == 0xD9) {
		switch (eip[1]) {
		case 0xE0:
			fpuSetReg(0, fpuChs(fpuGetReg(0)));
			r->eip += 2;
			return true;
		case 0xE1:              //FABS
			fpuSetReg(0, fpuAbs(fpuGetReg(0)));
			r->eip += 2;
			return true;
		case 0xE8:              //FLD1
			fpuPush(fpuGet1());
			r->eip += 2;
			return true;
		case 0xE9:              //FLD1
			fpuPush(fpuGetLog210());
			r->eip += 2;
			return true;
		case 0xEA:              //FLD1
			fpuPush(fpuGetLog2E());
			r->eip += 2;
			return true;
		case 0xEB:              //FLD1
			fpuPush(fpuGetPi());
			r->eip += 2;
			return true;
		case 0xEC:              //FLD1
			fpuPush(fpuGetLog102());
			r->eip += 2;
			return true;
		case 0xED:              //FLD1
			fpuPush(fpuGetLogE2());
			r->eip += 2;
			return true;
		case 0xEE:              //FLD1
			fpuPush(fpuGet0());
			r->eip += 2;
			return true;
		default:
			break;
		}
	}

	if (eip[0] == 0xD8 && eip[1] >= 0xC0 && eip[1] <= 0xC7) {           //FADD
		fpuSetReg(0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xD0 && eip[1] <= 0xD7) {     //FCOM
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xD0));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xD8 && eip[1] <= 0xDF) {     //FCOMP
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xD8));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FSUB
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUBR
		fpuSetReg(0, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVP
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xD8 && eip[1] >= 0xF8 /*&& eip[1] <= 0xFF*/) {     //FDIVRP
		fpuSetReg(0, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xD9 && eip[1] >= 0xC0 && eip[1] <= 0xC7) {      //FLD
		fpuPush(fpuGetReg(eip[1] - 0xC0));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD9 && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FXCH
		Float80 st1 = fpuGetReg(eip[1] - 0xC8);
		fpuSetReg(eip[1] - 0xC8, fpuGetReg(0));
		fpuSetReg(0, st1);
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADD
		fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMUL
		fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDC && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUB
		fpuSetReg(eip[1] - 0xE8, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xC0 && eip[1] <= 0xC7) {     //FADDP
		fpuSetReg(eip[1] - 0xC0, fpuAdd(fpuGetReg(0), fpuGetReg(eip[1] - 0xC0)));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FSUBRP
		fpuSetReg(eip[1] - 0xE0, fpuSub(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0)));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FSUBP
		fpuSetReg(eip[1] - 0xE8, fpuSub(fpuGetReg(eip[1] - 0xE8), fpuGetReg(0)));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xC8 && eip[1] <= 0xCF) {     //FMULP
		fpuSetReg(eip[1] - 0xC8, fpuMultiply(fpuGetReg(0), fpuGetReg(eip[1] - 0xC8)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xF8 /*&& eip[1] <= 0xFF*/) {     //FDIVP
		fpuSetReg(eip[1] - 0xF8, fpuDivide(fpuGetReg(eip[1] - 0xF8), fpuGetReg(0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xDE && eip[1] >= 0xF0 && eip[1] <= 0xF7) {     //FDIVRP
		fpuSetReg(eip[1] - 0xF0, fpuDivide(fpuGetReg(0), fpuGetReg(eip[1] - 0xF0)));
		r->eip += 2;
		fpuPop();
		return true;

	} else if (eip[0] == 0xDD && eip[1] >= 0xD0 && eip[1] <= 0xD7) {     //FST
		fpuSetReg(eip[1] - 0xD0, fpuGetReg(0));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDD && eip[1] >= 0xD8 && eip[1] <= 0xDF) {     //FSTP
		fpuSetReg(eip[1] - 0xD8, fpuGetReg(0));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDD && eip[1] >= 0xE0 && eip[1] <= 0xE7) {     //FUCOM
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xE0));
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDD && eip[1] >= 0xE8 && eip[1] <= 0xEF) {     //FUCOM
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(eip[1] - 0xE8));
		fpuPop();
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xDA && eip[1] == 0xE9) {                      //FUCOMPP
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(1));
		r->eip += 2;
		fpuPop();
		fpuPop();
		return true;

	} else if (eip[0] == 0xDE && eip[1] == 0xD9) {                      //FCOMPP
		fpuUnorderedCompare(fpuGetReg(0), fpuGetReg(1));
		r->eip += 2;
		fpuPop();
		fpuPop();
		return true;

	} else if (eip[0] == 0xDF && eip[1] == 0xE0) {                      //FNSTSW
		r->eax &= ~0xFFFF;
		r->eax |= fpuState.status;
		r->eip += 2;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 0) {                    //FADD
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuAdd(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 1) {                    //FMUL
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 4) {                    //FSUB
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 5) {                    //FSUBR
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuSub(fpu32ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 6) {                    //FDIV
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu32ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD8 && middleDigit == 7) {                    //FDIVR
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpu32ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 0) {                    //FLD
		uint32_t* p = (uint32_t*) ptr;
		fpuPush(fpu32ToInternal(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 3) {                    //FSTP
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuInternalTo32(fpuPop());
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 5) {                      //FLDCW
		uint16_t* p = (uint16_t*) ptr;
		fpuState.control = *p;
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xD9 && middleDigit == 7) {                      //FNSTCW
		uint16_t* p = (uint16_t*) ptr;
		*p = fpuState.control;
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDA && middleDigit == 1) {                    //FIMUL
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuLongToFloat(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDA && middleDigit == 4) {                    //FISUB
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpuLongToFloat(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDA && middleDigit == 7) {                    //FISUB
		uint32_t* p = (uint32_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuLongToFloat(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDB && middleDigit == 0) {                    //FILD
		uint32_t* p = (uint32_t*) ptr;
		fpuPush(fpuULongToFloat(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDB && middleDigit == 2) {                      //FIST
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuFloatToLong(fpuGetReg(0));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDB && middleDigit == 3) {                      //FISTP
		uint32_t* p = (uint32_t*) ptr;
		*p = fpuFloatToLong(fpuPop());
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 0) {                    //FADD
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuAdd(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 1) {                    //FMUL
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 2) {                    //FCOM
		uint64_t* p = (uint64_t*) ptr;
		fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 3) {                     //FCOMP
		uint64_t* p = (uint64_t*) ptr;
		fpuUnorderedCompare(fpuGetReg(0), fpu64ToInternal(*p));
		fpuPop();
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 4) {                    //FSUB
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuSub(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 5) {                    //FSUBR
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuSub(fpu64ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 6) {                    //FDIV
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuDivide(fpuGetReg(0), fpu64ToInternal(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDC && middleDigit == 7) {                    //FDIVR
		uint64_t* p = (uint64_t*) ptr;
		fpuSetReg(0, fpuDivide(fpu64ToInternal(*p), fpuGetReg(0)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDD && middleDigit == 0) {                    //FLD
		uint64_t* p = (uint64_t*) ptr;
		fpuPush(fpu64ToInternal(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDD && middleDigit == 2) {                    //FST
		uint64_t* p = (uint64_t*) ptr;
		*p = fpuInternalTo64(fpuGetReg(0));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDD && middleDigit == 3) {                    //FSTP
		uint64_t* p = (uint64_t*) ptr;
		*p = fpuInternalTo64(fpuPop());
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDE && middleDigit == 1) {                    //FIMUL 16
		uint16_t* p = (uint16_t*) ptr;
		fpuSetReg(0, fpuMultiply(fpuGetReg(0), fpuLongToFloat(*p)));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDF && middleDigit == 5) {                    //FILD
		uint64_t* p = (uint64_t*) ptr;
		fpuPush(fpuULongToFloat(*p));
		r->eip += instrLen;
		return true;

	} else if (eip[0] == 0xDF && middleDigit == 7) {                    //FISTP
		uint64_t* p = (uint64_t*) ptr;
		*p = fpuFloatToLong(fpuPop());
		r->eip += instrLen;
		return true;
	}

	return false;
}


void x87EmulHandler(regs* r, void* context)
{
	if (!x87FaultIntercept) {
		x87FaultIntercept = x87Handler;

		//Thr::executeDLL(Thr::loadDLL("C:/Banana/Drivers/em8087.sys"), computer);
	}

	if (x87FaultIntercept) {
		bool handled = x87FaultIntercept(r);
		if (handled) {
			return;
		}
	}

	kprintf("General Protection Fault!\n");

	displayDebugInfo(r);
	displayProgramFault("x87 not available");

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

extern "C" void voodooXADD(size_t, int, int);

void opcodeFault(regs* r, void* context)
{
	if (thisCPU()->opcodeDetectionMode) {
		kprintf("Opcode detection: invalid opcode.\n");
		r->eip += 25;
		return;
	}

	//emulate instructions added to the 486 and Pentium

	uint8_t* eip = (uint8_t*) r->eip;

	//lock prefix
	bool hasNonLockPrefix = false;
	bool has66Prefix = false;

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
		has66Prefix = true;
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

	//XADD
	if (eip[0] == 0x0F && (eip[1] == 0xC2 || eip[1] == 0xC3)) {
		kprintf("XADD HANDLER.\n");
		r->eip++;
		eip++;

		*eip -= 2;

		int instrLen;
		bool regOnly;
		uint8_t regNum;

		//get the instruction length
		CPU::decodeAddress(r, &instrLen, &regOnly, &regNum);

		int trueLength = instrLen + (r->eip - originalEIP);
		int opcodeStart = (r->eip - originalEIP) - 1;			//the 0xF starts here

		r->eip = originalEIP;
		voodooXADD((size_t) r, trueLength, opcodeStart);
		r->eip = originalEIP + trueLength;
		return;
	}

	//BSWAP		introduced with i486
	if (eip[0] == 0x0F && eip[1] >= 0xC8 && eip[1] <= 0xCF) {
		uint32_t in;
		uint8_t base = eip[1] - 0xC8;

		if (base == 0) in = r->eax;
		else if (base == 1) in = r->ecx;
		else if (base == 2) in = r->edx;
		else if (base == 3) in = r->ebx;
		else if (base == 4) in = r->useresp;
		else if (base == 5) in = r->ebp;
		else if (base == 6) in = r->esi;
		else if (base == 7) in = r->edi;

		if (has66Prefix) {
			//undefined behavior

			in &= ~0xFFFF;
			in |= 0xDEAD;

		} else {

			in = (in << 24) | ((in << 8) & 0x00FF0000) | ((in >> 8) & 0x0000FF00) | (in >> 24);
		}

		if (base == 0) r->eax = in;
		else if (base == 1) r->ecx = in;
		else if (base == 2) r->edx = in;
		else if (base == 3) r->ebx = in;
		else if (base == 4) r->useresp = in;
		else if (base == 5) r->ebp = in;
		else if (base == 6) r->esi = in;
		else if (base == 7) r->edi = in;

		r->eip += 2;
		return;
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
	kprintf("OPCODE: 0x%X (then 0x%X %X %X)\n", *((uint8_t*) (0 + r->eip + r->cs * 16)), *((uint8_t*) (1 + r->eip + r->cs * 16)), *((uint8_t*) (2 + r->eip + r->cs * 16)), *((uint8_t*) (3 + r->eip + r->cs * 16)));

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