
#include <uwsbe/wsbe.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "D:/Users/Alex/Desktop/Banana/kernel/sys/syscalls.hpp"

extern "C" uint64_t SystemCall(size_t, size_t, size_t, size_t);

void* operator new(size_t size) { return malloc(size); }
void* operator new[](size_t size) {return malloc(size); }
void operator delete(void* p) { free(p); }
void operator delete[](void* p) {free(p); }
extern "C" void __cxa_pure_virtual() {}

Entry* entry;
Entry* entry2;
bool eswap = false;

void winFrameHandler(Frame* frame, Message msg)
{
	if (msg.key == Enter) {
		char* text = entry->getText();

		if (strlen(text) > 254) {
			return;
		}

		char text2[256];
		strcpy(text2, text);
		free(text);

		pid_t pid;

		char* argv[2] = { text, 0 };

		pid = SystemCall((size_t) SystemCallNumber::Spawn, 0, (size_t) argv, (size_t) argv[0]);
	}
}

int main(int argc, char* argv[])
{
	Toplevel* win = new Toplevel(100, 200, 350, 140, FrameFlags::Toplevel | FrameFlags::NoResize, "Run");
	win->add();
	win->keyDownHandler = winFrameHandler;

	(new Label(20, 32, "Enter the full path of an executable file,"))->add(win);
	(new Label(20, 52, "then press ENTER."))->add(win);
	
	entry = new Entry(20, 85, 280, "C:/Banana/System/");
	entry->add(win);

	entry2 = new Entry(20, 110, 280, "C:/Banana/");
	entry2->add(win);

	entry->stealFocus();
	win->repaintDesktop();

	while (1) {
		win->processEvents();
	}
}
