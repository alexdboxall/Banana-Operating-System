
#ifndef _VGAVGAVideo_HPP_
#define _VGAVGAVideo_HPP_

#include <stdint.h>
#include "hal/video.hpp"


class VGAVideo : public Video
{
private:

protected:

public:
	VGAVideo();

	void setPlane(int pl);

	int open(int, int, void*);
	int close(int, int, void*);

	/*
	virtual void putpixel(int x, int y, uint32_t colour) override;*/
};


#endif
