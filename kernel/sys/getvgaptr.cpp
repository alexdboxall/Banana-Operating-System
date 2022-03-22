#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hw/cpu.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include "krnl/virtmgr.hpp"
#include "krnl/physmgr.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Returns a task's terminal data for use by CONHOST.EXE.
/// </summary>
/// <param name="ebx">Pointer to store 4096 bytes of data, 4000 of characters, then width (4 bytes), height (4 bytes) and GUI state (0 = terminal, 1 = GUI) (4 bytes). After that is the terminal's name.</param>
/// <param name="ecx">The PID of the task.</param>
/// <param name="edx">If this is set to a non-zero value, the terminal will become the active terminal.</param>
/// <returns>0 if good, 1 if bad.</returns>
/// 
uint64_t SysGetVGAPtr(regs* r)
{
	Process* prcss;
	if (r->ecx != -1) {
		prcss = KeProcessFromPID(r->ecx);
		if (prcss == nullptr) {
			return 1;
		}
	} else {
		prcss = currentTaskTCB->processRelatedTo;
	}

	VgaText* terminal = prcss->terminal;
	if (r->edx) {
		setActiveTerminal(terminal);
	}

	memcpy((void*) r->ebx, (const char*) terminal->displayData, 4000);
	*((int*) (r->ebx + 4000)) = terminal->cursorX;
	*((int*) (r->ebx + 4004)) = terminal->cursorY;
	*((int*) (r->ebx + 4008)) = prcss->threads[0].guiTask ? 1 : 0;
	strcpy((char*) (r->ebx + 4012), "<NO NAME>");
	return 0;
}
