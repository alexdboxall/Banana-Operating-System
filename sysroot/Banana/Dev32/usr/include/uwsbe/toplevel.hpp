#ifndef _WSBE_WINDOW_HPP
#define _WSBE_WINDOW_HPP

#include "frame.hpp"

class Toplevel : public Frame
{
private:

protected:
	virtual void _impl() override;

public:
	Toplevel(int x, int y, int w, int h, const char* title = "");
	Toplevel(int x, int y, int w, int h, FrameFlags flags, const char* title = "");

	void add();
	void setTitle(const char* title);
};

#endif