
#ifndef _PIT_HPP_
#define _PIT_HPP_

#include <stdint.h>
#include "hal/timer.hpp"

class PIT: public Timer
{
private:

protected:

public:
	PIT();

	void write(int hz);

	int open(int, int, void*);
	int close(int, int, void*);
};

#endif