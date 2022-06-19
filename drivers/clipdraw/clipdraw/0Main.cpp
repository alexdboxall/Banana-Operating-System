#include <stdint.h>

#pragma GCC optimize ("O0")

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
#include "krnl/kheap.hpp"
#include <hal/video.hpp>

#pragma GCC optimize ("O0")

extern "C" {
	#include "libk/string.h"
}

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("O0")

#include "Region.hpp"
#include "NFrame.hpp"
#include "Video.hpp"
#include "Mouse.hpp"
#include "Font.hpp"
#include "Syshooks.hpp"

#pragma GCC optimize ("O0")

NDesktopWindow* desktopWindow;

void NiMain(void* s)
{
	extern Video* screen;

	kprintf("Clipdraw is now running...\n");

	screen->clearScreen(0x008080);

	mouseX = 50;
	mouseY = 50;

	// DON'T PUT SHIT ON THE STACK
	//
	// When the mouse handler gets called it will crash because 
	// the original stack won't be paged in (the interrupt stack will be in)

	initFonts();
	SYSTEM_FONT_HANDLE = getFontHandle(FontStyle{ "*SYSTEM", 12 });
	kprintf("System font handle = %d\n", SYSTEM_FONT_HANDLE);

	NWindow* win = new NWindow(80, 50, 350, 350);
	NWindow* awin = new NWindow(180, 88, 450, 450);
	NButton* textDemo = new NButton(15, 40, 1600, 600);
	//awin->addChild(textDemo);

	desktopWindow = new NDesktopWindow(0, 0, screen->getWidth(), screen->getHeight(), 0x008080);
	desktopWindow->addChild(win);
	desktopWindow->addChild(awin);

	mouseInit(screen);

	installSystemHooks();

	Region dummyRgn = createRectangleRegion(screen->getWidth() + 1, 1, 1, 1);

	desktopWindow->tryInvalidate();
	desktopWindow->repaint(screen, dummyRgn);

	(new Process("C:/Banana/System/CLIPDEMO.EXE"))->createUserThread();

	while (1) {
		blockTask(TaskState::Paused);
	}
}