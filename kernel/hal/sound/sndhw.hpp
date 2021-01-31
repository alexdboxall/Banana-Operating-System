#ifndef _SOUNDHW_HPP_
#define _SOUNDHW_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

#include "hal/sound/sndchannel.hpp"

#define SOUND_DEVICE_MAX_VIRTUAL_CHANNELS 32

class SoundDevice : public Device
{
private:

protected:
	int numChannels;
	SoundChannel* channels[SOUND_DEVICE_MAX_VIRTUAL_CHANNELS];

	int getFreeChannelNum();

	int currentSampleRate;
	int currentBits;

public:
	SoundDevice(const char* name);
	virtual ~SoundDevice();
	
	int addChannel(SoundChannel* ch);
	void removeChannel(int id);

	int getAudio(int samples, float* tempBuffer, float* outputBuffer);

	void floatTo8(float* in, uint8_t* out, int len);

	virtual int getNumHwChannels() = 0;
	virtual void beginPlayback(int sampleRate, int bits) = 0;
	virtual void stopPlayback() = 0;
};

#endif