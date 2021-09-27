#pragma once

#include "context.hpp"
#include "list.hpp"

class NIWindow;


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

void NiLoadCursors();

class NIDesktop
{
private:


protected:
	NIContext* ctxt;

public:
	List<NIWindow*>* head;
	
	int mouseX;
	int mouseY;
	int mouseButtons;

	int cursorOffset;

	NIDesktop(NIContext* context);

	void addWindow(NIWindow* window);
	void raiseWindow(NIWindow* window);
	void deleteWindow(NIWindow* window);

	void invalidateAllDueToFullscreen(NIWindow* ignoredWindow);

	void completeRefresh();
	void rangeRefresh(int top, int bottom, int left, int right);
	void renderScanline(int line, int left, int right);
	void refreshWindowBounds(NIWindow* window, int start = -1, int end = -1);

	void handleMouse(int xdelta, int ydelta, int buttons, int z);

	NIWindow* getTopmostWindowAtPixel(int x, int y);
};

extern "C" {
#include "userlink.h"
}
NiEvent NiCreateEvent(NIWindow* win, int type, bool redraw);
