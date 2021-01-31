
#ifndef _ISA_HPP_
#define _ISA_HPP_

#include <stdint.h>
#include "hal/bus.hpp"

class DMA;
extern DMA* isaDMAController;

class ISA: public Bus
{
private:

protected:

public:
	ISA();

	int open(int, int, void*);
	int close(int, int, void*);

	void detect();

	void doSpeaker();
	void doSoundblaster();
	void doSerial();
	void doParallel();
	void doGameport();
	void doFloppy();
	void doATA();
	void doPS2();
	void doRTC();
};

#endif