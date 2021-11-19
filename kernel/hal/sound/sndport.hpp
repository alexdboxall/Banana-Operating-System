#ifndef SNDPORT_HPP
#define SNDPORT_HPP

#include <stdint.h>

class SoundCard;

class SoundPort
{
private:

protected:
	friend class SoundCard;

	int sampleRate;
	int bits;
	int channels;

	int32_t* buff = nullptr;
	int buffSize;
	int buffUsed;

	bool paused = true;

public:
	SoundPort(int sampleRate, int bits, int channels, int bufferSize = -1);
	~SoundPort();

	void unpause();
	void pause();

	int buffer16(int16_t* data, int samples);
	int buffer32(int32_t* data, int samples);

	int getBufferUsed();
	int getBufferSize();

	int unbufferAndAdd16(int max, int16_t* buffer, SoundCard* card);
	int unbufferAndAdd32(int max, int32_t* buffer, SoundCard* card);

};

#endif