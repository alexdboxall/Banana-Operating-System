#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include <reg/cm.hpp>

extern "C" {
#include <libk/string.h>
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Gets the registry type from a path.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="edx">The path.</param>
/// <returns>Returns the type ID or -1 on failure.</returns>
/// 
uint64_t SysRegistryGetTypeFromPath(regs* r)
{
	kprintf("SysRegistryGetTypeFromPath: %s\n", (const char*) r->edx);
	char name[300];
	int x = CmFindObjectFromPath(((Reghive*) r->ebx), (const char*) r->edx);
	kprintf("x = %d\n", x);
	if (!x) return -1;
	int type = CmGetNameAndTypeFromExtent(((Reghive*) r->ebx), x, name);
	kprintf("type = %d, name = %s\n", type, name);

	return type;
}

/// <summary>
/// Reads data.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="ecx">The extent number, with the 31st bit determining whether to read an integer (bit set), or a string (bit clear).</param>
/// <param name="edx">The path to write string data.</param>
/// <returns>Returns the integer data, else 0 if success, or non-zero on failure.</returns>
/// 
uint64_t SysRegistryReadExtent(regs* r)
{
	if ((r->ecx >> 31) & 1) {
		uint64_t i;
		CmGetInteger(((Reghive*) r->ebx), r->ecx & 0x7FFFFFFF, &i);
		return i;

	} else {
		CmGetString(((Reghive*) r->ebx), r->ecx & 0x7FFFFFFF, (char*) r->edx);
		return 0;
	}

	return -1;
}

/// <summary>
/// Gets the registry extent number from a path.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="edx">The path.</param>
/// <returns>Returns the extent number.</returns>
/// 
uint64_t SysRegistryPathToExtentLookup(regs* r)
{
	kprintf("SysRegistryPathToExtentLookup: %s\n", (const char*) r->edx);
	return CmFindObjectFromPath(((Reghive*) r->ebx), (const char*) r->edx);
}

/// <summary>
/// Gets the subdirectory registry extent number from an extent number.
/// </summary>
/// <param name="ebx">The registry pointer.</param>
/// <param name="ecx">The extent.</param>
/// <returns>Returns the extent number.</returns>
/// 
uint64_t SysRegistryEnterDirectory(regs* r)
{
	kprintf("SysRegistryEnterDirectory %d\n", r->ecx);
	return CmEnterDirectory(((Reghive*) r->ebx), r->ecx);
}

uint64_t SysRegistryGetNext(regs* r)
{
	kprintf("SysRegistryGetNext %d\n", r->ecx);
	return CmGetNext(((Reghive*) r->ebx), r->ecx);
}

uint64_t SysRegistryGetNameAndTypeFromExtent(regs* r)
{
	char name[300];
	int type = CmGetNameAndTypeFromExtent(((Reghive*) r->ebx), r->ecx, name);
	strcpy((char*) r->edx, name);
	return type;
}

uint64_t SysRegistryOpen(regs* r)
{
	return (uint64_t) CmOpen((const char*) r->edx);
}

uint64_t SysRegistryClose(regs* r)
{
	CmClose((Reghive*) r->ebx);
	return 0; 
}