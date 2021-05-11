#include "core/main.hpp"
#include "hal/sound/sndcard.hpp"
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


SoundCard::SoundCard(const char* name) : Device(name)
{
	deviceType = DeviceType::Audio;

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		channels[i] = nullptr;
	}

	playing = false;
}

SoundCard::~SoundCard()
{
	
}

bool SoundCard::configureRates(int sampleRate, int bits, int channels)
{
	if (!playing) {
		currentSampleRate = sampleRate;
		currentBits = bits;
		currentChannels = channels;
		return true;

	} else {
		return false;
	}
}

int SoundCard::getSamples16(int max, int16_t* buffer)
{
	int maxGot = 0;
	memset(buffer, 0, max * sizeof(int32_t));

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] != nullptr && !channels[i]->paused) {
			int got = channels[i]->unbufferAndAdd16(max, buffer, this);
			if (got > maxGot) {
				maxGot = got;
			}
		}
	}

	if (maxGot == 0 && playing) {
		stopPlayback();

	} else if (maxGot && !playing) {
		beginPlayback();
	}

	return maxGot;
}

int SoundCard::getSamples32(int max, int32_t* buffer)
{
	int maxGot = 0;
	memset(buffer, 0, max * sizeof(int32_t));

	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] != nullptr && !channels[i]->paused) {
			int got = channels[i]->unbufferAndAdd32(max, buffer, this);
			if (got > maxGot) {
				maxGot = got;
			}
		}
	}

	if (maxGot == 0 && playing) {
		stopPlayback();

	} else if (maxGot && !playing) {
		beginPlayback();
	}

	return maxGot;
}

int SoundCard::addChannel(SoundPort* ch)
{
	int id = -1;
	int numChs = 0;
	for (int i = 0; i < SOUND_DEVICE_MAX_VIRTUAL_CHANNELS; ++i) {
		if (channels[i] == nullptr) {
			id = i;
		} else {
			++numChs;
		}
	}

	if (id == -1) {
		kprintf("Could not add channel!\n");
		return -1;
	}

	channels[id] = ch;
	if (numChs == 0) {

	}
	return id;
}

void SoundCard::removeChannel(int id)
{
	channels[id] = nullptr;
}

void SoundCard::beginPlayback()
{
	panic("PSEDUO-PURE VIRTUAL SoundCard::beginPlayback CALLED");
}

void SoundCard::stopPlayback()
{
	panic("PSEDUO-PURE VIRTUAL SoundCard::stopPlayback CALLED");
}
