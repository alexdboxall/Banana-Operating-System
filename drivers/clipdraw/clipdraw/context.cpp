#include "context.hpp"

void NIContext::drvPutpixel4(int x, int y, uint32_t col)
{
	screen->putpixel(x, y, col);
}

void NIContext::drvDarken4(int x, int y, int amount)
{
	uint32_t og = screen->readPixelApprox(x, y);

	uint32_t r = (og >> 16) & 0xFF;
	uint32_t g = (og >>  8) & 0xFF;
	uint32_t b = (og >>  0) & 0xFF;

	r = r * amount / 100;
	g = g * amount / 100;
	b = b * amount / 100;

	uint32_t s = (r << 16) | (g << 8) | b;
	
	screen->putpixel(x, y, s);
}

NIContext::NIContext(Video* vid, int w, int h, int p, int _bitsPerPixel)
{
	screen = vid;
	width = w;
	height = h;
	pitch = p;
	bitsPerPixel = _bitsPerPixel;
}