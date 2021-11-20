
#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <stdint.h>
#include "krnl/common.hpp"
#include "krnl/gdt.hpp"
#include "krnl/idt.hpp"
#include "krnl/tss.hpp"
#include "hal/intctrl.hpp"
#include "hal/timer.hpp"

struct CPUSpecificData
{
	int cpuNumber;
	CPU* cpuPointer;
};


class CPU : public Device
{
private:

protected:
	void detectFeatures();

public:
	

	CPUSpecificData* cpuSpecificPhysAddr = nullptr;
	CPUSpecificData* cpuSpecificData;

	int cpuNum;
	GDT gdt;
	IDT idt;
	TSS tss;

	uint16_t doubleFaultSelector;

	Timer* timer;

	CPU();
	int open(int num, int b, void* vas);
	int close(int, int, void*);

	void setupFeatures();

	static inline __attribute__((always_inline)) size_t readCR0()
	{
		size_t val;
		asm volatile ("mov %%cr0, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readCR2()
	{
		size_t val;
		asm volatile ("mov %%cr2, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readCR3()
	{
		size_t val;
		asm volatile ("mov %%cr3, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readCR4()
	{
		size_t val;
		asm volatile ("mov %%cr4, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR0()
	{
		size_t val;
		asm volatile ("mov %%dr0, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR1()
	{
		size_t val;
		asm volatile ("mov %%dr1, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR2()
	{
		size_t val;
		asm volatile ("mov %%dr2, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR3()
	{
		size_t val;
		asm volatile ("mov %%dr3, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR6()
	{
		size_t val;
		asm volatile ("mov %%dr6, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) size_t readDR7()
	{
		size_t val;
		asm volatile ("mov %%dr7, %0" : "=r"(val));
		return val;
	}

	static inline __attribute__((always_inline)) void writeDR0(size_t val)
	{
		asm volatile ("mov %0, %%dr0" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeDR1(size_t val)
	{
		asm volatile ("mov %0, %%dr1" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeDR2(size_t val)
	{
		asm volatile ("mov %0, %%dr2" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeDR3(size_t val)
	{
		asm volatile ("mov %0, %%dr3" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeDR6(size_t val)
	{
		asm volatile ("mov %0, %%dr6" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeDR7(size_t val)
	{
		asm volatile ("mov %0, %%dr7" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeCR0(size_t val)
	{
		asm volatile ("mov %0, %%cr0" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeCR3(size_t val)
	{
		asm volatile ("mov %0, %%cr3" :: "r"(val));
	}

	static inline __attribute__((always_inline)) void writeCR4(size_t val)
	{
		asm volatile ("mov %0, %%cr4" :: "r"(val));
	}

	static inline __attribute__((always_inline)) int getNumber()
	{
		return 0;
	}

	static inline __attribute__((always_inline)) CPU* current()
	{
		kprintf("computer = 0x%X\n", computer);
		return computer->cpu[0];
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


void cpuid(int code, size_t* a, size_t* b, size_t* c, size_t* d);
bool cpuidCheckEDX(uint32_t check);
bool cpuidCheckECX(uint32_t check);
bool cpuidCheckExtendedEBX(uint32_t check);
bool cpuidCheckExtendedECX(uint32_t check);

struct REGS
{
	size_t eax;
	size_t ebx;
	size_t ecx;
	size_t edx;
};

void AMD_K6_write_msr(uint32_t msr, uint32_t v1, uint32_t v2, REGS* regs);
void AMD_K6_read_msr(uint32_t msr, REGS* regs);
void AMD_K6_writeback(int family, int model, int stepping);

char* lookupAMDName(uint8_t a, uint8_t b);
char* lookupIntelName(uint8_t a, uint8_t b);

#endif