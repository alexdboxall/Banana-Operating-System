#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MAX_EVENTS_PER_WINDOW	24

#define EVENT_TYPE_NULL			0
#define EVENT_TYPE_RESIZED		1
#define EVENT_TYPE_MOVED		2
#define EVENT_TYPE_REPAINT		3
#define EVENT_TYPE_MOUSE_MOVE	4
#define EVENT_TYPE_MOUSE_DRAG	5
#define EVENT_TYPE_MOUSE_DOWN	6
#define EVENT_TYPE_MOUSE_UP		7
#define EVENT_TYPE_KEYDOWN		8
#define EVENT_TYPE_KEYUP		9
#define EVENT_TYPE_RMOUSE_DOWN	10
#define EVENT_TYPE_RMOUSE_UP	11
#define EVENT_TYPE_RESIZE_DOWN	12

#define WIN_MAX_FLAG_DWORDS		1

#define WIN_FLAGS_0_NO_RESIZE							(1 << 0)
#define WIN_FLAGS_0_HIDE_ON_INVALIDATE					(1 << 1)
#define WIN_FLAGS_0_BLACK_ON_INVALIDATE					(1 << 2)
#define WIN_FLAGS_0_DRAW_ON_INVALIDATE					(1 << 3)
#define WIN_FLAGS_0_INTERNAL_HAS_BEEN_INVALIDATED		(1 << 4)
#define WIN_FLAGS_0_DRAW_RESIZE_MARKER					(1 << 5)
#define WIN_FLAGS_0_NO_SHADOWS							(1 << 6)
#define WIN_FLAGS_0_FORCE_RECTANGULAR					(1 << 7)
#define WIN_FLAGS_0_DRAW_OUTLINE_INSTEAD_OF_SHADOW		(1 << 8)
#define WIN_FLAGS_0_HIDDEN								(1 << 9)
#define WIN_FLAGS_0_PRETTY								(1 << 10)
#define WIN_FLAGS_0_INTERNAL_USERMODE_INIT_HELPER		(1 << 11)

#define WIN_FLAGS_DEFAULT_0 (WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_DRAW_ON_INVALIDATE | WIN_FLAGS_0_DRAW_RESIZE_MARKER)

typedef struct NiEvent {
	void* krnlWindow;

	int mouseButtons : 10;
	int ctrl : 1;
	int alt : 1;
	int shift : 1;
	int type : 18;
	int needsRedraw : 1;

	int16_t mouseX;
	int16_t mouseY;
	int16_t x, y, w, h;

	uint16_t key;

} NiEvent; 

typedef struct NiLinkWindowStruct
{
	char name[160];

	void* krnlWindow;

	int x;
	int y;
	int w;
	int h; 
	
	uint32_t flags[WIN_MAX_FLAG_DWORDS];

	uint32_t* buffer;
	int bufferSize;

	NiEvent evnt;

} NiLinkWindowStruct;

#define LINKCMD_CREATE_WINDOW				0
#define LINKCMD_DESTROY_WNIDOW				3
#define LINKCMD_RESUPPLY_FRAMEBUFFER		4
#define LINKCMD_CLEAR_FRAMEBUFFER			5
#define LINKCMD_GET_EVENTS					6
#define LINKCMD_UPDATE_FLAGS				7
#define LINKCMD_REDRAW						8
#define LINKCMD_READ_FLAGS					9
#define LINKCMD_RESUPPLY_SCANLINE			10
#define LINKCMD_RESUPPLY_DESKTOP			11
#define LINKCMD_BE_THE_DESKTOP				12