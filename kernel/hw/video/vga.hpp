
#ifndef _VGA_HPP_
#define _VGA_HPP_

#include <stdint.h>
#include "hal/video.hpp"

class VGA: public Video
{
private:

protected:

public:
	VGA();

	void setPlane(int pl);

	int open(int, int, void*);
	int close(int, int, void*);

	void putpixel(int x, int y, uint32_t colour);
};

#endif