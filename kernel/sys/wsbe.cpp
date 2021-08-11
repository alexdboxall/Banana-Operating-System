#include "thr/prcssthr.hpp"
#include "core/computer.hpp"
#include "sys/syscalls.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Makes a call to the GUI driver. If not loaded yet, it will print a message and terminate the program with exit code specified.
/// </summary>
/// <param name="ebx">Driver dependent, or the return code if no driver loaded.</param>
/// <param name="ecx">Driver dependent.</param>
/// <param name="edx">Driver dependent.</param>
/// <returns>Driver dependent.</returns>
/// 
uint64_t SysWsbe(regs* r)
{
	int br;
	char noGUI[] = "This program requires a GUI driver to run.\n";
	currentTaskTCB->processRelatedTo->terminal->write(strlen(noGUI), (void*) noGUI, &br);
	terminateTask(r->edx);
	return 0xDEADBEEF;
}