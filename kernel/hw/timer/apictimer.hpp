
#ifndef _APIC_TIMER_HPP_
#define _APIC_TIMER_HPP_

#include <stdint.h>
#include "hal/timer.hpp"

class APICTimer: public Timer
{
private:

protected:
	int irqNum;

public:
	APICTimer();

	int open(int, int, void*);
	int close(int, int, void*);	

	void write(int hz);
};

#endif