
#ifndef _GAMEPORTHPP_
#define _GAMEPORTHPP_

#include <stdint.h>

#include "krnl/main.hpp"
#include "krnl/physmgr.hpp"
#include "krnl/common.hpp"
#include "krnl/kheap.hpp"
#include "krnl/terminal.hpp"
#include "hal/intctrl.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "hal/sound/sndhw.hpp"
#include "fs/vfs.hpp"

extern "C" {
#include "libk/string.h"
#include "libk/math.h"
}

struct JoystickData
{
	uint16_t buttonCount : 4;
	uint16_t hasJoystick : 1;
	bool buttons[16];

	int8_t deltaX;		// -127 to 127 (don't use -128)
	int8_t deltaY;		// -127 to 127 (don't use -128)

	uint32_t internalData[8];
};

class JoystickHost
{
	virtual JoystickData read(int id) = 0;
};

class Gameport : public Device, public JoystickHost
{
private:

protected:

public:
	Gameport();
	~Gameport();

	int joy1AvgCalibX = 330;
	int joy1AvgCalibY = 330;
	int joy2AvgCalibX = 330;
	int joy2AvgCalibY = 330;

	int joy1MaxCalibX = 980;
	int joy1MaxCalibY = 980;
	int joy2MaxCalibX = 980;
	int joy2MaxCalibY = 980;

	bool gotJoystick1 = false;
	bool gotJoystick2 = false;

	JoystickData read(int id);

	void calibration(int id);
	bool overrideCalibration = false;
	bool needsCalibration = false;

	JoystickData readRaw(int id);

	virtual void detect() override;
	virtual int open(int, int, void*);
	virtual int close(int, int, void*);	
};


#endif
