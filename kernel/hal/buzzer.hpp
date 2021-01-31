#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "hal/device.hpp"

class Buzzer : public Device
{
private:

protected:

public:
	int timeToSleepInThread = 0;

	Buzzer(const char* name);
	virtual ~Buzzer();

	void beep(int hertz, int millisecs, bool blocking = true);
	void stop();

	virtual void start(int hertz) = 0;
};

extern Buzzer* systemBuzzer;

#endif