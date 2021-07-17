#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include <krnl/signal.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Sends a signal to another process. Blame POSIX for the misleading name.
/// </summary>
/// <param name="ebx">The signal number to send.</param>
/// <param name="ecx">The process ID to send the signal to. A negative value sends the signal to all possible processes.</param>
/// <returns>Returns 0 on success, or non-zero on failure.</returns>
/// 
uint64_t SysKill(regs* r)
{
	if (r->ecx == -1) {
		KePanic("kill(-1) WILL DESTORY THE SYSTEM");
		return -1;
	}

	ThreadControlBlock* f = (ThreadControlBlock*) taskList.getFirstElement();
	while (f) {
		if (f->processRelatedTo->pid == r->ecx) {
			KeRaiseSignal(currentTaskTCB->processRelatedTo->signals, r->ebx);
			return 0;
		}
		f = (ThreadControlBlock*) taskList.getNext(f);
	}

	f = (ThreadControlBlock*) sleepingTaskList.getFirstElement();
	while (f) {
		if (f->processRelatedTo->pid == r->ecx) {
			KeRaiseSignal(currentTaskTCB->processRelatedTo->signals, r->ebx);
			return 0;
		}
		f = (ThreadControlBlock*) sleepingTaskList.getNext(f);
	}

	return -1;
}


