#pragma once

#include "context.hpp"

class NIWindow;

struct DesktopWindowNode
{
	NIWindow* win;
	DesktopWindowNode* next;
};

#define MOUSE_WIDTH 32
#define MOUSE_HEIGHT 32
#define MOUSE_BUFSZ (MOUSE_WIDTH * MOUSE_HEIGHT)

#define MAX_CURSOR_TYPES 8
#define CURSOR_DATA_SIZE (MOUSE_WIDTH * MOUSE_HEIGHT / 8 * 2)

#define MOUSE_OFFSET_NORMAL	(CURSOR_DATA_SIZE * 0)
#define MOUSE_OFFSET_TEXT	(CURSOR_DATA_SIZE * 1)
#define MOUSE_OFFSET_WAIT	(CURSOR_DATA_SIZE * 2)
#define MOUSE_OFFSET_TLDR	(CURSOR_DATA_SIZE * 3)
#define MOUSE_OFFSET_VERT	(CURSOR_DATA_SIZE * 4)
#define MOUSE_OFFSET_HORZ	(CURSOR_DATA_SIZE * 5)
#define MOUSE_OFFSET_HAND	(CURSOR_DATA_SIZE * 6)

class NIDesktop
{
private:


protected:
	DesktopWindowNode* head;
	NIContext* ctxt;

public:
	int mouseX;
	int mouseY;

	int cursorOffset;

	NIDesktop(NIContext* context);

	void addWindow(NIWindow* window);
	void raiseWindow(NIWindow* window);
	void deleteWindow(NIWindow* window);
	DesktopWindowNode* getLastNode();

	void completeRefresh();
	void rangeRefresh(int top, int bottom, int left, int right);
	void renderScanline(int line, int left, int right);

	void handleMouse(int xdelta, int ydelta, int buttons, int z);
};