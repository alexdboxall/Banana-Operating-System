
#if 0

#ifndef _SB16HPP_
#define _SB16HPP_

#include <stdint.h>

#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "core/common.hpp"
#include "core/kheap.hpp"
#include "core/terminal.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/sound/sndhw.hpp"
#include "fs/vfs.hpp"

extern "C" {
#include "libk/string.h"
#include "libk/math.h"
}

class SoundBlaster16: public SoundDevice
{
private:

protected:

public:
	DMAChannel* dmaChannel;

	int hertz = 8000;
	int bits = 8;
	bool stereo = true;
	bool sign = false;

	bool justPressedPlay = false;

	uint32_t dmaAddr;

	SoundBlaster16();

	void handleIRQ();

	uint8_t dspVersion = 0;

	virtual int getNumHwChannels();
	virtual void beginPlayback(int sampleRate, int bits);
	virtual void stopPlayback();

	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands

	void onInterrupt();

	void DSPOut(uint16_t port, uint8_t val);
	void resetDSP();
	void turnSpeakerOn(bool on = true);
};


#endif



#endif
