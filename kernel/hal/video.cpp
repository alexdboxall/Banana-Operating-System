#include "core/main.hpp"
#include "core/kheap.hpp"
#include "hal/device.hpp"
#include "hal/video.hpp"

extern "C" {
#include "libk/string.h"
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

Video* screen;

Video::Video(const char* name) : Device(name)
{
	deviceType = DeviceType::Screen;
}

Video::~Video()
{

}

bool Video::isMonochrome()
{
	return mono;
}

int Video::getWidth()
{
	return width;
}

int Video::getHeight()
{
	return height;
}

void Video::putpixel(int x, int y, uint32_t col)
{
	kprintf("Bad putpixel.\n");
}

void Video::drawCursor(int mouse_x, int mouse_y, uint8_t* data, int invertMouse)
{
	//No more hacky mouse, instead we're going to rather inefficiently 
	//copy the pixels from our mouse image into the framebuffer
	for (int y = 0; y < 32; y++) {

		//Make sure we don't draw off the bottom of the screen
		if (y + mouse_y >= getHeight()) {
			break;
		}

		uint32_t wte = *(((uint32_t*) data) + y + 0);
		uint32_t blk = *(((uint32_t*) data) + y + 32);

		for (int x = 0; x < 32; x++) {

			//Make sure we don't draw off the right side of the screen
			if (x + mouse_x >= getWidth()) {
				break;
			}

			if (blk & 1) {
				putpixel(x + mouse_x, y + mouse_y, invertMouse ? 0xFFFFFF : 0);
			} else if (wte & 1) {
				putpixel(x + mouse_x, y + mouse_y, invertMouse ? 0 : 0xFFFFFF);
			}

			blk >>= 1;
			wte >>= 1;
		}
	}
}

//seriously, override this. This is slower than slow.
void Video::putrect(int x, int y, int w, int h, uint32_t colour)
{
	int maxX = x + w;
	int maxY = y + h;

	for (; y < maxY; ++y) {
		for (; x < maxX; ++x) {
			putpixel(x, y, colour);
		}
	}
}

//please, please, override this when you write a video driver
//this is a last resort function that should never be called
void Video::blit(uint32_t* buffer, int x, int y, int _width, int _height)
{
	for (int h = y; h < y + _height; ++h) {
		if (h > this->height) {
			break;
		}
		for (int w = x; w < x + _width; ++w) {
			if (w > this->width) {
				buffer++;
			} else {
				putpixel(x, y, *buffer++);
			}
		}
	}
}

//this will be even SLOWER! 
//any video driver writer that doesn't implement this should not be writing drivers
void Video::clearScreen(uint32_t colour)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			putpixel(x, y, colour);
		}
	}
}

typedef struct
{
	uint8_t magic1;             // must be zero
	uint8_t colormap;           // must be zero
	uint8_t encoding;           // must be 2
	uint16_t cmaporig;			// must be zero
	uint16_t cmaplen;			// must be zero
	uint8_t cmapent;            // must be zero
	uint16_t x;                 // must be zero
	uint16_t y;                 // image's height
	uint16_t h;                 // image's height
	uint16_t w;                 // image's width
	uint8_t bpp;                // must be 32
	uint8_t pixeltype;          // must be 40
} __attribute__((packed)) tga_header_t;

/**
 * Parse TGA format into pixels. Returns NULL or error, otherwise the returned data looks like
 *   ret[0] = width of the image
 *   ret[1] = height of the image
 *   ret[2..] = 32 bit ARGB pixels (blue channel in the least significant byte, alpha channel in the most)
 */

uint32_t* Video::tgaParse(uint8_t* ptr, int size, int* widthOut, int* heightOut)
{
    uint32_t* data;
	int j, k;
	int w = (ptr[13] << 8) + ptr[12];
	int h = (ptr[15] << 8) + ptr[14];
	int o = (ptr[11] << 8) + ptr[10];
    int m = ((ptr[1] ? (ptr[7] >> 3) * ptr[5] : 0) + 18);

    if (w < 1 || h < 1) {
        kprintf("width or height < 1\n");
        return NULL;
    }

    data = (uint32_t*) malloc((w * h + 2) * sizeof(uint32_t));
	tga_header_t* header = (tga_header_t*) data;

    if (!data) {
        kprintf("malloc stopped working");
        return NULL;
    }

    kprintf("TGA type %d\n", ptr[2]);
    switch (ptr[2]) {
    case 2:
        if (ptr[5] != 0 || ptr[6] != 0 || header->colormap != 0 || (header->bpp != 24 && header->bpp != 32)) {
            kprintf("case 2 null.\n");
            free(data);
            return NULL;
        }
        for (int y = 0, i = 0; y < h; y++) {
			j = ((!o ? h - y - 1 : y) * w * (header->bpp >> 3));
            for (int x = 0; x < w; x++) {
                data[i++] = ((header->bpp == 32 ? ptr[j + 3] : 0) << 24) | (ptr[j + 2] << 16) | (ptr[j + 1] << 8) | ptr[j];
                j += ptr[16] >> 3;
            }
        }
        break;

    default:
        kprintf("unsupported TGA %d\n", ptr[2]);
        free(data); return NULL;
    }

    kprintf("ret 0x%X\n", data);
	*widthOut = w;
    *heightOut = h;
    return data;
}

void Video::putTGA(int baseX, int baseY, uint8_t* tgaData, int tgaLen)
{
	int tgaWidth;
	int tgaHeight;
	uint32_t* parsed = tgaParse(tgaData, tgaLen, &tgaWidth, &tgaHeight);

    if (!parsed) {
        return;
    }

	for (int y = baseY; y < baseY + tgaHeight; ++y) {
		for (int x = baseX; x < baseX + tgaWidth; ++x) {
			putpixel(x, y, *parsed++);
		}
	}
}