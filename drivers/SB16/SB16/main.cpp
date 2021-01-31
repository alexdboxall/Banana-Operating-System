#include <stdint.h>

#include "main.hpp"

void start(void* p)
{
	while (1);

	Device* parent = (Device*) p;

	SoundBlaster16* dev = new SoundBlaster16();
	parent->addChild(dev);
	dev->open(0, 0, nullptr);

	extern void sb16Demo();
	sb16Demo();
}


#define DSP_BASE		0x220
#define DSP_MIXER		0x224
#define DSP_MIXER_DATA	0x225
#define DSP_RESET		0x226
#define DSP_READ		0x22A
#define DSP_WRITE		0x22C
#define DSP_READSTATUS	0x22E
#define DSP_ACKINT8		0x22E
#define DSP_ACKINT16	0x22F

#define WRITE_SET_TIME_CONSTANT		0x40
#define WRITE_SET_SAMPLE_RATE		0x41
#define WRITE_SPEAKER_ON			0xD1
#define WRITE_SPEAKER_OFF			0xD3
#define WRITE_STOP_CHANNEL_8		0xD0
#define WRITE_STOP_CHANNEL_16		0xD5
#define WRITE_GET_DSP_VERSION		0xE1

#define WRITE_PLAY_SOUND_8			0xC0
#define WRITE_PLAY_SOUND_16			0xB0

#define MIXER_MASTER_VOLUME			0x22
#define MIXER_SET_IRQ				0x80

#define IRQ_2			0x01
#define IRQ_5			0x02
#define IRQ_7			0x04
#define IRQ_10			0x08

#include "core/prcssthr.hpp"
#include "core/physmgr.hpp"
#include "hw/ports.hpp"
#include "fs/vfs.hpp"

uint8_t buf[4096];
uint8_t buf2[4096];

char fp1[] = "C:/francis.wav";

void sb16Demo(void* s)
{
	unlockScheduler();

	SoundBlaster16* dev = new SoundBlaster16();
	computer->addChild(dev);
	dev->open(0, 0, nullptr);

	SoundChannel* c = new SoundChannel(8000, 8, 90);
	SoundChannel* c2 = new SoundChannel(8000, 8, 270);

	File* f = new File(fp1, kernelProcess);
	f->open(FileOpenMode::Read);

	bool playedYet = false;

	while (1) {
		int bytesRead = 0;
		FileStatus st = f->read(4096, buf, &bytesRead);
		if (bytesRead == 0 || st != FileStatus::Success) {
			return;
		}

		lockScheduler();
		schedule();
		unlockScheduler();

		while (c->getBufferUsed() + bytesRead >= c->getBufferSize()) {
			sleep(1);
		}

		c->buffer8(buf, bytesRead);

		if (!playedYet) {
			dev->addChannel(c);
			c->play();
			playedYet = true;
		}
	}
}

char badsb[] = "BAD Soundblaster version, got 0x%X\n";
void SoundBlaster16::resetDSP()
{
	outb(DSP_RESET, 1);
	nanoSleep(1000 * 1000 * 3);
	outb(DSP_RESET, 0);

	uint8_t x = inb(DSP_READ);
	if (x == 0xAA) {
		outb(DSP_WRITE, WRITE_GET_DSP_VERSION);

		while ((inb(DSP_READSTATUS) & 0x80) == 0);

		dspVersion = inb(DSP_READ);
		inb(DSP_READ);
	} else {
		kprintf(badsb, x);
	}
}

void SoundBlaster16::DSPOut(uint16_t port, uint8_t val)
{
	while ((inb(DSP_WRITE) & 0x80) != 0);
	outb(port, val);
}

void SoundBlaster16::turnSpeakerOn(bool on)
{
	DSPOut(DSP_WRITE, on ? WRITE_SPEAKER_ON : WRITE_SPEAKER_OFF);
	if (!on) {
		DSPOut(DSP_WRITE, WRITE_STOP_CHANNEL_8);
	}
}

