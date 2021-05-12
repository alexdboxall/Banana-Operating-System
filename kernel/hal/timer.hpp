#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class Timer : public Device
{
private:

protected:
	int frequency;

public:
	Timer(const char* name);
	virtual ~Timer();

	int read();
	virtual void write(int hz) = 0;
};

Timer* setupTimer(int hz);
void timerHandler(uint32_t milliTenths);

extern uint32_t milliTenthsSinceBoot;

#endif