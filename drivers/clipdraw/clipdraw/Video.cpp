
#include <hal/video.hpp>

#include "Video.hpp"
#include "Mouse.hpp"

#pragma GCC optimize ("Os")

void videoDrawRect(Screen scr, int x, int y, int w, int h, uint32_t colour)
{
	scr->putrect(x, y, w, h, colour);
}

void videoDrawRectDotted(Screen scr, int x, int y, int w, int h, uint32_t colour)
{
	if (x > scr->getWidth()) return;
	if (y > scr->getHeight()) return;
	if (x + w < 0) return;
	if (y + h < 0) return;
	if (x < 0) {
		w += x;
		x = 0;
	}
	if (y < 0) {
		h += y;
		y = 0;
	}
	if (x + w > scr->getWidth()) {
		w = scr->getWidth() - x;
	}
	if (y + h > scr->getHeight()) {
		h = scr->getHeight() - y;
	}
	//scr->putrect(x, y, w, h, colour);
	//return;

	for (int j = 0; j < h; ++j) {
		//if (y + j < 0) continue;
		//if (y + j >= scr->getHeight()) break;
		uint32_t modcolour = ((x + y + j) & 1) ? colour ^ 0xFFFFFF : colour;
		for (int k = 0; k < w; ++k) {
			//if (x + k < 0 || y + j < 0) continue;
			scr->putpixel(x + k, y + j, modcolour);
			modcolour ^= 0xFFFFFF;
		}
	}
}

uint32_t cursorBuffer[32 * 32];

uint32_t* videoSaveAreaUnderCursor(Screen scr, int xx, int yy)
{
	for (int y = 0; y < 32; y++) {
		if (y + yy >= scr->getHeight()) {
			break;
		}

		for (int x = 0; x < 32; x++) {
			if (x + xx >= scr->getWidth()) {
				break;
			}

			cursorBuffer[y * 32 + x] = scr->readPixelApprox(xx + x, yy + y);
		}
	}

	return cursorBuffer;
}

void videoPutpixel(Screen scr, int x, int y, uint32_t colour)
{
	scr->putpixel(x, y, colour);
}

void videoDrawCursor(Screen scr, int mouse_x, int mouse_y, uint32_t* data)
{
	scr->drawCursor(mouse_x, mouse_y, data, false);
}