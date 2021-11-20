#include <arch/i386/hal.hpp>
#include <arch/i386/pic.hpp>
#include <arch/i386/rtc.hpp>
#include <arch/i386/x86.hpp>

#include <hw/cpu.hpp>
#include <vm86/x87em.hpp>

#include <krnl/common.hpp>
#include <krnl/fault.hpp>
#include <krnl/physmgr.hpp>
#include <krnl/panic.hpp>
#include <krnl/virtmgr.hpp>
#include <krnl/hal.hpp>

#include <sys/syscalls.hpp>
#include <thr/elf.hpp>
#include <thr/prcssthr.hpp>
#include <hal/intctrl.hpp>
#include <hw/intctrl/pic.hpp>
#include <hw/intctrl/apic.hpp>
#include <hal/device.hpp>
#include <hw/acpi.hpp>
#include <hw/cpu.hpp>
#include <vm86/vm8086.hpp>


x86Features features;

enum class CPUVendor
{
	Unknown,
	Intel,
	AMD,
	Cyrix,
	VIA,
	TransMeta,
	Centaur,
	Nexgen,
	UMC,
	SIS,
	NSC,
	Rise,
	Vortex,
	VirtualMachine,
};

bool opcodeDetectionMode = false;

CPUVendor vendor;
uint8_t steppingID;
uint8_t processorType;
uint8_t model;
uint8_t familyID;

char vendorIDString[13];

#define PORT_SYSTEM_CONTROL_A	0x92
#define PORT_SYSTEM_CONTROL_B	0x61
#define PORT_CMOS_BASE			0x70	

extern "C" int detectCPUID();
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

bool nmi = false;

size_t HalPageGlobalFlag = 0;
size_t HalPageWriteCombiningFlag = 0;

uint8_t x86ReadCMOS(uint8_t reg)
{
	outb(PORT_CMOS_BASE + 0, reg | (nmi ? 0 : 0x80));
	return inb(PORT_CMOS_BASE + 1);
}

void x86WriteCMOS(uint8_t reg, uint8_t val)
{
	outb(PORT_CMOS_BASE + 0, reg | (nmi ? 0 : 0x80));
	outb(PORT_CMOS_BASE + 1, val);
}

extern "C" size_t is486();
extern "C" size_t hasLegacyFPU();

enum cpuid_requests
{
	CPUID_GETVENDORSTRING,
	CPUID_GETFEATURES,
	CPUID_GETTLB,
	CPUID_GETSERIAL,
	CPUID_GETEXTENDED = 7,
	CPUID_GETHIGHEST = 0x80000000,
	CPUID_INTELEXTENDED = 0x80000001,
	CPUID_INTELFEATURES,
	CPUID_INTELBRANDSTRING,
	CPUID_INTELBRANDSTRINGMORE,
	CPUID_INTELBRANDSTRINGEND,
};

enum CPUID_Features
{
	CPUID_FEAT_ECX_SSE3 = 1 << 0,
	CPUID_FEAT_ECX_PCLMUL = 1 << 1,
	CPUID_FEAT_ECX_DTES64 = 1 << 2,
	CPUID_FEAT_ECX_MONITOR = 1 << 3,
	CPUID_FEAT_ECX_DS_CPL = 1 << 4,
	CPUID_FEAT_ECX_VMX = 1 << 5,
	CPUID_FEAT_ECX_SMX = 1 << 6,
	CPUID_FEAT_ECX_EST = 1 << 7,
	CPUID_FEAT_ECX_TM2 = 1 << 8,
	CPUID_FEAT_ECX_SSSE3 = 1 << 9,
	CPUID_FEAT_ECX_CID = 1 << 10,
	CPUID_FEAT_ECX_FMA = 1 << 12,
	CPUID_FEAT_ECX_CX16 = 1 << 13,
	CPUID_FEAT_ECX_ETPRD = 1 << 14,
	CPUID_FEAT_ECX_PDCM = 1 << 15,
	CPUID_FEAT_ECX_PCIDE = 1 << 17,
	CPUID_FEAT_ECX_DCA = 1 << 18,
	CPUID_FEAT_ECX_SSE4_1 = 1 << 19,
	CPUID_FEAT_ECX_SSE4_2 = 1 << 20,
	CPUID_FEAT_ECX_x2APIC = 1 << 21,
	CPUID_FEAT_ECX_MOVBE = 1 << 22,
	CPUID_FEAT_ECX_POPCNT = 1 << 23,
	CPUID_FEAT_ECX_AES = 1 << 25,
	CPUID_FEAT_ECX_XSAVE = 1 << 26,
	CPUID_FEAT_ECX_OSXSAVE = 1 << 27,
	CPUID_FEAT_ECX_AVX = 1 << 28,

