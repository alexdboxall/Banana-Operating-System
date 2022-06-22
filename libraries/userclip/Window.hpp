
#pragma once

#include <stdint.h>

extern "C" {
	#include "C:\Users\Alex\Desktop\Banana\kernel\sys\syscalls.hpp"
	uint64_t SystemCall(size_t, size_t, size_t, size_t);
}

#include "C:\Users\Alex\Desktop\Banana\drivers\clipdraw\clipdraw\Userlink.hpp"

class Window
{
protected:
	void* krnlFrame;

	uint64_t performSystemCall(UserCommand cmd, void* arg);
	void setCoordinates(UserCommandArg::Coordinates args);
	void refreshCoordinates();

	int mostRecentX;
	int mostRecentY;
	int mostRecentW;
	int mostRecentH;
	int mostRecentAbsX;
	int mostRecentAbsY;

public:
	Window(int x, int y, int w, int h, const char* title = "", int flags = 0);

	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	void setSize(int w, int h);
	void setWidth(int w);
	void setHeight(int h);

	int getX(bool update = true);
	int getY(bool update = true);
	int getWidth(bool update = true);
	int getHeight(bool update = true);

	void invalidate();

	void setParentAsDesktop();
	void setParent(Window* window);

	void setFullscreen(bool state = true);
	void toggleFullscreen();
	bool isFullscreen();

	void hide(bool state = true);
	void unhide();
	bool isHidden();

	void raise();
};