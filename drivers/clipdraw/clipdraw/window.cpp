#include "window.hpp"
#include <krnl/panic.hpp>
#include <core/kheap.hpp>

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

NIWindow::NIWindow(NIContext* ctxt, int _x, int _y, int _w, int _h)
{
	width = _w;
	height = _h;

	fullscreen = false;

	valid = false;
	renderTable = nullptr;
	renderTableLength = 0;

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
				if (dZ > 102/*80*/) {
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
				context->drvPutpixel4(x + xpos, y + ypos, renderTable[y].data32[x]);
			}
		}
	}
}

int curveLookup7[] = { 5, 3, 2, 1, 1, 0, 0, 0 };
int curveLoopup11[] = { 9, 6, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0 };

void NIWindow::rerender()
{
	const bool largeRounded = false;

	if (valid) {
		invalidate();
	}

	renderTableLength = height;
	renderTable = (RenderTableEntry*) malloc(sizeof(RenderTableEntry) * renderTableLength);

	for (int i = 0; i < renderTableLength; ++i) {
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

		renderTable[i].data32 = (uint32_t*) malloc(width * bytesPerPixel);
	}

	/// TODO: call user function to populate the framebuffer

	//placeholder
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			putpixel(i, j, j > WINDOW_TITLEBAR_HEIGHT ? 0xD4D4D4 : 0xFFFFFF);
		}
	}
}

void NIWindow::invalidate()
{
	if (valid && renderTable) {
		for (int i = 0; i < renderTableLength; ++i) {
			free(renderTable[i].data8);
		}

		free(renderTable);
	}

	renderTable = nullptr;
	renderTableLength = 0;
	valid = false;
}

void NIWindow::request()
{
	if (!valid) {
		rerender();
	}
}

void NIWindow::putpixel(int x, int y, uint32_t colour)
{
	if (bytesPerPixel == 4) renderTable[y].data32[x] = colour;
	else if (bytesPerPixel == 2) renderTable[y].data16[x] = colour;
	else renderTable[y].data8[x] = colour;
}