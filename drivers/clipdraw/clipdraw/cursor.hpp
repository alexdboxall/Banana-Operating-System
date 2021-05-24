#pragma once

#include "context.hpp"
#include "gdo.hpp"

#define MOUSE_BUTTON_LEFT			1
#define MOUSE_BUTTON_MIDDLE			2
#define MOUSE_BUTTON_RIGHT			4
#define MOUSE_BUTTON_UP				8
#define MOUSE_BUTTON_DOWN			16
#define MOUSE_SCROLL_LEFT			32
#define MOUSE_SCROLL_RIGHT			64

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

extern uint8_t mouse_data[CURSOR_DATA_SIZE * MAX_CURSOR_TYPES];

void processMouse(int mx, int my, int buttons);
void setupCursor();
void startMouse();