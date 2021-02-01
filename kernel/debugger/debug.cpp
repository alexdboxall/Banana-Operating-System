#include "debugger/debug.hpp"
#include "core/prcssthr.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

namespace Debug
{
	void displayFunctionCallers()
	{
		lockScheduler();
		kprintf("Callers to the function:\n");
		kprintf("    0: 0x%X\n", (uint32_t) __builtin_return_address(0));
		kprintf("    1: 0x%X\n", (uint32_t) __builtin_return_address(1));
		//kprintf("    3: 0x%X\n", (uint32_t) __builtin_return_address(3));
		unlockScheduler();
	}
}

#pragma GCC diagnostic pop