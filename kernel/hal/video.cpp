/*
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
//any video driver writer that doesn't implement this should be ashamed of themselves
void Video::clearScreen(uint32_t colour)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			putpixel(x, y, colour);
		}
	}
}
*/