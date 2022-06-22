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
	uint32_t cursorBuffer[32 * 32];

public:
	Video(const char* name);
	virtual ~Video();

	int getWidth();
	int getHeight();
	bool isMonochrome();

	uint32_t* tgaParse(uint8_t* ptr, int size, int* widthOut, int* heightOut);

	virtual void putpixel(int x, int y, uint32_t colour);
	virtual void putrect(int x, int y, int w, int h, uint32_t colour);
	virtual void putTGA(int x, int y, uint8_t* tgaData, int tgaLen);
	virtual void drawCursor(int x, int y, uint32_t* data, int invertMouse);
	virtual uint32_t* savePixelsInSquare(int x, int y);

	virtual uint32_t readPixelApprox(int x, int y);
	virtual void bitblit(int sx, int sy, int x, int y, int w, int h, int pitch, uint32_t* data);

	virtual void blit(uint32_t* buffer, int x, int y, int width, int height);
	virtual void clearScreen(uint32_t colour);
};


#endif