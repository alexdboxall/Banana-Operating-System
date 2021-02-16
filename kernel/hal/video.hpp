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
	bool mono;

public:
	Video(const char* name);
	virtual ~Video();

	int getWidth();
	int getHeight();
	bool isMonochrome();

	virtual void putpixel(int x, int y, uint32_t colour);
	virtual void putrect(int x, int y, int w, int h, uint32_t colour);
	virtual void drawCursor(int x, int y, uint8_t* data, int invertMouse);

	virtual void blit(uint32_t* buffer, int x, int y, int width, int height);
	virtual void clearScreen(uint32_t colour);
};


#endif