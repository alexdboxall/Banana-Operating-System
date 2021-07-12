#include <stdint.h>

#pragma GCC optimize ("O1")

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
#include "desktop.hpp"

#pragma GCC optimize ("-fno-strict-aliasing")

#include "monika.hpp"
/*uint16_t og = justMonika[(line * 480 / ctxt->height) * 640 + (i * 640 / ctxt->width)];

			uint32_t r = ((og >> 5) & 0x3) * 85;
			uint32_t g = ((og >> 2) & 0x7) * 36;
			uint32_t b = ((og >> 0) & 0x3) * 85;

			renderData[i] = (r << 16) | (g << 8) | b;*/

void monikaBsod(char* msg)
{
	extern Video* screen;

	int i = 0;
	int m = 0;
	while (1) {
		uint8_t val = justMonika[m++];
		uint8_t count = 1;
		if (val >= 0x80) {
			count = val - 0x80;
			val = justMonika[m++];
		}

		for (int j = 0; j < count; ++j) {
			uint32_t r = ((val >> 5) & 3) * 85;
			uint32_t g = ((val >> 2) & 7) * 36;
			uint32_t b = ((val >> 0) & 3) * 85;
			uint32_t col = (r << 16) | (g << 8) | b;
			screen->putpixel(i % 640, i / 640, col);
			++i;
		}
	}
}

void start(void* s)
{
	extern Video* screen;
	extern void (*guiPanicHandler)(char* message);

	guiPanicHandler = monikaBsod;

	monikaBsod("JUST MONIKA");

	NIContext* ctxt = new NIContext(screen, screen->getWidth(), screen->getHeight(), screen->getWidth(), 32);

	NIDesktop* desktop = new NIDesktop(ctxt);

	NIWindow* win0 = new NIWindow(ctxt, 0, 0, 1, 1);

	NIWindow* win1 = new NIWindow(ctxt, 50, 50, 400, 320);
	NIWindow* win2 = new NIWindow(ctxt, 200, 150, 500, 380);
	NIWindow* win3 = new NIWindow(ctxt, 125, 400, 270, 175);

	desktop->addWindow(win0);
	desktop->addWindow(win1);
	desktop->addWindow(win2);
	desktop->addWindow(win3);

	desktop->completeRefresh();

	while (1) {
		blockTask(TaskState::Paused);
	}

	/*NIWindow win1(&ctxt, 50, 50, 400, 320);
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
	win3.realdraw();*/

	/* {
		int chrs = 0;
		int total = 0;
		int xp = win3.xpos + 15;
		int yp = win3.ypos + 3;

		do {
			xp += ctxt.renderTTF(xp, yp, 0, (char*) "Run..." + total, &chrs);
			total += chrs;
		} while (chrs);
	}
	{
		int chrs = 0;
		int total = 0;
		int xp = win2.xpos + 15;
		int yp = win2.ypos + 3;

		do {
			xp += ctxt.renderTTF(xp, yp, 0xAAAAAA, (char*) "About Banana" + total, &chrs);
			total += chrs;
		} while (chrs);
	}
	{
		int chrs = 0;
		int total = 0;
		int xp = win1.xpos + 15;
		int yp = win1.ypos + 3;

		do {
			xp += ctxt.renderTTF(xp, yp, 0xAAAAAA, (char*) "Notepad" + total, &chrs);
			total += chrs;
		} while (chrs);
	}
	*/

	while (1) {
		blockTask(TaskState::Paused);
	}
}
