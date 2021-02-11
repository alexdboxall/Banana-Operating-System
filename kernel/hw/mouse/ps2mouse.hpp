
#ifndef _PS2MOUSE_HPP_
#define _PS2MOUSE_HPP_

#include <stdint.h>
#include "hal/mouse.hpp"

class PS2Mouse: public Mouse
{
private:

protected:
	PS2* controller;
	PS2Port* port;

	uint8_t mouseMode;					//0 = normal, 3 = with scrollwheel, 4 = with scrollwheel + 4th and 5th button
	unsigned char cycle = 0;
	uint8_t mouse_bytes[4] = { 0 };

public:
	void handler();

	PS2Mouse();

	int open(int, int, void*);
	int close(int, int, void*);
};

#endif