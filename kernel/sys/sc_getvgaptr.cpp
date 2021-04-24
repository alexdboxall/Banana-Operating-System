#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hw/cpu.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Sys
{
	/// <summary>
	/// ...
	/// </summary>
	/// <param name="ebx">Pointer to store 4096 bytes of data, 4000 of characters, then width (4 bytes) and height (4 bytes). After that is the terminal's name.</param>
	/// <param name="ecx">Does not matter yet.</param>
	/// <param name="edx">Does not matter yet.</param>
	/// <returns>Zero.</returns>
	/// 
	uint64_t getVGAPtr(regs* r)
	{
		memcpy((void*) r->ebx, (const char*) currentTaskTCB->processRelatedTo->terminal->displayData, 4000);
		*((int*) (r->ebx + 4000)) = currentTaskTCB->processRelatedTo->terminal->cursorX;
		*((int*) (r->ebx + 4004)) = currentTaskTCB->processRelatedTo->terminal->cursorY;
		strcpy((char*) (r->ebx + 4008), currentTaskTCB->processRelatedTo->terminal->name);
		return 0;
	}
}
