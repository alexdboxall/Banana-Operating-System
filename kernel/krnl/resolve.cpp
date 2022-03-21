
// Unfortunate hacks to allow old drivers to use old symbol names that
// don't actually exist anymore.

#include <krnl/computer.hpp>
#include <krnl/panic.hpp>
extern "C" {
#include <libk/string.h>
}

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
	if (!strcmp(name, "computer")) {
		return (size_t) (&computer);

	} else if (!strcmp(name, "__udivdi3")) {
		return (size_t) __udivdi3;

	} else if (!strcmp(name, "_ZN4Krnl8computerE")) {
		return (size_t) (&computer);

	} else if (!strcmp(name, "__divdi3")) {
		return (size_t) __divdi3;

	} else if (!strcmp(name, "_ZN4Krnl5panicEPKc")) {
		return (size_t) KePanic;

	} else if (!strcmp(name, "_ZN4Krnl14setBootMessageEPKc")) {
		return (size_t) KeSetBootMessage;

	} else if (!strcmp(name, "__umoddi3")) {
		return (size_t) __umoddi3;

	} else if (!strcmp(name, "__moddi3")) {
		return (size_t) __moddi3;

	} else if (!strcmp(name, "_ZN4Krnl12preemptionOnE")) {
		return (size_t) &KeIsPreemptionOn;

	} else if (!strcmp(name, "preemptionOn")) {
		return (size_t) &KeIsPreemptionOn;

	} else if (!strcmp(name, "schedulingOn")) {
		return (size_t) &KeIsSchedulingOn;

	}

	return 0;
}