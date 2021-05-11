#ifndef _SOUNDCARD_HPP_
#define _SOUNDCARD_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hal/sound/sndport.hpp"

#define SOUND_DEVICE_MAX_VIRTUAL_CHANNELS 32

class SoundCard : public Device
{
private:

protected:
	SoundPort* channels[SOUND_DEVICE_MAX_VIRTUAL_CHANNELS];
	bool playing = false;

public:
	SoundCard(const char* name);
	virtual ~SoundCard();

	int getSamples16(int max, int16_t* buffer);
	int getSamples32(int max, int32_t* buffer);
	
	int addChannel(SoundPort* ch);
	void removeChannel(int id);

	virtual void beginPlayback(int sampleRate, int bits);
	virtual void stopPlayback();
};

#endif