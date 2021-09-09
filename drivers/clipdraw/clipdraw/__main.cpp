#include <stdint.h>

#pragma GCC optimize ("O1")

void NiMain(void* s);
void NiBegin(void* s)
{
	NiMain(s);
}

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
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

	extern void NiDisplayRAM(void*);
	kernelProcess->createThread(NiDisplayRAM);

	NIWindow* win0 = new NIWindow(ctxt, 0, 0, 1, 1);

	NIWindow* win1 = new NIWindow(ctxt, 50, 50, 400, 320);
	NIWindow* win2 = new NIWindow(ctxt, 200, 150, 500, 380);
	NIWindow* win3 = new NIWindow(ctxt, 125, 400, 270, 175);

	win3->flags |= WINFLAG_DISABLE_RESIZE;

	desktop->addWindow(win0);
	desktop->addWindow(win1);
	desktop->addWindow(win2);
	desktop->addWindow(win3);
	
	desktop->completeRefresh();

	(new Process("C:/Banana/System/newgui.exe"))->createUserThread();

	while (1) {
		blockTask(TaskState::Paused);
	}
}
