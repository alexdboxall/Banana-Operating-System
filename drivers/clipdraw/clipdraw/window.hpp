#pragma once

#include "context.hpp"

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

		union
		{
			uint8_t* data8;
			uint16_t* data16;
			uint32_t* data32;
		};
	};

	bool valid;
	int renderTableLength;

	RenderTableEntry* renderTable;

	int xpos;
	int ypos;
	int width;
	int height;

	void rerender();
	void invalidate();
	void request();
	void realdraw();
	void SHADOW_TEST();
	
	NIWindow(NIContext* ctxt, int x, int y, int w, int h);
	void changeContext(NIContext* ctxt, int x, int y);

	void putpixel(int x, int y, uint32_t colour);
};