	CPUID_FEAT_EDX_FPU = 1 << 0,
	CPUID_FEAT_EDX_VME = 1 << 1,
	CPUID_FEAT_EDX_DE = 1 << 2,
	CPUID_FEAT_EDX_PSE = 1 << 3,
	CPUID_FEAT_EDX_TSC = 1 << 4,
	CPUID_FEAT_EDX_MSR = 1 << 5,
	CPUID_FEAT_EDX_PAE = 1 << 6,
	CPUID_FEAT_EDX_MCE = 1 << 7,
	CPUID_FEAT_EDX_CX8 = 1 << 8,
	CPUID_FEAT_EDX_APIC = 1 << 9,
	CPUID_FEAT_EDX_SEP = 1 << 11,
	CPUID_FEAT_EDX_MTRR = 1 << 12,
	CPUID_FEAT_EDX_PGE = 1 << 13,
	CPUID_FEAT_EDX_MCA = 1 << 14,
	CPUID_FEAT_EDX_CMOV = 1 << 15,
	CPUID_FEAT_EDX_PAT = 1 << 16,
	CPUID_FEAT_EDX_PSE36 = 1 << 17,
	CPUID_FEAT_EDX_PSN = 1 << 18,
	CPUID_FEAT_EDX_CLF = 1 << 19,
	CPUID_FEAT_EDX_DTES = 1 << 21,
	CPUID_FEAT_EDX_ACPI = 1 << 22,
	CPUID_FEAT_EDX_MMX = 1 << 23,
	CPUID_FEAT_EDX_FXSR = 1 << 24,
	CPUID_FEAT_EDX_SSE = 1 << 25,
	CPUID_FEAT_EDX_SSE2 = 1 << 26,
	CPUID_FEAT_EDX_SS = 1 << 27,
	CPUID_FEAT_EDX_HTT = 1 << 28,
	CPUID_FEAT_EDX_TM1 = 1 << 29,
	CPUID_FEAT_EDX_IA64 = 1 << 30,
	CPUID_FEAT_EDX_PBE = 1 << 31
};

int lastCode = -1;
size_t lastA = 0;
size_t lastB = 0;
size_t lastC = 0;
size_t lastD = 0;


#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" /* early engineering samples of AMD K5 processor */
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA1         "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"
#define CPUID_VENDOR_VORTEX       "Vortex86 SoC"
#define CPUID_VENDOR_VIA2         "VIA VIA VIA "

#define CPUID_VENDOR_VMWARE       "VMwareVMware"
#define CPUID_VENDOR_XENHVM       "XenVMMXenVMM"
#define CPUID_VENDOR_MICROSOFT_HV "Microsoft Hv"
#define CPUID_VENDOR_PARALLELS    " lrpepyh vr"


