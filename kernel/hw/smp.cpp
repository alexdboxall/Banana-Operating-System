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
	void startCPU(int num)
	{
		lockScheduler();

		if (!computer->features.hasMSR) {
			return;
		}

		uint64_t apicBase = computer->rdmsr(IA32_APIC_BASE_MSR) & 0xfffff000;
		kprintf("apicBase = 0x%X\n", apicBase);

		unlockScheduler();
	}
}
