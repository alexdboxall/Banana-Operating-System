#include "hw/smp.hpp"
#include "hw/ports.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Krnl
{
	uint8_t bspID;

	void startCPU(int num)
	{
		if (!computer->features.hasMSR) {
			return;
		}

		size_t apicBase = computer->rdmsr(IA32_APIC_BASE_MSR) & 0xfffff000;
		kprintf("apicBase = 0x%X\n", apicBase);

		*((volatile uint32_t*) (apicBase + 0x280)) = 0;
		
		*((volatile uint32_t*) (apicBase + 0x280)) = 0;                                                                             // clear APIC errors
		*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24);         // select AP
		*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff00000) | 0x00C500;          // trigger INIT IPI
		do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (lapic_ptr + 0x300)) & (1 << 12));         // wait for delivery
		*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24);         // select AP
		*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff00000) | 0x008500;          // deassert
		do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (lapic_ptr + 0x300)) & (1 << 12));         // wait for delivery
		
		nanoSleep(1000 * 1000 * 10);
		
		for (j = 0; j < 2; j++) {
			*((volatile uint32_t*) (apicBase + 0x280)) = 0;                                                                     // clear APIC errors
			*((volatile uint32_t*) (apicBase + 0x310)) = (*((volatile uint32_t*) (apicBase + 0x310)) & 0x00ffffff) | (num << 24); // select AP
			*((volatile uint32_t*) (apicBase + 0x300)) = (*((volatile uint32_t*) (apicBase + 0x300)) & 0xfff0f800) | 0x000608;  // trigger STARTUP IPI for 0800:0000
			nanoSleep(1000 * 200);
			do { __asm__ __volatile__("pause" : : : "memory"); } while (*((volatile uint32_t*) (apicBase + 0x300)) & (1 << 12)); // wait for delivery
		}
	}

	void startCPUs()
	{
		if (!computer->features.hasCPUID) return;
		if (!computer->features.hasMSR) return;
		if (!computer->features.hasAPIC) return;

		asm volatile ("mov $1, %%eax; cpuid; shrl $24, %%ebx;": "=b"(bspID));

		for (int i = 0; i < processorDiscoveryNumber; ++i) {
			if (i == bspID) {
				continue;
			}

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
