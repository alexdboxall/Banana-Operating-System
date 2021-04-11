#ifndef _WSBE_FRAME_HPP
#define _WSBE_FRAME_HPP

#include <stdint.h>
#include <stddef.h>

extern "C" {
	#include "krnllink.h"
}

enum class FrameFlags: uint32_t
{
	NoDecoration = WIN_NODECORATION,
	NoResize = WIN_NORESIZING,
	Toplevel = WIN_TOPLEVELWIN,
};

FrameFlags operator |(FrameFlags a, FrameFlags b);

class Frame;
typedef void(*EventHandler)(Frame* frame, Message msg);

typedef Window WSBE;

class Frame
{
private:

protected:
	Frame* children[64];
	int nextChild = 0;

	WSBE* wsbe;
	void gotMessage(Message msg);
	virtual void _impl() = 0;

public:
	Frame();

	WSBE* getWSBE();

	EventHandler keyDownHandler = nullptr;

	void add(Frame* parent);
	void repaintDesktop();
	void processEvents();
};

#endif