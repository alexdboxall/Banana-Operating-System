
#include "Primatives.hpp"
#include "Font.hpp"

uint32_t drawCharacter(Screen scr, Region rgn, int inX, int inY, uint32_t colour, char c)
{
	int characterHeight = 12;
	int characterWidth = 8;

	int scanline = 0;
	int i = 0;
	while (scanline < rgn.height && scanline < inY + characterHeight) {
		uint32_t dword = rgn.data[i++];
		int numInversions = dword & 0xFFFF;
		int times = dword >> 16;

		uint32_t* data = (uint32_t*) (rgn.data + i);

		i += numInversions;

		bool in = false;
		int x = 0;

		if (times + scanline >= inY) {
			while (x < rgn.width) {
				if (*data == x) {
					++data;
					in ^= true;
					--numInversions;
				}

				int modX = x - inX;
				if (in && modX >= 0 && modX < characterWidth) {
					for (int n = 0; n < times; ++n) {
						int row = scanline + n - inY;
						if (row >= 0 && row < characterHeight) {
							if (((font_array[((int) c) + row * 128] << modX) & 0x80)) {
								videoPutpixel(scr, rgn.relX + x, rgn.relY + scanline + n, colour);
							}
						}
					}
				}

				if (numInversions && *data < (unsigned) inX) {
					x = *data;
				} else {
					x++;
				}

				if (x > inX + characterWidth) {
					break;
				}
			}
		}

		scanline += times;
	}

	return characterWidth | (characterHeight << 16);
}

void fillRegion(Screen scr, Region rgn, uint32_t colour)
{
	int scanline = 0;
	int i = 0;

	while (scanline < rgn.height) {
		uint32_t dword = rgn.data[i++];
		if (dword == 0xFFFFFFFF) {
			return;
		}
		int numInversions = dword & 0xFFFF;
		int times = dword >> 16;

		uint32_t* data = (uint32_t*) (rgn.data + i);
		i += numInversions;

		bool in = false;
		int x = 0;
		while (x < rgn.width) {
			if (*data == x) {
				++data;
				in ^= true;
				--numInversions;
			}

			if (in) {
				if (rgn.dotted) {
					videoDrawRectDotted(scr, rgn.relX + x, rgn.relY + scanline, (*data) - x, times, colour);

				} else {
					videoDrawRect(scr, rgn.relX + x, rgn.relY + scanline, (*data) - x, times, colour);
				}
			}

			if (numInversions) {
				x = *data;

			} else if (!in) {		// no more inversions, and we're not in
				break;

			} else {
				++x;
			}
		}

		scanline += times;
	}
}
