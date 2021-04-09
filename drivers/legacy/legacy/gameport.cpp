
#include <stdint.h>
#include <stddef.h>

#include "gameport.hpp"

#include "core/main.hpp"
#include "hw/ports.hpp"
#include "core/physmgr.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define JOYSTICK_PORT			0x201
#define GARBAGE_DATA			0xFF
#define MAX_TIME_ATTEMPTS		1000

#define JOYSTICK_A_AXIS_X		0x01
#define JOYSTICK_A_AXIS_Y		0x02
#define JOYSTICK_A_BUTTON_1		0x10
#define JOYSTICK_A_BUTTON_2		0x20

#define JOYSTICK_B_AXIS_X		0x04
#define JOYSTICK_B_AXIS_Y		0x08
#define JOYSTICK_B_BUTTON_1		0x40
#define JOYSTICK_B_BUTTON_2		0x80

Gameport::Gameport(): Device("Gameport")
{
	gotJoystick1 = false;
	gotJoystick2 = false;

	ports[noPorts].rangeStart = 0x201;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
}

Gameport::~Gameport()
{

}

void Gameport::calibration(int id)
{
	if (overrideCalibration) {
		needsCalibration = true;
		return;
	}

	readRaw(id);
	nanoSleep(1000 * 1000);
	JoystickData j1 = readRaw(id);
	nanoSleep(1000 * 1000);
	JoystickData j2 = readRaw(id);
	nanoSleep(1000 * 1000);
	JoystickData j3 = readRaw(id);
	nanoSleep(1000 * 1000);
	readRaw(id);

	int meanX = (j1.internalData[0] + j2.internalData[0] + j3.internalData[0]) / 3;
	int meanY = (j1.internalData[1] + j2.internalData[1] + j3.internalData[1]) / 3;
	
	if (id == 0) {
		joy1AvgCalibX = meanX;
		joy1AvgCalibY = meanY;

	} else {
		joy2AvgCalibX = meanX;
		joy2AvgCalibY = meanY;
	}

	joy1MaxCalibX = joy1AvgCalibX * 3;
	joy1MaxCalibY = joy1AvgCalibY * 3;
	joy2MaxCalibX = joy2AvgCalibX * 3;
	joy2MaxCalibY = joy2AvgCalibY * 3;
}


void Gameport::detect()
{
	JoystickData j1 = readRaw(0);
	JoystickData j2 = readRaw(1);

	if (!gotJoystick1 && j1.hasJoystick) {
		//add a joystick device

		calibration(0);

	} else if (gotJoystick1 && !j1.hasJoystick) {
		//remove a joystick device

	}

	if (!gotJoystick2 && j2.hasJoystick) {
		//add a joystick device

		calibration(1);

	} else if (gotJoystick2 && !j2.hasJoystick) {
		//remove a joystick device

	}

	gotJoystick1 = j1.hasJoystick;
	gotJoystick2 = j2.hasJoystick;
}

JoystickData Gameport::read(int id)
{
	if ((id == 0 && !gotJoystick1) || (id == 1 && !gotJoystick2)) {
		JoystickData j;
		j.hasJoystick = false;
		return j;
	}

	JoystickData joy;
	joy = readRaw(id);

	int cx = id == 1 ? joy2AvgCalibX : joy1AvgCalibX;
	int cy = id == 1 ? joy2AvgCalibY : joy1AvgCalibY;
	int mx = id == 1 ? joy2MaxCalibX : joy1MaxCalibX;
	int my = id == 1 ? joy2MaxCalibY : joy1MaxCalibY;
	int dx = joy.internalData[0];
	int dy = joy.internalData[1];

	//stop division by zero (which would only happen if the joystick was broken)
	if (!cx || !cy || mx == cx || my == cy) {
		JoystickData j;
		j.hasJoystick = false;
		return j;
	}

	if (dx > cx) {
		joy.deltaX = ((dx - cx) * 127) / (mx - cx);
		joy.deltaY = ((dx - cy) * 127) / (my - cy);
	} else {
		joy.deltaX = ((dx - cy) * 127) / cx;
		joy.deltaY = ((dx - cy) * 127) / cy;
	}

	return joy;
}

JoystickData Gameport::readRaw(int id)
{
	JoystickData joy;
	joy.hasJoystick = true;
	joy.buttonCount = 2;

	uint8_t stat = inb(JOYSTICK_PORT);
	if (id == 0) {
		joy.buttons[0] = stat & JOYSTICK_A_BUTTON_1;
		joy.buttons[1] = stat & JOYSTICK_A_BUTTON_2;
	} else {
		joy.buttons[0] = stat & JOYSTICK_B_BUTTON_1;
		joy.buttons[1] = stat & JOYSTICK_B_BUTTON_2;
	}
	
	outb(JOYSTICK_PORT, GARBAGE_DATA);
	lockScheduler();
	int xCount = 0;
	int yCount = 0;
	bool xDone = false;
	bool yDone = false;
	int count = 0;

	int bitX = id == 1 ? JOYSTICK_B_AXIS_X : JOYSTICK_A_AXIS_X;
	int bitY = id == 1 ? JOYSTICK_B_AXIS_Y : JOYSTICK_A_AXIS_Y;

	while (1) {
		stat = inb(JOYSTICK_PORT);
		if ((stat & bitX) && !xDone) {
			xCount++;
		} else {
			xDone = true;
		}

		if ((stat & bitY) && !yDone) {
			yCount++;
		} else {
			yDone = true;
		}

		count++;
		if (count == 0xFFFF || (xDone && yDone)) {
			break;
		}
	}
	unlockScheduler();

	if (xCount == 0xFFFF || yCount == 0xFFFF) {
		joy.hasJoystick = false;
	}

	joy.internalData[0] = xCount;
	joy.internalData[1] = yCount;
	return joy;
}

int Gameport::open(int a, int b, void* c)
{
	return 0;
}

int Gameport::close(int a, int b, void* c)
{
	return 0;
}