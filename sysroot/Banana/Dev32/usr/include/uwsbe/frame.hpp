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

	Frame* parent = nullptr;
	Frame* focusChild = nullptr;

	WSBE* wsbe;
	void gotMessage(Message msg);
	virtual void _impl() = 0;

	bool wsbeRegistered = false;
	int wsbeX;
	int wsbeY;
	int wsbeW;
	int wsbeH;

public:
	Frame();

	WSBE* getWSBE();

	EventHandler keyDownHandler = nullptr;
	EventHandler focusEnterHandler = nullptr;
	EventHandler focusLeaveHandler = nullptr;
	EventHandler lbuttonDownHandler = nullptr;
	EventHandler lbuttonUpHandler = nullptr;
	EventHandler lbuttonDoubleHandler = nullptr;
	EventHandler mouseDragHandler = nullptr;
	EventHandler resizingHandler = nullptr;
	EventHandler resizedHandler = nullptr;
	EventHandler movingHandler = nullptr;
	EventHandler movedHandler = nullptr;
	EventHandler cursorBlinkHandler = nullptr;
	EventHandler conhostUpdateHandler = nullptr;

	virtual void stealFocus();
	virtual bool hasFocus();
	void add(Frame* parent);
	void repaintDesktop();
	void processEvents();
};

#endif