void AMD_K6_writeback(int family, int model, int stepping)
{
	/* mem_end == top of memory in bytes */
	int mem = (Phys::highestMem >> 20) / 4; /* turn into 4mb aligned pages */
	int c;
	REGS regs;

	if (family == 5) {
		c = model;

		/* model 8 stepping 0-7 use old style, 8-F use new style */
		if (model == 8) {
			if (stepping < 8)
				c = 7;
			else
				c = 9;
		}

		switch (c) {
			/* old style write back */
		case 6:
		case 7:
			AMD_K6_read_msr(0xC0000082, &regs);
			AMD_K6_write_msr(0xC0000082, ((mem << 1) & 0x7F), 0, &regs);
			break;

			/* new style write back */
		case 9:
			AMD_K6_read_msr(0xC0000082, &regs);
			AMD_K6_write_msr(0xC0000082, ((mem << 22) & 0x3FF), 0, &regs);
			break;
		default:    /* dont set it on Unknowns + k5's */
			break;
		}
	}
}

void AMD_K6_write_msr(uint32_t msr, uint32_t v1, uint32_t v2, REGS* regs)
{
	asm __volatile__("pusha");
	asm __volatile__(
		"pushfl\n"
		"cli\n"
		"wbinvd\n"
		"wrmsr\n"
		"popfl\n"
		: "=a" (regs->eax)
		: "a" (v1),
		"d" (v2),
		"c" (msr)
	);
	asm __volatile__("popa");

}

void AMD_K6_read_msr(uint32_t msr, REGS* regs)
{
	asm __volatile__("pusha");
	asm __volatile__(
		"pushfl\n"
		"cli\n"
		"wbinvd\n"
		"xorl %%eax, %%eax\n"
		"xorl %%edx, %%edx\n"
		"rdmsr\n"
		"popfl\n"
		: "=a" (regs->eax)
		: "c" (msr)
	);
	asm __volatile__("popa");
}

void cpuid(int code, size_t* a, size_t* b, size_t* c, size_t* d)
{
	if (code == lastCode) {
		*a = lastA;
		*b = lastB;
		*c = lastC;
		*d = lastD;
		return;
	}
	asm volatile ("cpuid" : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d) : "a"(code), "c"(0) : "cc");
	lastCode = code;
	lastA = *a;
	lastB = *b;
	lastC = *c;
	lastD = *d;
}

bool cpuidCheckEDX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
	return edx & check;
}

bool cpuidCheckECX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
	return ecx & check;
}

bool cpuidCheckExtendedEBX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETEXTENDED, &eax, &ebx, &ecx, &edx);
	return ebx & check;
}

bool cpuidCheckExtendedECX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETEXTENDED, &eax, &ebx, &ecx, &edx);
	return ecx & check;
}

