#pragma once

#include <stdint.h>
#include <hal/video.hpp>

class NIContext
{
private:

protected:

public:
	Video* screen;
	
	int width;
	int height;
	int pitch;
	int bitsPerPixel;

	NIContext(Video* video, int width, int height, int pitch, int bitsPerPixel);

	void drvDarken4(int x, int y, int amount);
	void drvPutpixel4(int x, int y, uint32_t col);
};