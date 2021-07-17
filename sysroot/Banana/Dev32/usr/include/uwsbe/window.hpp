#ifndef _WSBE_WINDOW_HPP
#define _WSBE_WINDOW_HPP

extern "C" {
	#include "krnllink.h"
}

class Toplevel
{
private:

protected:
	Window* kernel;
	Window* user;

	void repaintDesktop();

public:
	Toplevel(int x, int y, int w, int h, const char* title = "");

	void add();
	void setTitle(const char* title);
	
	Window* _getWSBEWindow();
	 
};

#endif