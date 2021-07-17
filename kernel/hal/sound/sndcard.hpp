#ifndef _SOUNDCARD_HPP_
#define _SOUNDCARD_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hal/sound/sndport.hpp"

#define SOUND_DEVICE_MAX_VIRTUAL_CHANNELS 32

class SoundPort;

class SoundCard : public Device
{
private:

protected:
	friend class SoundPort;

	SoundPort* channels[SOUND_DEVICE_MAX_VIRTUAL_CHANNELS];
	bool playing = false;

	int currentBits = 0;
	int currentSampleRate = 0;
	int currentChannels = 0;

public:
	bool configureRates(int sampleRate, int bits, int channels);

	SoundCard(const char* name);
	virtual ~SoundCard();

	int getSamples16(int max, int16_t* buffer);
	int getSamples32(int max, int32_t* buffer);
	
	int addChannel(SoundPort* ch);
	void removeChannel(int id);

	virtual void beginPlayback();
	virtual void stopPlayback();
};

#endif