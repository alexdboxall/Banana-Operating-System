#include "hw/smp.hpp"
#include "hw/ports.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "fs/vfs.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

extern "C" void prepareTramp();

#define SMP_START_PAGE	0x2
namespace Krnl
{
	uint8_t bspID;

	void smpEntry()
	{
		while (1);
	}

	void startCPU(int num)
	{
		if (!computer->features.hasMSR) {
			return;
		}

		lockScheduler();
		size_t apicBase = computer->rdmsr(IA32_APIC_BASE_MSR) & 0xfffff000;
		kprintf("apicBase = 0x%X\n", apicBase);

		*((volatile uint32_t*) (apicBase + 0x280)) = 0;
		
		*((volatile uint32_t*) (apicBase + 0x280)) = 0;                                                                             // clear APIC errors
		*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24);       // select AP
		*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff00000) | 0x00C500;          // trigger INIT IPI
		do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (apicBase + 0x300)) & (1 << 12));        // wait for delivery
		*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24);       // select AP
		*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff00000) | 0x008500;          // deassert
		do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (apicBase + 0x300)) & (1 << 12));        // wait for delivery
		
		//nanoSleep(1000 * 1000 * 10);
		
		for (int j = 0; j < 2; j++) {
			*((volatile uint32_t*) (apicBase + 0x280)) = 0;																							// clear APIC errors
			*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24);					// select AP
			*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff0f800) | (0x000600 | SMP_START_PAGE);		// trigger STARTUP IPI for 0800:0000
			//nanoSleep(1000 * 200);
			do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (apicBase + 0x300)) & (1 << 12));					// wait for delivery
		}

		while (1);
		unlockScheduler();
	}

	void startCPUs()
	{
		if (!computer->features.hasCPUID) return;
		if (!computer->features.hasMSR) return;
		if (!computer->features.hasAPIC) return;

		prepareTramp();

		asm volatile ("mov $1, %%eax; cpuid; shrl $24, %%ebx;": "=b"(bspID));

		for (int i = 0; i < processorDiscoveryNumber; ++i) {
			if (i == bspID) {
				continue;
			}

			File* f = new File("C:/Banana/System/TRAMP.EXE", kernelProcess);
			f->open(FileOpenMode::Read);
			uint64_t siz;
			bool dir;
			int br;
			f->stat(&siz, &dir);
			f->read(siz, (void*) (VIRT_LOW_MEGS + 0x2000), &br);
			f->close();

			kprintf("CPU %d: processor ID 0x%X, apic ID 0x%X\n", i, processorID[i], matchingAPICID[i]);
			startCPU(i);
		}

		//for each cpu
			//start it
			//cpu[i]->open(i, 0, nullptr);

		//cpu[0] = new CPU();
		//addChild(cpu[0]);
		//cpu[0]->open(0, 0, vas);		//FIRST ARG IS CPU NUMBER
	}
}
