#ifndef _AC97_HPP_
#define _AC97_HPP_

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

class AC97: public SoundDevice
{
private:

protected:
	size_t nam;
	size_t nabm;

public:
	AC97();
	virtual ~AC97();

	void handleIRQ();
	void setVolume(int leftPercent, int rightPercent);

	int open(int a, int b, void* c);
	int _open(int a, int b, void* c);
	int close(int a, int b, void* c);

	virtual void beginPlayback(int sampleRate, int bits) override;
	virtual int getNumHwChannels() override;
	virtual void stopPlayback() override;
};

#endif