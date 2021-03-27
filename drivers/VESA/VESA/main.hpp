
#ifndef _VESAVideo_HPP_
#define _VESAVideo_HPP_

#include <stdint.h>
#include "hal/video.hpp"
#include "hw/ports.hpp"

#define RATIO_UNKNOWN	0
#define RATIO_43		1
#define RATIO_169		2
#define RATIO_1610		3

struct ModeInfo
{
	//VM8086 gives us this
	uint16_t width;
	uint16_t height;
	uint16_t pitch;
	uint8_t bpp;
	uint8_t reserved;
	uint32_t lfb;

	//we add this
	uint16_t number;
	uint8_t ratioEstimation;
};

class VESA: public Video
{
private:

protected:

public:
	VESA();

	uint8_t* vramPhys;
	uint8_t* vram;

	int pitch;
	int bpp;

	bool gotModes = false;
	void getModes();
	ModeInfo getModeStruct(int mode);
	ModeInfo calculateBestMode();
	void setMode(int mode);

	int open(int, int, void*);
	int close(int, int, void*);

	virtual void putpixel(int x, int y, uint32_t colour) override;
};


#endif