void HalDetectFeatures()
{
	features.hasACPI = true;

	features.hasCR8 = false;
	features.hasSMAP = false;
	features.hasSysenter = false;
	features.hasSyscall = false;
	features.hasRDRAND = false;
	features.hasTSC = false;
	features.hasPAE = false;
	features.hasPSE = false;
	features.hasGlobalPages = false;
	features.hasPAT = false;
	features.hasSMEP = false;
	features.hasRDSEED = false;
	features.hasUMIP = false;
	features.hasMTRR = false;
	features.onboardFPU = false;
	features.hasTPAUSE = false;
	features.hasAPIC = false;
	features.hasCPUID = false;
	features.hasMSR = false;
	features.hasx87 = false;
	features.hasMMX = false;
	features.has3DNow = false;
	features.hasSSE = false;
	features.hasSSE2 = false;
	features.hasSSE3 = false;
	features.hasSSE41 = false;
	features.hasSSE42 = false;
	features.hasSSSE3 = false;
	features.hasAVX = false;
	features.hasAVX512 = false;
	features.hasNXBit = false;
	features.hasLongMode = false;
	features.hasMCE = false;
	features.hasCPUID = detectCPUID() ? true : false;

	if (features.hasCPUID) {
		features.hasMSR = cpuidCheckEDX(CPUID_FEAT_EDX_MSR);
		features.hasSSE2 = cpuidCheckEDX(CPUID_FEAT_EDX_SSE2);
		features.hasMCE = cpuidCheckEDX(CPUID_FEAT_EDX_MCE);
		features.hasMMX = cpuidCheckEDX(CPUID_FEAT_EDX_MMX);

		if ((sysBootSettings & 1) || (sysBootSettings & 1024)) {
			features.hasAPIC = false;
		} else {
			features.hasAPIC = cpuidCheckEDX(CPUID_FEAT_EDX_APIC);
		}

		if (features.hasAPIC && !features.hasMSR) {
			features.hasAPIC = false;
		}

		//features.hasAPIC = false;

		bool ecxCanReturnFeatures = true;
		ecxCanReturnFeatures = false;

		if (ecxCanReturnFeatures) {
			features.hasSSE3 = cpuidCheckECX(CPUID_FEAT_ECX_SSE3);
			features.hasSSSE3 = cpuidCheckECX(CPUID_FEAT_ECX_SSSE3);
			features.hasSSE41 = cpuidCheckECX(CPUID_FEAT_ECX_SSE4_1);
			features.hasSSE42 = cpuidCheckECX(CPUID_FEAT_ECX_SSE4_2);
		}

		size_t eax, ebx, ecx, edx;
		cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
		if (eax >= 0x80000001) {
			cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			features.has3DNow = edx & (1 << 31);
			features.hasLongMode = edx & (1 << 29);
			features.hasNXBit = edx & (1 << 20);
		}
	}

	if (sysBootSettings & 1024) {
		features.hasACPI = false;
	}

	opcodeDetectionMode = true;

	memset(vendorIDString, 0, 13);

	if (features.hasCPUID) {
		features.hasTSC = cpuidCheckEDX(CPUID_FEAT_EDX_TSC);
		features.hasPAE = cpuidCheckEDX(CPUID_FEAT_EDX_PAE);
		features.hasPSE = cpuidCheckEDX(CPUID_FEAT_EDX_PSE);
		features.hasGlobalPages = cpuidCheckEDX(CPUID_FEAT_EDX_PGE);
		features.hasPAT = cpuidCheckEDX(CPUID_FEAT_EDX_PAT);
		features.onboardFPU = cpuidCheckEDX(CPUID_FEAT_EDX_FPU);
		features.hasSysenter = cpuidCheckEDX(CPUID_FEAT_EDX_SEP);

		if (features.hasGlobalPages) {
			HalPageGlobalFlag = (1 << 8);
		}
		if (features.hasPAT) {
			HalPageWriteCombiningFlag = (1 << 7);
		}

		size_t eax, ebx, ecx, edx;
		cpuid(0, &eax, &ebx, &ecx, &edx);
		memcpy(vendorIDString + 0, &ebx, 4);
		memcpy(vendorIDString + 4, &edx, 4);
		memcpy(vendorIDString + 8, &ecx, 4);

		if (!strcmp(vendorIDString, CPUID_VENDOR_OLDAMD) || !strcmp(vendorIDString, CPUID_VENDOR_AMD)) vendor = CPUVendor::AMD;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_VIA1) || !strcmp(vendorIDString, CPUID_VENDOR_VIA2)) vendor = CPUVendor::VIA;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_OLDTRANSMETA) || !strcmp(vendorIDString, CPUID_VENDOR_TRANSMETA)) vendor = CPUVendor::TransMeta;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_INTEL)) vendor = CPUVendor::Intel;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_CYRIX)) vendor = CPUVendor::Cyrix;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_CENTAUR)) vendor = CPUVendor::Centaur;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_NEXGEN)) vendor = CPUVendor::Nexgen;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_UMC)) vendor = CPUVendor::UMC;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_SIS)) vendor = CPUVendor::SIS;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_NSC)) vendor = CPUVendor::NSC;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_RISE)) vendor = CPUVendor::Rise;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_VORTEX)) vendor = CPUVendor::Vortex;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_VMWARE)) vendor = CPUVendor::VirtualMachine;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_XENHVM)) vendor = CPUVendor::VirtualMachine;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_MICROSOFT_HV)) vendor = CPUVendor::VirtualMachine;
		else if (!strcmp(vendorIDString, CPUID_VENDOR_PARALLELS)) vendor = CPUVendor::VirtualMachine;
		else vendor = CPUVendor::Unknown;

		if (eax >= 7) {
			features.hasSMEP = cpuidCheckExtendedEBX(1 << 7);
			features.hasSMAP = cpuidCheckExtendedEBX(1 << 20);
			features.hasRDSEED = cpuidCheckExtendedEBX(1 << 18);
			features.hasUMIP = cpuidCheckExtendedECX(1 << 2);
			features.hasTPAUSE = cpuidCheckExtendedECX(1 << 5);
		}

		cpuid(1, &eax, &ebx, &ecx, &edx);
		steppingID = eax & 0xF;
		model = (eax >> 4) & 0xF;
		familyID = (eax >> 8) & 0xF;
		processorType = (eax >> 12) & 3;
		if (familyID == 6 || familyID == 15) {
			model |= (((eax >> 16) & 0xF) << 4);
		}
		if (familyID == 15) {
			familyID += ((eax >> 20) & 0xFF);
		}

		bool ecxCanReturnFeatures = false;
		if (ecxCanReturnFeatures) {
			features.hasRDRAND = cpuidCheckECX(1 << 30);
		}

		features.hasINVLPG = 1;
		features.hasINVD = 1;
		features.hasWBINVD = 1;

		cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
		if (eax >= 0x80000001) {
			cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			features.hasCR8 = ecx & (1 << 4);
			features.hasMTRR = edx & (1 << 12);
			features.hasSyscall = edx & (1 << 11);
		}
	}
	else {
		//either an i386 or an i486

		strcpy(vendorIDString, CPUID_VENDOR_INTEL);
		vendor = CPUVendor::Intel;

		if (is486()) {
			features.hasINVLPG = 1;
			features.hasINVD = 1;
			features.hasWBINVD = 1;

			size_t cr0 = CPU::readCR0();
			if ((cr0 & (1 << 2)) && !(cr0 & (1 << 4))) {
				features.onboardFPU = false;

			}
			else {
				features.onboardFPU = hasLegacyFPU();
			}

		}
		else {
			features.hasINVLPG = 0;
			features.hasINVD = 0;
			features.hasWBINVD = 0;

			size_t cr0 = CPU::readCR0();
			if ((cr0 & (1 << 2)) && !(cr0 & (1 << 4))) {
				features.onboardFPU = false;

			}
			else {
				features.onboardFPU = hasLegacyFPU();
			}
		}
	}

	if (!features.onboardFPU) {
		features.onboardFPU = hasLegacyFPU();
	}

	if (features.onboardFPU) {
		features.hasx87 = true;
	}

	if (!features.hasx87) {
		features.hasx87 = x87Detect();
	}
	if (features.hasSSE2) features.hasSSE = true;
	if (features.hasSSE3) features.hasSSE = true;
	if (features.hasSSE41) features.hasSSE = true;
	if (features.hasSSE42) features.hasSSE = true;

	if (features.hasx87 && !features.hasSSE) {
		features.hasSSE = sseDetect();
	}
	if (features.hasSSE && !features.hasAVX) {
		features.hasAVX = false;
	}

	opcodeDetectionMode = false;
}

