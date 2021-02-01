#include "debugger/debug.hpp"
#include "core/prcssthr.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

namespace Debug
{
	void displayFunctionCallers()
	{
		lockScheduler();
		kprintf("Callers to the function:");
		kprintf("    1: 0x%X\n", 0 /* (uint32_t) __builtin_return_address(1)*/);
		//kprintf("    2: 0x%X\n", (uint32_t) __builtin_return_address(2));
		//kprintf("    3: 0x%X\n", (uint32_t) __builtin_return_address(3));
		unlockScheduler();
	}
}

#pragma GCC diagnostic pop