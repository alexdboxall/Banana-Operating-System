#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#include "krnl/virtmgr.hpp"
#include "krnl/physmgr.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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


void CPU::AMD_K6_writeback(int family, int model, int stepping)
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

void CPU::AMD_K6_write_msr(uint32_t msr, uint32_t v1, uint32_t v2, REGS* regs)
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

void CPU::AMD_K6_read_msr(uint32_t msr, REGS* regs)
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

void CPU::cpuid(int code, size_t* a, size_t* b, size_t* c, size_t* d)
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

bool CPU::cpuidCheckEDX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
	return edx & check;
}

bool CPU::cpuidCheckECX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
	return ecx & check;
}

bool CPU::cpuidCheckExtendedEBX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETEXTENDED, &eax, &ebx, &ecx, &edx);
	return ebx & check;
}

bool CPU::cpuidCheckExtendedECX(uint32_t check)
{
	size_t eax, ebx, ecx, edx;
	cpuid(CPUID_GETEXTENDED, &eax, &ebx, &ecx, &edx);
	return ecx & check;
}

CPU::CPU(): Device("CPU")
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

	cpuSpecificData = (CPUSpecificData*) VIRT_CPU_SPECIFIC;

	cpuSpecificPhysAddr = (CPUSpecificData*) Phys::allocatePage();
	cpuSpecificPhysAddr->cpuNumber = num;
	cpuSpecificPhysAddr->cpuPointer = this;

	VAS* vas = (VAS*) vas_;
	if (vas) {
		vas->setCPUSpecific((size_t) cpuSpecificPhysAddr);
	} else {
		KePanic("NO KERNEL VAS");
	}
	
	KeSetBootMessage("Detecting CPU specific features...");
	//here so APIC can be disabled on dodgy K5 CPUs
	detectFeatures();

	KeSetBootMessage("Starting the HAL...");
	HalInitialise();

	timer = setupTimer(sysBootSettings & 16 ? 30 : 100);

	if (sysBootSettings & 32) {
		setupFeatures();
	}

	return 0;
}

extern "C" size_t is486();
extern "C" size_t hasLegacyFPU();

void CPU::detectFeatures()
{
	opcodeDetectionMode = true;

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

	memset(vendorIDString, 0, 13);

	if (computer->features.hasCPUID) {
		features.hasTSC = cpuidCheckEDX(CPUID_FEAT_EDX_TSC);
		features.hasPAE = cpuidCheckEDX(CPUID_FEAT_EDX_PAE);
		features.hasPSE = cpuidCheckEDX(CPUID_FEAT_EDX_PSE);
		features.hasGlobalPages = cpuidCheckEDX(CPUID_FEAT_EDX_PGE);
		features.hasPAT = cpuidCheckEDX(CPUID_FEAT_EDX_PAT);
		features.onboardFPU = cpuidCheckEDX(CPUID_FEAT_EDX_FPU);
		features.hasSysenter = cpuidCheckEDX(CPUID_FEAT_EDX_SEP);

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

		setName("Unknown CPU");

	} else {
		//either an i386 or an i486

		strcpy(vendorIDString, CPUID_VENDOR_INTEL);
		vendor = CPUVendor::Intel;

		if (is486()) {
			//setName("Intel i486");
			features.hasINVLPG = 1;
			features.hasINVD = 1;
			features.hasWBINVD = 1;

			size_t cr0 = readCR0();
			if ((cr0 & (1 << 2)) && !(cr0 & (1 << 4))) {
				features.onboardFPU = false;

			} else {
				features.onboardFPU = hasLegacyFPU();
			}

		} else {
			//setName("Intel i386");
			features.hasINVLPG = 0;
			features.hasINVD = 0;
			features.hasWBINVD = 0;

			size_t cr0 = readCR0();
			if ((cr0 & (1 << 2)) && !(cr0 & (1 << 4))) {
				features.onboardFPU = false;

			} else {
				features.onboardFPU = hasLegacyFPU();
			}
		}
	}

	if (!features.onboardFPU) {
		features.onboardFPU = hasLegacyFPU();
	}

	if (features.onboardFPU) {
		computer->features.hasx87 = true;
	}

	opcodeDetectionMode = false;
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
	/*if (computer->features.hasMSR) {
		uint64_t pat = computer->rdmsr(0x277);

		//first 4 entries
		uint32_t lowPat = pat & 0xFFFFFFFF;

		//next 4 entries
		uint32_t highPat = pat >> 32;

		//clear first entry of high dword (entry 4)
		highPat &= ~7;

		//set to write combining
		highPat |= 1;

		//write back the PAT
		pat = (((uint64_t) highPat) << 32) | ((uint64_t) lowPat);
		computer->wrmsr(0x277, pat);
	}*/
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