char sb16n[] = "SoundBlaster 16";
SoundBlaster16::SoundBlaster16(): SoundDevice(sb16n)
{

}

void SoundBlaster16::handleIRQ()
{
	int bits = currentBits;

	if (bits == 8) {
		inb(DSP_ACKINT8);
	} else {
		outb(DSP_MIXER, 0x82);
		uint8_t intStatus = inb(DSP_MIXER_DATA);
		if (intStatus & 2) {
			inb(DSP_ACKINT16);
		}
	}

	onInterrupt();
}

void sb16Handler(regs* r, void* context)
{
	reinterpret_cast<SoundBlaster16*>(context)->handleIRQ();
}

#define DMA_SIZE 8192

int SoundBlaster16::getNumHwChannels()
{
	return 1;
}

void SoundBlaster16::beginPlayback(int sampleRate, int _bits)
{
	turnSpeakerOn(true);

	uint8_t timeConstant = 256 - (1000000 / ((stereo ? 2 : 1) * hertz));
	DSPOut(DSP_WRITE, WRITE_SET_TIME_CONSTANT);
	DSPOut(DSP_WRITE, timeConstant);
	DSPOut(DSP_WRITE, WRITE_PLAY_SOUND_8 /*+ 4*/);
	DSPOut(DSP_WRITE, ((int) stereo << 5) | ((int) sign << 4));
	DSPOut(DSP_WRITE, (DMA_SIZE / 2 - 1) & 0xFF);
	DSPOut(DSP_WRITE, ((DMA_SIZE / 2 - 1) >> 8) & 0xFF);		//play 1 buffer length

	//start the first segment of playback
	DSPOut(DSP_WRITE, 0x48);
	DSPOut(DSP_WRITE, (DMA_SIZE / 2 - 1) & 0xFF);
	DSPOut(DSP_WRITE, ((DMA_SIZE / 2 - 1) >> 8) & 0xFF);
	DSPOut(DSP_WRITE, 0x1C);
}

void SoundBlaster16::stopPlayback()
{
	turnSpeakerOn(false);
}

int SoundBlaster16::open(int, int, void*)
{
	sign = true;
	stereo = false;

	dmaAddr = PhysMem::allocateDMA(DMA_SIZE);

	hertz = 8000;// sampleRate;
	bits = 8;// _bits;

	//reset the DSP
	resetDSP();
	turnSpeakerOn(true);

	//set IRQ
	DSPOut(DSP_MIXER, MIXER_SET_IRQ);
	DSPOut(DSP_MIXER_DATA, IRQ_5);
	addIRQHandler(5, sb16Handler, true, (void*) this);

	int bits = currentBits;

	//program ISA DMA
	outb(0x0A, 5);
	outb(0x0C, 1);
	outb(0x0B, 0x49);
	outb(0x83, (dmaAddr >> 16) & 0xFF);		//POSITION EXTRA HIGH
	outb(0x02, (dmaAddr >> 0) & 0xFF);		//POSITION LOW
	outb(0x02, (dmaAddr >> 8) & 0xFF);		//POSITION HIGH
	outb(0x03, (DMA_SIZE - 1) & 0xFF);		//LENGTH LOW
	outb(0x03, (DMA_SIZE - 1) >> 8);		//LENGTH HIGH
	outb(0x0A, 1);

	return 0;
}

float tempBuffer[DMA_SIZE / 2];
float outputBuffer[DMA_SIZE / 2];

void SoundBlaster16::onInterrupt()
{
	static bool bufferB = true;

	int samplesGot = getAudio(DMA_SIZE / 2, tempBuffer, outputBuffer);

	uint8_t* dma = (uint8_t*) dmaAddr + (!bufferB ? (DMA_SIZE / 2) : 0);
	//memset(dma, 0, DMA_SIZE / 2);
	floatTo8(outputBuffer, dma, samplesGot);

	bufferB ^= 1;
}

int SoundBlaster16::close(int, int, void*)
{
	return 0;
}