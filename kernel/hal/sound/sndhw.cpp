#include "core/main.hpp"
#include "hal/sound/sndhw.hpp"
#include "core/common.hpp"
#include "core/kheap.hpp"
extern "C" {
#include "libk/string.h"
#include "libk/math.h"
}
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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

void SoundDevice::floatTo16(float* in, uint16_t* out, int len)
{
	for (int i = 0; i < len; ++i) {
		float scaledValue = (((float) in[i]) + 1.0) / 2.0 * 32767.0;
		if (scaledValue >= 32767.0) {
			out[i] = 32767;
		} else if (scaledValue <= 0.0) {
			out[i] = 0;
		} else {
			out[i] = (short) lrintf(scaledValue);
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
	kprintf("SoundDevice::getAudio\n");

	int minSamplesGot = samples;

	kprintf("A.\n");
	kprintf("The output buffer is at 0x%X\n", outputBuffer);
	kprintf("0x%X samples makes 0x%X bytes.\n", samples, sizeof(float) * samples);
	memset(outputBuffer, 0, sizeof(float) * samples);
	kprintf("B.\n");

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		kprintf("C.\n");
		if (channels[i] != nullptr && !channels[i]->paused() && channels[i]->getVolume()) {
			kprintf("D.\n");
			float vol = ((float) channels[i]->getVolume()) / 100.0;
			kprintf("E.\n");

			int samplesGot = channels[i]->unbuffer(tempBuffer, currentSampleRate, samples);
			kprintf("F.\n");

			for (int j = 0; j < samplesGot; ++j) {
				kprintf("G.\n");
				outputBuffer[j] += (tempBuffer[j] * vol) / ((float) numChannels);
				kprintf("H.\n");
			}
			kprintf("I.\n");

			if (samplesGot < minSamplesGot) {
				kprintf("J.\n");
				minSamplesGot = samplesGot;
			}

			kprintf("K.\n");
		}

		kprintf("L.\n");
	}

	kprintf("M.\n");

	return minSamplesGot;
}
