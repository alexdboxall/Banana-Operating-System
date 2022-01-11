#include <stdint.h>

#pragma GCC optimize ("O1")

void NiMain(void* s);
void NiBegin(void* s)
{
	NiMain(s);
}

#include "krnl/main.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

#include "context.hpp"
#include "window.hpp"
#include "desktop.hpp"
#include "syshandler.hpp"

#pragma GCC optimize ("-fno-strict-aliasing")

NIContext* ctxt;
NIDesktop* desktop;



void NiMain(void* s)
{
	extern Video* screen;

	NiInstallSysHooks();
	NiLoadCursors();

	ctxt = new NIContext(screen, screen->getWidth(), screen->getHeight(), screen->getWidth(), 32);
	desktop = new NIDesktop(ctxt);

#ifdef KERNEL_DEBUG
	extern void NiDisplayRAM(void*);
	kernelProcess->createThread(NiDisplayRAM);
#endif

	extern void NiClockEventThread(void*);
	kernelProcess->createThread(NiClockEventThread);

	NIWindow* win0 = new NIWindow(ctxt, 0, 0, 1, 1);
	desktop->addWindow(win0);
	
	(new Process("C:/Banana/System/desktop.exe"))->createUserThread();

	while (1) {
		blockTask(TaskState::Paused);
	}
}