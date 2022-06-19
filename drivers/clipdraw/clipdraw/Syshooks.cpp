
#include <thr/prcssthr.hpp>
#include <hal/keybrd.hpp>
#include <hal/video.hpp>
#include <krnl/atexit.hpp>
#include <sys/syscalls.hpp>
#include "krnl/common.hpp"
#include "krnl/kheap.hpp"
#include "libk/string.h"
#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "krnl/virtmgr.hpp"
#include "thr/elf.hpp"
#include "hal/timer.hpp"
#include "krnl/unixfile.hpp"
#include "krnl/pipe.hpp"
#include "krnl/terminal.hpp"
#include "hal/clock.hpp"
#include "hal/keybrd.hpp"
#include "fs/vfs.hpp"
#include "hw/cpu.hpp"
#include "fs/symlink.hpp"
#include <krnl/powctrl.hpp>

#include "Mouse.hpp"
#include "Video.hpp"
#include "Userlink.hpp"
#include "NFrame.hpp"
#include "VGA.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

extern void (*guiMouseHandler) (int xdelta, int ydelta, int buttons, int z);
extern void (*guiPanicHandler)(char* message); extern uint64_t(*systemCallHandlers[])(regs* r);
extern void (*guiKeyboardHandler) (KeyboardToken kt, bool* keystates);

void kernelPanicHandler(char* message)
{
	extern Video* screen;
	screen->clearScreen(0x000080);

	for (int i = 0; " STOP ERROR "[i]; ++i) {
		drawVGAChar(6 + i, 2, " STOP ERROR "[i], 0x000080, 0xFFFFFF);
	}

	for (int i = 0; "A problem has occured and Banana cannot continue."[i]; ++i) {
		drawVGAChar(6 + i, 4, "A problem has occured and Banana cannot continue."[i], 0xFFFFFF, 0x000080);
	}

	for (int i = 0; message[i]; ++i) {
		drawVGAChar(10 + i, 6, message[i], 0xFFFFFF, 0x000080);
	}

	while (1) {
		HalStallProcessor();
	}
}

void kernelMouseHandler(int x, int y, int buttons, int z)
{
	extern Video* screen;
	handleMouse(screen, x, y, 0, 0, buttons);
}

uint64_t kernelSystemCallHandler(regs* r)
{
	return usermodeLinkHandler((UserCommand) r->ebx, (NFrame*) r->ecx, (void*) r->edx);
}

void installSystemHooks()
{
	guiPanicHandler = kernelPanicHandler;
	guiMouseHandler = kernelMouseHandler;

	systemCallHandlers[(int) SystemCallNumber::WSBE] = kernelSystemCallHandler;
}
