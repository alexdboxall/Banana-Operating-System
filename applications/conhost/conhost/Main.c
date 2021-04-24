
#include <stdio.h>
#include <stdlib.h>

#include <uwsbe/krnllink.h>

#include "D:\Users\Alex\Desktop\Banana\kernel\sys\syscalls.hpp"

int CHAR_WIDTH = 7;
int CHAR_HEIGHT = 12;

uint16_t* vga;
Window* cons[25];
WsbeScript script;

int pid;

uint32_t vgaColours[16] = {
	0x000000,
	0x0000AA,
	0x00AA00,
	0x00AAAA,
	0xAA0000,
	0xAA00AA,
	0xAA5500,
	0xAAAAAA,
	0x555555,
	0x5555FF,
	0x55FF55,
	0x55FFFF,
	0xFF5555,
	0xFF55FF,
	0xFFFF55,
	0xFFFFFF
};

void redoPaintScript(bool repaint)
{
	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	SystemCall(GetVGAPtr, (size_t) vga, pid, 1);

	int cx = vga[2000];
	int cy = vga[2002];

	uint16_t* v = vga;
	for (int y = 0; y < 25; ++y) {
		bool repaintLine = repaint;

		script = wsbeNewScript();
		//wsbeBufferFillRect(&script, 0, 0, WSBE_MATH_WIDTH_DEREF, CHAR_HEIGHT, 0);

		for (int x = 0; x < 80; ++x) {
			uint16_t ch = *v++;
			char txt[2];
			txt[0] = ch & 0xFF;
			txt[1] = 0;

			wsbeBufferFillRect(&script, x * CHAR_WIDTH, 0, CHAR_WIDTH, CHAR_HEIGHT, vgaColours[(ch >> 12) & 0xF]);
			wsbeBufferDrawText(&script, x * CHAR_WIDTH, 0, txt, vgaColours[(ch >> 8) & 0xF]);

			if (x == cx && y == cy) {
				wsbeBufferDrawText(&script, x * CHAR_WIDTH, 0, "_", vgaColours[(ch >> 8) & 0xF]);
				repaintLine = true;
			}
		}

		wsbeSetRepaintScript(cons[y], script);
		wsbeDeleteScript(script);
		if (repaintLine) wsbePaintWindow(cons[y]);
	}
}

int main (int argc, char *argv[])
{
	CHAR_WIDTH = 7;
	CHAR_HEIGHT = 12;

	vga = (uint16_t*) malloc(4096);

	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
	
	char* aaa[] = { "C:/Banana/System/command.exe", 0 };
	pid = SystemCall(Spawn, 1, (size_t) aaa, (size_t) aaa[0]);

	SystemCall(GetVGAPtr, (size_t) vga, pid, 1);

	Window* win = wsbeCreateWindow(40, 40, 80 * CHAR_WIDTH + 10, 25 + 25 * CHAR_HEIGHT + 10, WIN_TOPLEVELWIN | WIN_NORESIZING);
	wsbeSetWindowTitle(win, (const char*) (vga + 2004));
	wsbeAddWindow(wsbeDesktopWindow(), win);
	wsbePaintWindow(win);

	for (int i = 0; i < 25; ++i) {
		cons[i] = wsbeCreateWindow(5, 30 + i * CHAR_HEIGHT, 80 * CHAR_WIDTH, CHAR_HEIGHT, WIN_NODECORATION);
		wsbeAddWindow(win, cons[i]);
	}
	
	redoPaintScript(true);

	extern uint64_t SystemCall(size_t, size_t, size_t, size_t);

	while (1) {
		Message msg;
		int count = wsbeGetMessage(win, &msg);
		if (count && msg.type == MESSAGE_KEYDOWN) {
			redoPaintScript(true);
		}
		SystemCall(Yield, 0, 0, 0);
	}

	return 0;
}