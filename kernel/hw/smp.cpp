#include "hw/smp.hpp"
#include "krnl/hal.hpp"
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
		
	}

	void startCPUs()
	{
		
	}
}
