#ifndef _WSBE_WINDOW_HPP
#define _WSBE_WINDOW_HPP

#include "frame.hpp"

class Toplevel : public Frame
{
private:

protected:
	virtual void _impl() override;

	friend void _toplevelEnterHandler(Frame* f, Message msg);
	friend void _toplevelLeaveHandler(Frame* f, Message msg);
	friend void _toplevelResizingHandler(Frame* f, Message msg);
	friend void _toplevelResizedHandler(Frame* f, Message msg);
	friend void _toplevelMovingHandler(Frame* f, Message msg);
	friend void _toplevelMovedHandler(Frame* f, Message msg);

	void toplevelEnterHandler(Frame* f, Message msg);
	void toplevelLeaveHandler(Frame* f, Message msg);
	void toplevelResizingHandler(Frame* f, Message msg);
	void toplevelResizedHandler(Frame* f, Message msg);
	void toplevelMovingHandler(Frame* f, Message msg);
	void toplevelMovedHandler(Frame* f, Message msg);

	bool toplevelFocus = false;

public:
	Toplevel(int x, int y, int w, int h, const char* title = "");
	Toplevel(int x, int y, int w, int h, FrameFlags flags, const char* title = "");

	virtual void stealFocus() override;
	virtual bool hasFocus() override;

	void add();
	void setTitle(const char* title);
};

#endif