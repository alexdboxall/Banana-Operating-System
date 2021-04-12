
#include <uwsbe/wsbe.hpp>
#include <stdio.h>
#include <stdlib.h>

void* operator new(size_t size) {return malloc(size);}
void* operator new[](size_t size) {return malloc(size);}
void operator delete(void* p) {free(p);}
void operator delete[](void* p) {free(p);}
extern "C" void __cxa_pure_virtual() {}

#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"
extern "C" uint64_t SystemCall(size_t, size_t, size_t, size_t);

Label* ramLabel;

void update(Frame* frame, Message msg) {
	uint32_t data = SystemCall((int) SystemCallNumber::GetRAMData, 0, 0, 0);
	int percentUsed = data >> 24;
	uint32_t totalKilobytes = (data & 0xFFFFFF) * 4;
	uint32_t usedKilobytes = totalKilobytes * percentUsed / 100;

	char str[256];
	int percent = 0;

	sprintf(str, "%d / %d used. (%d%%)", usedKilobytes, totalKilobytes, percentUsed);
}

int main(int argc, char* argv[])
{
	Toplevel* win = new Toplevel(100, 90, 350, 195, FrameFlags::Toplevel | FrameFlags::NoResize, "About Banana");
	win->add();

	(new Label(20, 32, "Banana 0.1.3"))->add(win);
	(new Label(20, 62, "Copyright (C) 2016-2021 Alex Boxall"))->add(win);
	(new Label(20, 132, "See C:/Banana/Legal/COPYRIGHT"))->add(win);
	(new Label(20, 150, "for third party notices."))->add(win);

	win->keyDownHandler = update;

	//int percent = Phys::usedPages * 100 / Phys::usablePages;
	//return Phys::usablePages | (percent << 24);

	ramLabel = new Label(20, 95, "");
	ramLabel->add(win);

	(new Bitmap(230, 37, "C:/Banana/Icons/colour/ewrtherr.tga"))->add(win);

	win->repaintDesktop();

	while (1) {
		win->processEvents();
	}
}
