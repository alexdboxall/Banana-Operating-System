#pragma once

#include <stdint.h>
#include <hal/video.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

class NIContext
{
private:

protected:
	uint32_t* glyphRenderBuffer;

	char* fontNames[256];
	int nextFont = 0;

public:
	Video* screen;

	int width;
	int height;
	int pitch;
	int bitsPerPixel;

	NIContext(Video* video, int width, int height, int pitch, int bitsPerPixel);
	~NIContext();

	int renderTTF(int x, int y, uint32_t col, char* str, int* chars);
	void drvDarken4(int x, int y, int amount);
	void drvPutpixel4(int x, int y, uint32_t col);
};