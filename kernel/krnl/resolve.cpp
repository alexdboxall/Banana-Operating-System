
// Unfortunate hacks to allow old drivers to use old symbol names that
// don't actually exist anymore.

#include <krnl/computer.hpp>
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>
#include <libk/string.h>

extern "C" unsigned long __udivdi3(unsigned long, unsigned long);
extern "C" long __divdi3(long, long);
extern "C" unsigned long __umoddi3(unsigned long, unsigned long);
extern "C" long __moddi3(long, long);

/// <summary>
/// Given an kernel symbol name which doesn't exist anymore, returns a pointer
/// to the object if it still exists under a new name.
/// </summary>
/// <param name="name">The old kernel symbol name as a string (mangled C++ names)</param>
/// <returns>A pointer to the object if it still exists, otherwise zero.</returns>
size_t KeResolveCompatibilitySymbol(char* name)
{
	if (!strcmp(name, "computer")) {							// probably unneeded
		return (size_t) (&computer);

	} else if (!strcmp(name, "__udivdi3")) {					// internal divsion related function
		return (size_t) __udivdi3;

	} else if (!strcmp(name, "_ZN4Krnl8computerE")) {			// Krnl::computer
		return (size_t) (&computer);

	} else if (!strcmp(name, "__divdi3")) {						// internal divsion related function
		return (size_t) __divdi3;

	} else if (!strcmp(name, "_ZN4Krnl5panicEPKc")) {			// Krnl::panic
		return (size_t) KePanic;

	} else if (!strcmp(name, "_ZN4Krnl14setBootMessageEPKc")) {	// Krnl::setBootMessage
		return (size_t) KeSetBootMessage;

	} else if (!strcmp(name, "__umoddi3")) {					// internal divsion related function
		return (size_t) __umoddi3;

	} else if (!strcmp(name, "__moddi3")) {						// internal divsion related function
		return (size_t) __moddi3;

	} else if (!strcmp(name, "_ZN4Krnl12preemptionOnE")) {		// Krnl::preemptionOn
		return (size_t) &keIsPreemptionOn;

	} else if (!strcmp(name, "preemptionOn")) {
		return (size_t) &keIsPreemptionOn;

	} else if (!strcmp(name, "schedulingOn")) {
		return (size_t) &keIsSchedulingOn;

	} else if (!strcmp(name, "KeIsPreemptionOn")) {
		return (size_t) &keIsPreemptionOn;

	} else if (!strcmp(name, "KeIsSchedulingOn")) {
		return (size_t) &keIsSchedulingOn;

	} else if (!strcmp(name, "_Z13terminateTaski")) {			// terminateTask
		return (size_t) &KeTerminateCurrentThread;

	}

	return 0;
}