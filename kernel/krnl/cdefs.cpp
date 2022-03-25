#include <thr/prcssthr.hpp>

/// <summary>
/// Wraps the unlockScheduler function with C linkage.
/// </summary>
extern "C" void CUnlockScheduler()
{
	unlockScheduler();
}

/// <summary>
/// Wraps the lockScheduler function with C linkage.
/// </summary>
extern "C" void CLockScheduler()
{
	lockScheduler();
}

/// <summary>
/// Wraps the kprintf function with C linkage.
/// </summary>
/// <param name="formatString">The format string for kprintf. See the documentation of kprintf for more details.</param>
/// <param name="">The variable argument list for kprintf. See the documentation of kprintf for more details.</param>
extern "C" void CPrintf(const char* formatString, ...)
{
	kprintf("%s", formatString);
}