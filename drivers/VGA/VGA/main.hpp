
#ifndef _VGAVGAVideo_HPP_
#define _VGAVGAVideo_HPP_

#include <stdint.h>
#include "hal/video.hpp"
#include "krnl/hal.hpp"

class VGAVideo: public Video
{
private:

protected:

public:
	VGAVideo();

	bool mono;

	size_t vramBase = 0xA0000;
	int biosMode = 0x12;

	void setPlane(int pl);

	int open(int, int, void*);
	int close(int, int, void*);

	virtual void blit(uint32_t* buffer, int x, int y, int _width, int _height);
	virtual uint32_t readPixelApprox(int x, int y) override;
	virtual void bitblit(int sx, int sy, int x, int y, int w, int h, int pitch, uint32_t* data);
	virtual void putpixel(int x, int y, uint32_t colour) override;
	virtual void putrect(int x, int y, int w, int h, uint32_t colour) override;
};


#endif
