#include "window.hpp"
#include <krnl/panic.hpp>
#include <core/kheap.hpp>

extern "C" {
#include "libk/string.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

void NIWindow::changeContext(NIContext* ctxt, int _x, int _y)
{
	invalidate();

	context = ctxt;
	xpos = _x;
	ypos = _y;

	if (context->bitsPerPixel <= 8) bytesPerPixel = 1;
	else if (context->bitsPerPixel <= 16) bytesPerPixel = 2;
	else bytesPerPixel = 4;

	rerender();
}

void NIWindow::postEvent(NiEvent evnt)
{
	if (evnt.type == EVENT_TYPE_MOUSE_MOVE && nextEventId && events[nextEventId - 1].type == EVENT_TYPE_MOUSE_MOVE && evnt.mouseButtons == events[nextEventId - 1].mouseButtons) {
		//return;
	}
	if (evnt.type == EVENT_TYPE_MOUSE_DRAG && nextEventId && events[nextEventId - 1].type == EVENT_TYPE_MOUSE_DRAG && evnt.mouseButtons == events[nextEventId - 1].mouseButtons) {
		//return;
	}
	if (numEvents == MAX_EVENTS_PER_WINDOW) {
		return;
	}

	kprintf("Posting event.\n");
	kprintf("ID = %d\n", nextEventId);
	kprintf("this = 0x%X\n", this);
	kprintf("dest = 0x%X\n", &events[nextEventId]);
	kprintf("src = 0x%X\n", &evnt);
	events[nextEventId] = evnt;
	nextEventId = (nextEventId + 1) % MAX_EVENTS_PER_WINDOW;
	numEvents++;
}

int NIWindow::getEventCount()
{
	return numEvents;
}

NiEvent NIWindow::grabEvent()
{
	NiEvent e = events[firstEventId];
	events[firstEventId].type = EVENT_TYPE_NULL;
	firstEventId = (firstEventId + 1) % MAX_EVENTS_PER_WINDOW;
	numEvents--;
	return e;
}

NIWindow::NIWindow(NIContext* ctxt, int _x, int _y, int _w, int _h)
{
	width = _w;
	height = _h;

	fullscreen = false;

	for (int i = 0; i < WIN_MAX_FLAG_DWORDS; ++i) {
		flags[i] = 0;
	}
	flags[0] |= WIN_FLAGS_0_HIDDEN;

	valid = false;
	renderTable = nullptr;
	renderTableLength = 0;

	numEvents = 0;
	nextEventId = 0;
	firstEventId = 0;

	changeContext(ctxt, _x, _y);
}

void NIWindow::SHADOW_TEST()
{
	request();

	if (renderTableLength != height) {
		KePanic("ASSERTION FAILURE (A).");
	}

	if (bytesPerPixel == 4) {
		for (int y = 0; y < height; ++y) {
			int ls = renderTable[y].leftSkip;
			int rs = renderTable[y].rightSkip;

			for (int x = ls; x < width - rs; ++x) {
				if (!(y < 6 || y > height - 6 || x < ls + 6 || x > width - rs - 6)) continue;

				int dC = 490 / (y + 5);
				int dD = 490 / ((height - rs) - y + 4);

				int dY = dC > dD ? dC : dD;
				if (dY < 10) dY = 10;
				int dYY8 = dY * dY * 8;

				int dA = 490 / (x + 5);
				int dB = 490 / ((width - rs) - x + 4);

				int dX = dA > dB ? dA : dB;

				if (dX < 10) dX = 10;

				int dZ = (dX * dX * 8 + dYY8 + dX * dY) >> 8;
				if (dZ > 102) {
					dZ = ((dZ - 102) >> 1) + 102;
				}
				if (dZ > 115) {
					dZ = ((dZ - 115) >> 2) + 115;
				}
				if (dZ >= 128) continue;
				if (dZ < 10) dZ = 10;

				context->drvDarken4(x + xpos, y + ypos, dZ);
			}
		}
	}
}

void NIWindow::realdraw()
{
	request();

	if (renderTableLength != height) {
		KePanic("ASSERTION FAILURE (A).");
	}

	if (bytesPerPixel == 4) {
		for (int y = 0; y < height; ++y) {
			int ls = renderTable[y].leftSkip;
			int rs = renderTable[y].rightSkip;
			for (int x = ls; x < width - rs; ++x) {
				context->drvPutpixel4(x + xpos, y + ypos, data32[y * width + x]);
			}
		}
	}
}

int curveLookup7[]	= { 4, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

// { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// { 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// { 4, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// { 5, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, };
// { 9, 6, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, };

int curveLoopup11[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };	

void NIWindow::drawBasicWindow()
{
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			putpixel(i, j, j > WINDOW_TITLEBAR_HEIGHT ? 0xD4D4D4 : 0xFFFFFF);
		}
	}
}

