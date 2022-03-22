#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include <thr/alarm.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Creates a new thread.
/// </summary>
/// <param name="ebx">The argument to pass to the start function.</param>
/// <param name="ecx">The attributes of the new thread.</param>
/// <param name="edx">The start function.</param>
/// <returns>Returns zero on success, and non-zero otherwise.</returns>
/// 
uint64_t SysPthreadCreate(regs* r)
{
	ThreadControlBlock* tcb = currentTaskTCB->processRelatedTo->createUserThread();
	//tcb->pthreadStartLocation = (size_t) r->edx;
	//tcb->pthreadContext = (void*) r->ebx;
	return 0;
}




/// <summary>
/// Returns the relative thread ID of the currently running thread.
/// </summary>
/// <returns>Returns the relative thread ID.</returns>
/// 
uint64_t SysPthreadGetTID(regs* r)
{
	return currentTaskTCB->rtid;
}




uint64_t SysInternalPthreadGetContext(regs* r)
{
	return 0;// (uint64_t) currentTaskTCB->pthreadContext;
}

uint64_t SysInternalPthreadGetStartLocation(regs* r)
{
	return 0;// (uint64_t) currentTaskTCB->pthreadStartLocation;
}


uint64_t SysPthreadJoin(regs* r)
{
	return 0;
}

uint64_t SysPthreadExit(regs* r)
{
	KeTerminateCurrentThread(r->ebx);
	return -1;
}