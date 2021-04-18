#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
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
	/// Returns the pointer to the kernel process' terminal data, stored in VGA text mode 3 format. It also allows this current process to read from the this page.
	/// </summary>
	/// <param name="ebx">Does not matter yet.</param>
	/// <param name="ecx">Does not matter yet.</param>
	/// <param name="edx">Does not matter yet.</param>
	/// <returns>Returns the pointer to a 4096 byte area. Writing to this area, or accessing outside this area will cause a page fault and the program will be terminated.</returns>
	/// 
	uint64_t getVGAPtr(regs* r)
	{
		kprintf("getVGAPtr: 0x%X\n", kernelProcess->terminal->displayData);
		
		size_t* entry = currentTaskTCB->processRelatedTo->vas->getPageTableEntry((size_t) kernelProcess->terminal->displayData);
		kprintf("*entry = 0x%X\n", *entry);
		*entry |= PAGE_WRITABLE;
		*entry |= PAGE_USER;

		//flush TLB
		CPU::writeCR3(CPU::readCR3());

		kprintf("*entry = 0x%X\n", *entry);

		return (uint64_t) kernelProcess->terminal->displayData;
	}
}


