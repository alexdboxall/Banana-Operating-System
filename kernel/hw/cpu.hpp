
#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <stdint.h>
#include "core/common.hpp"
#include "core/gdt.hpp"
#include "core/idt.hpp"
#include "core/tss.hpp"
#include "hal/intctrl.hpp"
#include "hal/timer.hpp"

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

class CPU : public Device
{
private:

protected:
	void detectFeatures();

public:
	CPUVendor vendor;
	uint32_t steppingID : 4;
	uint32_t processorType : 2;
	uint32_t model : 8;
	uint32_t familyID : 8;

	char vendorIDString[13];

	int cpuNum;
	GDT gdt;
	IDT idt;
	TSS tss;
	uint16_t doubleFaultSelector;

	InterruptController* intCtrl;
	Timer* timer;

	CPU();
	int open(int num, int b, void* c);
	int close(int, int, void*);

	void displayFeatures();
	void setupFeatures();

	struct CPUFeatures
	{
		uint32_t hasRDRAND : 1;
		uint32_t hasTSC : 1;
		uint32_t hasPAE : 1;
		uint32_t hasPSE : 1;
		uint32_t hasGlobalPages : 1;
		uint32_t hasPAT : 1;
		uint32_t hasSMEP : 1;
		uint32_t hasRDSEED : 1;
		uint32_t hasINVLPG : 1;
		uint32_t hasINVD : 1;
		uint32_t hasWBINVD : 1;
		uint32_t hasUMIP : 1;
		uint32_t hasSMAP : 1;
		uint32_t hasCR8 : 1;
		uint32_t hasSysenter : 1;
		uint32_t hasSyscall : 1;
		uint32_t hasMTRR : 1;
		uint32_t onboardFPU : 1;
		uint32_t hasTPAUSE : 1;

	} features;

	bool opcodeDetectionMode = false;

	static inline size_t readCR0()
	{
		size_t val;
		asm volatile ("mov %%cr0, %0" : "=r"(val));
		return val;
	}

	static inline size_t readCR2()
	{
		size_t val;
		asm volatile ("mov %%cr2, %0" : "=r"(val));
		return val;
	}

	static inline size_t readCR3()
	{
		size_t val;
		asm volatile ("mov %%cr3, %0" : "=r"(val));
		return val;
	}

	static inline size_t readCR4()
	{
		size_t val;
		asm volatile ("mov %%cr4, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR0()
	{
		size_t val;
		asm volatile ("mov %%dr0, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR1()
	{
		size_t val;
		asm volatile ("mov %%dr1, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR2()
	{
		size_t val;
		asm volatile ("mov %%dr2, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR3()
	{
		size_t val;
		asm volatile ("mov %%dr3, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR6()
	{
		size_t val;
		asm volatile ("mov %%dr6, %0" : "=r"(val));
		return val;
	}

	static inline size_t readDR7()
	{
		size_t val;
		asm volatile ("mov %%dr7, %0" : "=r"(val));
		return val;
	}

	static inline void writeDR0(size_t val)
	{
		asm volatile ("mov %0, %%dr0" :: "r"(val));
	}

	static inline void writeDR1(size_t val)
	{
		asm volatile ("mov %0, %%dr1" :: "r"(val));
	}

	static inline void writeDR2(size_t val)
	{
		asm volatile ("mov %0, %%dr2" :: "r"(val));
	}

	static inline void writeDR3(size_t val)
	{
		asm volatile ("mov %0, %%dr3" :: "r"(val));
	}

	static inline void writeDR6(size_t val)
	{
		asm volatile ("mov %0, %%dr6" :: "r"(val));
	}

	static inline void writeDR7(size_t val)
	{
		asm volatile ("mov %0, %%dr7" :: "r"(val));
	}

	static inline void writeCR0(size_t val)
	{
		asm volatile ("mov %0, %%cr0" :: "r"(val));
	}

	static inline void writeCR3(size_t val)
	{
		asm volatile ("mov %0, %%cr3" :: "r"(val));
	}

	static inline void writeCR4(size_t val)
	{
		asm volatile ("mov %0, %%cr4" :: "r"(val));
	}

	void setupSMEP();
	void setupSMAP();
	void setupUMIP();
	void setupTSC();
	void setupLargePages();
	void setupGlobalPages();
	void setupPAT();
	void setupMTRR();

	void allowUsermodeDataAccess();
	void prohibitUsermodeDataAccess();

};

CPU* thisCPU();
int getCPUNumber();

extern void cpuid(int code, size_t* a, size_t* b, size_t* c, size_t* d);
extern bool cpuidCheckEDX(uint32_t check);
extern bool cpuidCheckECX(uint32_t check);
extern bool cpuidCheckExtendedEBX(uint32_t check);
extern bool cpuidCheckExtendedECX(uint32_t check);

#endif