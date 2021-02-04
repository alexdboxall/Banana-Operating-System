#include "core/main.hpp"
#include "hal/sound/sndhw.hpp"
#include "core/common.hpp"
#include "core/kheap.hpp"
extern "C" {
#include "libk/string.h"
#include "libk/math.h"
}
//#pragma GCC optimize ("Os")

SoundDevice::SoundDevice(const char* name) : Device(name)
{
	deviceType = DeviceType::Audio;
	numChannels = 0;

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		channels[i] = nullptr;
	}
}

SoundDevice::~SoundDevice()
{
	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] != nullptr) {
			delete channels[i];
		}
	}
}

int SoundDevice::getFreeChannelNum()
{
	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] == nullptr) {
			return i;
		}
	}

	return -1;
}

int SoundDevice::addChannel(SoundChannel* ch)
{
	int chNum = getFreeChannelNum();

	if (chNum == -1 || ch == nullptr) return -1;

	channels[chNum] = ch;

	if (numChannels == 0) {
		currentSampleRate = ch->getSampleRate();
		currentBits = ch->getBits();
		beginPlayback(currentSampleRate, currentBits);
	}

	++numChannels;

	return true;
}

void SoundDevice::removeChannel(int id)
{
	if (id >= 0 && id < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS && channels[id] != nullptr) {
		channels[id] = nullptr;
		--numChannels;

		if (numChannels == 0) {
			stopPlayback();
		}
	}
}

void SoundDevice::floatTo8(float* in, uint8_t* out, int len)
{
	for (int i = 0; i < len; ++i) {
		float scaledValue = (((float) in[i]) + 1.0) / 2.0 * 128.0;
		if (scaledValue >= 127.0) {
			out[i] = 127;
		} else if (scaledValue <= 0.0) {
			out[i] = 0;
		} else {
			out[i] = (short) lrintf(scaledValue);
		}
	}
}

int SoundDevice::getAudio(int samples, float* tempBuffer, float* outputBuffer)
{
	int minSamplesGot = samples;

	memset(outputBuffer, 0, sizeof(float) * samples);

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] != nullptr && !channels[i]->paused() && channels[i]->getVolume()) {
			float vol = ((float) channels[i]->getVolume()) / 100.0;

			int samplesGot = channels[i]->unbuffer(tempBuffer, currentSampleRate, samples);

			for (int j = 0; j < samplesGot; ++j) {
				outputBuffer[j] += (tempBuffer[j] * vol) / ((float) numChannels);
			}

			if (samplesGot < minSamplesGot) {
				minSamplesGot = samplesGot;
			}
		}
	}

	return minSamplesGot;
}
