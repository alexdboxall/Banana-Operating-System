
#ifndef _VGAVGAVideo_HPP_
#define _VGAVGAVideo_HPP_

#include <stdint.h>
#include "hal/video.hpp"
#include "hw/ports.hpp"

class VGAVideo: public Video
{
private:

protected:

public:
	VGAVideo();

	bool mono;

	void setPlane(int pl);

	int open(int, int, void*);
	int close(int, int, void*);

	virtual void bitblit(int sx, int sy, int x, int y, int w, int h, int pitch, uint32_t* data);
	virtual void putpixel(int x, int y, uint32_t colour) override;
	virtual void putrect(int x, int y, int w, int h, uint32_t colour) override;
};


#endif
