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
	
	{
		File* f = new File("C:/Banana/Icons/Office/new.tga", kernelProcess);
		FileStatus fs = f->open(FILE_OPEN_READ);
		kprintf("FS = %d\n", (int) fs);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		kprintf("tgalen = %d\n", (int) tgaLen);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		fs = f->read(tgaLen, tgaData, &br);
		kprintf("br = %d, fs = %d\n", br, (int) fs);
		screen->putTGA(50 + 10 + 24 * 0, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/open.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 1, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/print.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 2, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}

	{
		File* f = new File("C:/Banana/Icons/Office/copy.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 4, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/paste.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 5, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}

	{
		File* f = new File("C:/Banana/Icons/Office/undo.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 7, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/redo.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 8, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}

	{
		File* f = new File("C:/Banana/Icons/Office/bold.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 10, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/italic.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 11, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}
	{
		File* f = new File("C:/Banana/Icons/Office/underline.tga", kernelProcess);
		f->open(FILE_OPEN_READ);
		uint64_t tgaLen;
		bool dir;
		f->stat(&tgaLen, &dir);
		int br;
		uint8_t* tgaData = (uint8_t*) malloc(tgaLen);
		f->read(tgaLen, tgaData, &br);
		screen->putTGA(50 + 10 + 24 * 12, 55 + WINDOW_TITLEBAR_HEIGHT, tgaData, tgaLen);
		f->close();
		delete f;
	}

	//(new Process("C:/Banana/System/newgui.exe"))->createUserThread();

	while (1) {
		blockTask(TaskState::Paused);
	}
}
