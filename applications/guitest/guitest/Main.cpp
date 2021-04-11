
#include <uwsbe/wsbe.hpp>
#include <stdio.h>
#include <stdlib.h>

void* operator new(size_t size) {return malloc(size);}
void* operator new[](size_t size) {return malloc(size);}
void operator delete(void* p) {free(p);}
void operator delete[](void* p) {free(p);}
extern "C" void __cxa_pure_virtual() {}

int main(int argc, char* argv[])
{
	Toplevel* win = new Toplevel(100, 90, 350, 195, FrameFlags::Toplevel | FrameFlags::NoResize, "About Banana");
	win->add();

	(new Label(20, 32, "Banana 0.1.3"))->add(win);
	(new Label(20, 62, "Copyright (C) 2016-2021 Alex Boxall"))->add(win);
	(new Label(20, 132, "See C:/Banana/Legal/COPYRIGHT"))->add(win);
	(new Label(20, 150, "for third party notices."))->add(win);

	Entry* entry = new Entry(20, 98, 150, "Text");
	entry->add(win);

	(new Bitmap(230, 37, "C:/Banana/Icons/colour/ewrtherr.tga"))->add(win);

	while (1) {
		win->processEvents();
		entry->processEvents();
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
#include "uwsbe/krnllink.h"

int main (int argc, char *argv[])
{
	Window* win = wsbeCreateWindow(100, 90, 350, 195, WIN_TOPLEVELWIN | WIN_NORESIZING);
	wsbeSetWindowTitle(win, "About Banana");

	WsbeScript script = wsbeNewScript(1024);
	wsbeBufferFillRect(&script, 0, 0, WSBE_MATH_WIDTH_DEREF, WSBE_MATH_HEIGHT_DEREF, WIN_BGCOLOR);
	wsbeBufferDrawText(&script, 20, 10, "Banana 0.1.3", 0);
	wsbeBufferDrawText(&script, 20, 30, "Copyright (C) 2016-2021 Alex Boxall", 0);
	wsbeBufferDrawText(&script, 20, 100, "See C:/Banana/Legal/COPYRIGHT", 0);
	wsbeBufferDrawText(&script, 20, 118, "for third party notices.", 0);

	wsbeBufferDrawTGAFromFile(&script, "C:/Banana/Icons/colour/ewrtherr.tga", 230, 10);
	wsbeSetRepaintScript(win, script);

	wsbeAddWindow(wsbeDesktopWindow(), win);
	wsbePaintWindow(win);

	while (1) {
		;
	}

	return 0;
}*/