void HalEnableNMI()
{
	nmi = true;
	x86ReadCMOS(0x10);
}

void HalDisableNMI()
{
	nmi = false;
	x86ReadCMOS(0x10);
}

bool HalGetNMIState()
{
	return nmi;
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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

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

uint64_t x86rdmsr(uint32_t msr_id)
{
	if (!features.hasMSR) {
		KePanic("RDMSR");
	}

	uint64_t msr_value;
	asm volatile ("rdmsr" : "=A" (msr_value) : "c" (msr_id));
	return msr_value;
}

void x86wrmsr(uint32_t msr_id, uint64_t msr_value)
{
	if (!features.hasMSR) {
		KePanic("WRMSR");
	}

	asm volatile ("wrmsr" : : "c" (msr_id), "A" (msr_value));
}

bool HalHandleGeneralProtectionFault(void* rr, void* ctxt)
{
	return Vm::faultHandler((regs*) rr);
}

uint8_t* HalFindRSDP()
{
	if (Phys::usablePages < 2048 || (sysBootSettings & 1024)) {
		features.hasACPI = false;
	}
	if (!features.hasACPI) {
		return 0;
	}

	uint8_t* ptr = (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0x0);

	for (; ptr < (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0xFFFFF); ptr += 16) {
		if (!memcmp((char*) ptr, "RSD PTR ", 8)) {
			return ptr;
		}
	}

	features.hasACPI = false;

	return 0;
}

bool HalHandlePageFault(void* rr, void* ctxt)
{
	return currentTaskTCB->processRelatedTo->vas->tryLoadBackOffDisk(CPU::readCR2());
}

bool HalHandleOpcodeFault(void* rr, void* ctxt)
{
	regs* r = (regs*) rr;

	if (opcodeDetectionMode) {
		kprintf("Opcode detection: invalid opcode.\n");
		r->eip += 25;
		return true;
	}

	return false;
}

void HalDisplayDebugInfo(void* rr)
{
	regs* r = (regs*) rr;

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

	kprintf("ERROR: %d, %s\n", r->int_no, exceptionNames[r->int_no]);

	setActiveTerminal(kernelProcess->terminal);

	kernelProcess->terminal->puts("\n FAULT NUM: ");
	kernelProcess->terminal->putx(r->int_no);
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

void HalReceivedNMI()
{
	uint8_t sysA = inb(PORT_SYSTEM_CONTROL_A);
	uint8_t sysB = inb(PORT_SYSTEM_CONTROL_B);

	kprintf("RECEIVED AN NMI\n");

	if (sysA & (1 << 4)) {
		KePanic("WATCHDOG NMI");
	}

	if (sysB & (1 << 6)) {
		KePanic("BUS ERROR");
	}

	if (sysB & (1 << 7)) {
		KePanic("MEMORY ERROR");
	}
}

extern "C" void doTPAUSE();
void HalSystemIdle()
{
	if (features.hasTPAUSE) {
		uint64_t msr = x86rdmsr(0xE1);
		x86wrmsr(0xE1, msr & 2);	//only keep bit 1 as it is reserved
		doTPAUSE();

	} else {
		HalStallProcessor();
	}
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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


void noCopro(size_t a)
{

}

ThreadControlBlock* fpuOwner = nullptr;

void x87EmulHandler(regs* r, void* context)
{
	if (currentTaskTCB->vm86Task) {
		KePanic("VM86 CANNOT USE FPU");
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

	kprintf("Device not available\n");
	Thr::terminateFromIRQ();
}

void HalInitialiseCoprocessor()
{
	fpuOwner = nullptr;
	HalInstallISRHandler(ISR_DEVICE_NOT_AVAILABLE, x87EmulHandler);

	/*if (features.hasAVX)
		coproSaveFunc = avxSave;
		coproLoadFunc = avxLoad;
		avxInit();
		return;
	}*/

	if (features.hasSSE) {
		coproSaveFunc = sseSave;
		coproLoadFunc = sseLoad;
		sseInit();
		return;
	}

	if (features.hasx87) {
		coproSaveFunc = x87Save;
		coproLoadFunc = x87Load;
		x87Init();
		return;
	}

	coproSaveFunc = noCopro;
	coproLoadFunc = noCopro;

	CPU::current()->writeCR0(CPU::current()->readCR0() | 4);
}

void (*guiPanicHandler)(char* message);

void HalPanic(const char* message)
{
	HalDisableInterrupts();

	kprintf("\nFATAL SYSTEM ERROR: %s\n", message);

	if (guiPanicHandler) guiPanicHandler((char*) message);

	if (activeTerminal) {
		//give it those classic colours
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		activeTerminal->clearScreen();
		activeTerminal->setTitle((char*) "");
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);

		//print error message
		activeTerminal->puts("\n\n      ");
		activeTerminal->setDefaultColours(VgaColour::Blue, VgaColour::White);
		activeTerminal->puts(" STOP ERROR ");
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		activeTerminal->puts("\n\n");
		activeTerminal->puts("      A problem has occured and Banana cannot continue.\n\n");
		activeTerminal->puts("          ");
		activeTerminal->puts(message);
		activeTerminal->puts("\n\n");
	}

	while (1);

	char* drvName = Thr::getDriverNameFromAddress((size_t) __builtin_return_address(0));
	if (drvName) {
		activeTerminal->puts("      The currently executing driver was:\n\n");
		activeTerminal->puts("          ");
		activeTerminal->puts(drvName);
	} else {
		activeTerminal->puts("      The currently executing task was:\n\n");
		activeTerminal->puts("          ");
		activeTerminal->puts(currentTaskTCB->processRelatedTo->taskname);
	}

	activeTerminal->puts("\n\n\n");
	activeTerminal->puts("      Please restart your computer or press RETURN. If this\n");
	activeTerminal->puts("      screen appears again, hold the 7 key on startup and disable\n");
	activeTerminal->puts("      APIC and ACPI.\n\n\n");

	//endlessly loop
	while (1) {
		char c = inb(0x60);
		if (c == 0x1C || c == 0x5A) {
			uint8_t good = 0x02;
			while (good & 0x02) good = inb(0x64);
			outb(0x64, 0xFE);

			asm("cli; hlt");
		}
	}
}

uint64_t HalQueryPerformanceCounter()
{
	if (features.hasTSC) {
		return 0;
	}
	uint64_t ret;
	asm volatile ("rdtsc" : "=A"(ret));
	return ret;
}

bool apic = false;
void HalInitialise()
{
	//check if the APIC exists
	if (ioapicDiscoveryNumber == 0) {
		features.hasAPIC = false;
	}


	/// DEBUG
	features.hasAPIC = false;
	/// DEBUG


	apic = features.hasAPIC;

	picOpen();

	if (apic) {
		picDisable();
		apicOpen();
	}

	HalInstallISRHandler(ISR_DIV_BY_ZERO, (void (*)(regs*, void*))KeOtherFault);
	HalInstallISRHandler(ISR_DEBUG, (void (*)(regs*, void*))KeOtherFault);
	HalInstallISRHandler(ISR_NMI, (void (*)(regs*, void*))KeNonMaskableInterrupt);

	HalInstallISRHandler(ISR_BREAKPOINT, (void (*)(regs*, void*))KeOtherFault);
	HalInstallISRHandler(ISR_OVERFLOW, (void (*)(regs*, void*))KeOtherFault);
	HalInstallISRHandler(ISR_BOUNDS, (void (*)(regs*, void*))KeOtherFault);

	HalInstallISRHandler(ISR_INVALID_OPCODE, (void (*)(regs*, void*))KeOpcodeFault);
	HalInstallISRHandler(ISR_DOUBLE_FAULT, (void (*)(regs*, void*))KeDoubleFault);

	for (int i = ISR_COPROCESSOR_SEGMENT_OVERRUN; i < ISR_STACK_SEGMENT; ++i) {
		HalInstallISRHandler(i, (void (*)(regs*, void*))KeOtherFault);
	}

	HalInstallISRHandler(ISR_GENERAL_PROTECTION, (void (*)(regs*, void*))KeGeneralProtectionFault);
	HalInstallISRHandler(ISR_PAGE_FAULT, (void (*)(regs*, void*))KePageFault);

	for (int i = ISR_RESERVED; i < ISR_SECURITY_EXCEPTION; ++i) {
		HalInstallISRHandler(i, (void (*)(regs*, void*))KeOtherFault);
	}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
	HalInstallISRHandler(96, reinterpret_cast<void(*)(regs*, void*)>(KeSystemCall));
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

void HalMakeBeep(int hertz)
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
uint32_t HalGetRand()
{
	//i386GetRDRAND()

	return 0;
}

#define IA32_APIC_BASE_MSR 0x1B

void HalEndOfInterrupt(int irqNum)
{
	if (apic) {
		uint64_t ret = x86rdmsr(IA32_APIC_BASE_MSR);
		uint32_t* ptr = (uint32_t*) (size_t) ((ret & 0xfffff000) + 0xb0);
		*ptr = 1;

	} else {
		picEOI(irqNum);
	}
}

void HalRestart()
{

}

void HalShutdown()
{

}

void HalSleep()
{

}



CPU::CPU() : Device("CPU")
{
	deviceType = DeviceType::CPU;
}

int CPU::open(int num, int b, void* vas_)
{
	cpuNum = num;
	gdt.setup();
	tss.setup(0xDEADBEEF);
	tss.flush();
	idt.setup();
	writeDR7(0x400);

	cpuSpecificData = (CPUSpecificData*)VIRT_CPU_SPECIFIC;

	cpuSpecificPhysAddr = (CPUSpecificData*)Phys::allocatePage();
	cpuSpecificPhysAddr->cpuNumber = num;
	cpuSpecificPhysAddr->cpuPointer = this;

	VAS* vas = (VAS*)vas_;
	if (vas) {
		vas->setCPUSpecific((size_t)cpuSpecificPhysAddr);
	}
	else {
		KePanic("NO KERNEL VAS");
	}

	KeSetBootMessage("Starting the HAL...");
	HalInitialise();

	timer = setupTimer(sysBootSettings & 16 ? 30 : 100);

	if (sysBootSettings & 32) {
		setupFeatures();
	}

	return 0;
}

int CPU::close(int a, int b, void* ptr)
{
	return 0;
}

void CPU::setupSMEP()
{
	writeCR4(readCR4() | (1 << 20));
}

void CPU::setupSMAP()
{
	writeCR4(readCR4() | (1 << 21));
	prohibitUsermodeDataAccess();
}

void CPU::setupUMIP()
{
	writeCR4(readCR4() | (1 << 11));
}

void CPU::setupTSC()
{
	writeCR4(readCR4() | (1 << 2));
}

void CPU::setupLargePages()
{
	writeCR4(readCR4() | (1 << 4));
}

void CPU::setupPAT()
{
	if (features.hasMSR) {
		uint64_t pat = x86rdmsr(0x277);

		//first 4 entries
		uint32_t lowPat = pat & 0xFFFFFFFF;

		//next 4 entries
		uint32_t highPat = pat >> 32;

		//clear first entry of high dword (entry 4)
		highPat &= ~7;

		//set to write combining
		highPat |= 1;

		//write back the PAT
		pat = (((uint64_t)highPat) << 32) | ((uint64_t)lowPat);
		x86wrmsr(0x277, pat);
	}
}

void CPU::setupMTRR()
{

}

void CPU::setupGlobalPages()
{
	writeCR4(readCR4() | (1 << 7));
}

void CPU::allowUsermodeDataAccess()
{
	if (features.hasSMAP) {
		asm volatile ("stac" ::: "cc");
	}
}

void CPU::prohibitUsermodeDataAccess()
{
	if (features.hasSMAP) {
		asm volatile ("clac" ::: "cc");
	}
}

void CPU::setupFeatures()
{
	if (features.hasSMEP) {
		//kprintf("SMEP on.\n");
		//setupSMEP();
	}

	if (features.hasSMAP) {
		//kprintf("SMAP on.\n");
		//setupSMAP();
	}

	if (features.hasUMIP) {
		kprintf("UMIP on.\n");
		setupUMIP();
	}

	if (features.hasTSC) {
		kprintf("TSC on.\n");
		setupTSC();
	}

	if (features.hasPSE) {
		kprintf("PSE on.\n");
		setupLargePages();
	}

	if (features.hasGlobalPages) {
		kprintf("GLOBAL PAGES on.\n");
		setupGlobalPages();
	}

	if (features.hasPAT) {
		kprintf("PAT on.\n");
		setupPAT();
	}

	if (features.hasMTRR) {
		kprintf("MTRR on.\n");
		setupMTRR();
	}
}
