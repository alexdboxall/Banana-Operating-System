#ifndef SNDCHANNEL_HPP
#define SNDCHANNEL_HPP

#include "hal/libresample/samplerate.h"
#include <stdint.h>

class SoundChannel
{
private:

protected:
	int sampleRate;
	int bits;
	int direction;

	SRC_STATE* conv;

	float* buff;
	int buffSize;

	int buffStart;
	int buffUsed;


	bool isPaused;
	int volume;
	float speed;

public:
	SoundChannel(int sampleRate, int bits, int direction, int bufferSize = -1);
	~SoundChannel();

	int unbuffer(float* output, int sampleRate, int maxOut);

	int buffer8(uint8_t* data, int len);
	int buffer16(int16_t* data, int samples);

	int getBufferUsed();
	int getBufferSize();

	int getSampleRate();
	int getBits();
};

#endif