#include "hal/sound/sndchannel.hpp"
#include "core/common.hpp"
#include "core/kheap.hpp"
#include "hal/device.hpp"
#include "thr/prcssthr.hpp"
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

extern "C" {
	#include "libk/string.h"
	#include "libk/math.h"
}

bool gotLookupTable = false;
float lookupTable8[256];

SoundChannel::SoundChannel(int _sampleRate, int _bits, int _direction, int _buffSize)
{
	sampleRate = _sampleRate;
	bits = _bits;
	direction = _direction;

	if (_buffSize == -1) {
		_buffSize = sampleRate * bits / 4 + 4000;
	}

	buffSize = _buffSize;

	buffStart = 0;
	buffUsed = 0;
	buff = (float*) malloc(buffSize * sizeof(float));

	int error;
	conv = src_new(SRC_LINEAR, 1, &error);
	if (error) {
		panic("TODO: SOUND CHANNEL ERROR");
	}

	//the reason we do this is so that 386s without FPUs can
	//still play audio using the soft floating point library
	//(which is slow as hell)

	if (!gotLookupTable) {
		const float f = 1.0 / (1.0 * 0x80);

		for (int i = 0; i < 256; ++i) {
			lookupTable8[i] = ((float) i) * f;
		}
		gotLookupTable = true;
	}
}

SoundChannel::~SoundChannel()
{
	free(buff);
}

int SoundChannel::getSampleRate()
{
	return sampleRate;
}

int SoundChannel::getBits()
{
	return bits;
}

int SoundChannel::getBufferUsed()
{
	return buffUsed;
}

int SoundChannel::getBufferSize()
{
	return buffSize;
}

int SoundChannel::unbuffer(float* output, int outSampleRate, int maxOut)
{
	SRC_DATA data;
	kprintf("A.\n");

	data.data_in = buff;
	data.input_frames = buffUsed;
	data.output_frames = maxOut;
	data.data_out = output;
	data.src_ratio = ((float) outSampleRate) / ((float) sampleRate) / speed;
	data.end_of_input = 0;

	kprintf("B.\n");

	src_process(conv, &data);
	kprintf("C.\n");

	buffUsed -= data.input_frames_used;
	kprintf("D.\n");
	kprintf("buff size = %d, input frames used %d, buff = 0x%X\n", buffSize, data.input_frames_used, buff);
	kprintf("dest = 0x%X, src = 0x%X, size = 0x%X\n", buff, buff + data.input_frames_used, (buffSize - data.input_frames_used) * sizeof(float));
	memmove(buff, buff + data.input_frames_used, (buffSize - data.input_frames_used) * sizeof(float));
	kprintf("E.\n");
	return data.output_frames_gen;
}

int SoundChannel::buffer16(int16_t* data, int samples)
{
	int done = 0;

	if (buffUsed == buffSize) {
		return 0;
	}

	const float f = 1.0 / (1.0 * 0x8000);

	int i = 0;
	for (; i < samples; ++i) {
		buff[buffUsed++] = ((float) data[i]) * f;

		++done;

		if (buffUsed == buffSize) {
			//buffer full
			return i + 1;
		}
	}

	return i;
}

int SoundChannel::buffer8(uint8_t* data, int len)
{
	int done = 0;

	if (buffUsed == buffSize) {
		return 0;
	}

	int i = 0;
	for (; i < len; ++i) {
		buff[buffUsed++] = lookupTable8[data[i]];
		
		++done;

		if (buffUsed == buffSize) {
			//buffer full
			return i + 1;
		}
	}
	
	return i;
}

