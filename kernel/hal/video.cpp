#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/video.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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
	putpixel(mouse_x, mouse_y, 0);
	return;

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
