
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

	static inline void setPlane(int pl)
	{
		outb(0x3CE, 4);
		outb(0x3CF, pl & 3);

		outb(0x3C4, 2);
		outb(0x3C5, 1 << (pl & 3));
	}

	int open(int, int, void*);
	int close(int, int, void*);

	virtual void putpixel(int x, int y, uint32_t colour) override;
	virtual void putrect(int x, int y, int w, int h, uint32_t colour) override;
};


#endif