void NIWindow::drawResizeMarker()
{
	if (!(flags[0] & WIN_FLAGS_0_NO_RESIZE) && !fullscreen) {
		putpixel(width - 10 - 3, height - 2 - 3, 0x555555);
		putpixel(width -  8 - 3, height - 2 - 3, 0x555555);
		putpixel(width -  6 - 3, height - 2 - 3, 0x555555);
		putpixel(width -  4 - 3, height - 2 - 3, 0x555555);
		putpixel(width -  2 - 3, height - 2 - 3, 0x555555);

		putpixel(width - 8 - 3, height - 4 - 3, 0x555555);
		putpixel(width - 6 - 3, height - 4 - 3, 0x555555);
		putpixel(width - 4 - 3, height - 4 - 3, 0x555555);
		putpixel(width - 2 - 3, height - 4 - 3, 0x555555);

		putpixel(width - 6 - 3, height - 6 - 3, 0x555555);
		putpixel(width - 4 - 3, height - 6 - 3, 0x555555);
		putpixel(width - 2 - 3, height - 6 - 3, 0x555555);

		putpixel(width - 4 - 3, height - 8 - 3, 0x555555);
		putpixel(width - 2 - 3, height - 8 - 3, 0x555555);

		putpixel(width - 2 - 3, height - 10 - 3, 0x555555);
	}
}

void NIWindow::rerender()
{
	const bool largeRounded = false;
	
	if (valid) {
		invalidate();
	}

	renderTableLength = height;
	renderTable = (RenderTableEntry*) malloc(sizeof(RenderTableEntry) * renderTableLength);
	data32 = (uint32_t*) malloc(height * width * bytesPerPixel);

	for (int i = 0; i < renderTableLength; ++i) {
		if (fullscreen || (flags[0] & WIN_FLAGS_0_FORCE_RECTANGULAR)) {
			renderTable[i].leftSkip = 0;
			renderTable[i].rightSkip = 0;
		} else {
			if (i < (largeRounded ? 11 : 7)) {
				renderTable[i].leftSkip = largeRounded ? curveLoopup11[i] : curveLookup7[i];
				renderTable[i].rightSkip = largeRounded ? curveLoopup11[i] : curveLookup7[i];

			} else if (i > height - (largeRounded ? 11 : 7)) {
				renderTable[i].leftSkip = largeRounded ? curveLoopup11[height - i] : curveLookup7[height - i];
				renderTable[i].rightSkip = largeRounded ? curveLoopup11[height - i] : curveLookup7[height - i];

			} else {
				renderTable[i].leftSkip = 0;
				renderTable[i].rightSkip = 0;
			}
		}
	}
	valid = true;

	if (!(flags[0] & WIN_FLAGS_0_HIDE_ON_INVALIDATE)) {
		if (flags[0] & WIN_FLAGS_0_BLACK_ON_INVALIDATE) {
			memset(data32, 0, height * width * bytesPerPixel);
		}
		if (flags[0] & WIN_FLAGS_0_DRAW_ON_INVALIDATE) {
			drawBasicWindow();
		}
	}
}

void NIWindow::invalidate()
{
	if (valid && renderTable && data32) {
		free(data32);
		free(renderTable);
	}

	renderTable = nullptr;
	renderTableLength = 0;
	valid = false;

	hadFullRefreshSinceInvalidate = false;

	flags[0] |= WIN_FLAGS_0_INTERNAL_HAS_BEEN_INVALIDATED;
}

void NIWindow::request()
{
	if (!valid) {
		rerender();
	}
}

void NIWindow::putpixel(int x, int y, uint32_t colour)
{
	 data32[y * width + x] = colour;
}