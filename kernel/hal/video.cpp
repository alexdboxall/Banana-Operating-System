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
	KePanic("Video::pixel MUST BE OVERRIDDEN\n");
}

uint32_t Video::readPixelApprox(int x, int y)
{
	KePanic("Video::readPixelApprox MUST BE OVERRIDDEN\n");
	return 0;
}

void Video::drawCursor(int mouse_x, int mouse_y, uint32_t* data, int invertMouse)
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

	int ox = x;

	for (; y < maxY; ++y) {
		for (x = ox; x < maxX; ++x) {
			putpixel(x, y, colour);
		}
	}
}

//THIS IS PROBABLY THE MOST CRUCIAL FUNCTION TO GET RIGHT WHEN YOU ARE WRITING A VIDEO DRIVER
//all images pass through this!
//SO PLEASE OVERRIDE IT!!!
//any video driver writer that doesn't implement this should not be writing drivers
void Video::bitblit(int sx, int sy, int x, int y, int w, int h, int pitch, uint32_t* data)
{
	for (int yyy = 0; yyy < h; ++yyy) {
		int tempx = sx;
		uint32_t* database = data + ((y + yyy) * pitch + x);
		for (int xxx = 0; xxx < w; ++xxx) {
			putpixel(tempx++, sy, *database++);
		}
		++sy;
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
	uint8_t magic1;
	uint8_t colormap;
	uint8_t encoding;
	uint16_t cmaporig;	
	uint16_t cmaplen;
	uint8_t cmapent;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h; 
	uint8_t bpp;
	uint8_t pixeltype; 
} __attribute__((packed)) tga_header_t;

uint32_t* Video::tgaParse(uint8_t* ptr, int size, int* widthOut, int* heightOut)
{
	int w = (ptr[13] << 8) + ptr[12];
	int h = (ptr[15] << 8) + ptr[14];

    uint32_t* data = (uint32_t*) malloc((w * h + 2) * sizeof(uint32_t));
	tga_header_t* header = (tga_header_t*) ptr;

	if (!data) {
		KePanic("tgaParse malloc");
	}

	int j, k;
	int o = header->y;
    int imageDataOffset = ((header->colormap ? (header->cmapent >> 3) * header->cmaplen : 0) + 18);

    if (w < 1 || h < 1) {
        kprintf("width or height < 1\n");
        return NULL;
    }

	switch (ptr[2]) {
	case 2:
	{
		if (header->cmaplen != 0 || header->colormap != 0 || (header->bpp != 24 && header->bpp != 32)) {
			kprintf("case 2 null.\n");
			free(data);
			return NULL;
		}
		j = imageDataOffset;
		int i = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				data[i++] = ((header->bpp == 32 ? ptr[j + 3] : 0) << 24) | (ptr[j + 2] << 16) | (ptr[j + 1] << 8) | ptr[j];
				j += header->bpp >> 3;
			}
		}
		break;
	}
	case 10:
	{
		if (header->cmaplen != 0 || header->colormap != 0 || (header->bpp != 24 && header->bpp != 32)) {
			kprintf("case 10 null.\n");
			free(data);
			return NULL;
		}
		int m = imageDataOffset;
		int i = 0;
		int y = 0;
		for (int x = 0; x < w * h && m < size;) {
			int k = ptr[m++];		//packet header

			if (k >= 128) {
				//RLE packet
				int numRepeats = k & 0x7F;
				uint32_t val = ((header->bpp == 32 ? ptr[m + 3] : 0) << 24) | (ptr[m + 2] << 16) | (ptr[m + 1] << 8) | ptr[m];
				for (int z = 0; z < numRepeats; ++z) {
					data[i++] = val;
				}
				m += header->bpp >> 3;

			} else {
				//raw packet

				int numPixels = k;
				for (int z = 0; z < numPixels; ++z) {
					data[i++] = ((header->bpp == 32 ? ptr[m + 3] : 0) << 24) | (ptr[m + 2] << 16) | (ptr[m + 1] << 8) | ptr[m];
					m += header->bpp >> 3;
				}
			}
		}
		break;
	}

    default:
        kprintf("unsupported TGA %d\n", ptr[2]);
        free(data); return NULL;
    }

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