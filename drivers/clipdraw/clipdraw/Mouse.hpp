#pragma once

extern int mouseX;
extern int mouseY;

#include "Video.hpp"

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

#define MOUSE_BUTTON_LEFT	1
#define MOUSE_BUTTON_MIDDLE	2
#define MOUSE_BUTTON_RIGHT	4

void showCursor(Screen scr);
void hideCursor(Screen scr, int oldX, int oldY, int newX, int newY);
void mouseInit(Screen scr);
bool handleMouse(Screen scr, int xDelta, int yDelta, int zDeltaHz, int zDeltaVt, int buttons);