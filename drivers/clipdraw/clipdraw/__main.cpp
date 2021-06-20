#include <stdint.h>

void start(void* s);
void begin(void* s)
{
	start(s);
}

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}


#include "context.hpp"
#include "window.hpp"

void start(void* s)
{
	extern Video* screen;

	NIContext ctxt(screen, screen->getWidth(), screen->getHeight(), screen->getWidth(), 32);

	for (int y = 0; y < screen->getHeight(); ++y) {
		for (int x = 0; x < screen->getWidth(); ++x) {
			ctxt.drvPutpixel4(x, y, 0x5580FF);
		}
	}

	NIWindow win1(&ctxt, 50, 50, 400, 320);
	NIWindow sha1(&ctxt, 45, 45, 410, 330);
	sha1.SHADOW_TEST();
	win1.realdraw();

	NIWindow win2(&ctxt, 200, 150, 500, 380);
	NIWindow sha2(&ctxt, 195, 145, 510, 390);
	sha2.SHADOW_TEST();
	win2.realdraw();

	NIWindow win3(&ctxt, 125, 400, 270, 175);
	NIWindow sha3(&ctxt, 120, 395, 280, 185);
	sha3.SHADOW_TEST();
	win3.realdraw();

	while (1) {
		blockTask(TaskState::Paused);
	}
}
