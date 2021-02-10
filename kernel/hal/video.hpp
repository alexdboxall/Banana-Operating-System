#ifndef _VIDEO_HPP_
#define _VIDEO_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class Video : public Device
{
private:

protected:
	int width;
	int height;

public:
	Video(const char* name);
	virtual ~Video();

	int getWidth();
	int getHeight();

	virtual void putpixel(int x, int y, uint32_t colour) = 0;

	virtual void blit(uint32_t* buffer, int x, int y, int width, int height);
	virtual void clearScreen(uint32_t colour);
};

#endif