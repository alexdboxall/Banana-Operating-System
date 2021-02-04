#include "core/prcssthr.hpp"
#include "core/syscalls.hpp"
#include "core/virtmgr.hpp"
#include "hal/intctrl.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Changes and/or returns the location of the process' system break by a certain number of bytes, allocating new memory if needed.
/// </summary>
/// <remark>
/// This system call does not check that there is enough physical memory or virtual memory in the kernel to successfully make this call,
/// so requesting an excessive amount of memory will cause a kernel panic.
/// </remark>
/// <param name="ebx">If zero, non changes are made, and the location of the system break is returned. If greater than zero, the system break
/// increases by at least this many bytes if possible (the actual amount may be more). If less than zero, the system
/// break may shrink by up to this many bytes. The call will fail if this value is greater than 64MiB.</param>
/// <returns>On success, the updated system break value is returned. On error, it returns -1.</returns>
uint64_t sysCallSbrk(regs* r)
{
	size_t previousBreak = currentTaskTCB->processRelatedTo->vas->sbrk;

	if (r->ebx == 0) {
		return previousBreak;
	}

	if (((int) r->ebx) < 0) {
		return previousBreak;
	}

	if (r->ebx > 67108864) {
		return -1;
	}

	currentTaskTCB->processRelatedTo->vas->allocatePages((r->ebx + 4095) / 4096, PAGE_PRESENT | PAGE_WRITABLE | PAGE_USER | PAGE_ALLOCATED);

	return previousBreak;
}