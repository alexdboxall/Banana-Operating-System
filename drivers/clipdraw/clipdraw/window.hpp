#pragma once

#include "context.hpp"

extern "C" {
#include "userlink.h"
}

#define WINDOW_TITLEBAR_HEIGHT 25

class NIWindow
{
private:
	NIContext* context;

	int bytesPerPixel;

protected:

public:
	struct RenderTableEntry
	{
		uint16_t leftSkip;
		uint16_t rightSkip;
	};

	union
	{
		uint8_t* data8;
		uint16_t* data16;
		uint32_t* data32;
	};

	int numEvents;
	int nextEventId;
	int firstEventId;
	NiEvent events[MAX_EVENTS_PER_WINDOW];

	bool valid;
	int renderTableLength;

	RenderTableEntry* renderTable;

	int xpos;
	int ypos;
	int width;
	int height;

	bool fullscreen;
	int rstrx;
	int rstry;
	int rstrw;
	int rstrh;

	uint32_t flags[WIN_MAX_FLAG_DWORDS];

	void rerender();
	void invalidate();
	void request();
	void realdraw();
	void SHADOW_TEST();
	void drawResizeMarker();

	NIWindow(NIContext* ctxt, int x, int y, int w, int h);
	void changeContext(NIContext* ctxt, int x, int y);
	void drawBasicWindow();

	void putpixel(int x, int y, uint32_t colour);

	void postEvent(NiEvent evnt);
	int getEventCount();
	NiEvent grabEvent();
};