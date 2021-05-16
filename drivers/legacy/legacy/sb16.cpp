
#include <stdint.h>
#include <stddef.h>

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
#define WRITE_STOP_CHANNEL_8		0xD0
#define WRITE_SPEAKER_ON			0xD1
#define WRITE_SPEAKER_OFF			0xD3
#define WRITE_STOP_CHANNEL_16		0xD5
#define WRITE_GET_DSP_VERSION		0xE1

#define WRITE_PLAY_SOUND_16			0xB0
#define WRITE_PLAY_SOUND_8			0xC0

#define MIXER_MASTER_VOLUME			0x22
#define MIXER_SET_IRQ				0x80
#define MIXER_SET_DMA				0x81

#define DMA_0			1
#define DMA_1			2
//DMA2 hardwired to floppy
#define DMA_3			8

#define IRQ_2			1
#define IRQ_5			2
#define IRQ_7			4
#define IRQ_10			8

#define DMA_SIZE (8192 * 2)

#include "isadma.hpp"
#include "sb16.hpp"
#include "main.hpp"

#include "thr/prcssthr.hpp"
#include "core/physmgr.hpp"
#include "hw/ports.hpp"
#include "fs/vfs.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

int16_t buf[4096];

void sb16Demo(void* __)
{
	unlockScheduler();

	SoundCard* card = (SoundCard*) __;

	SoundPort* port = new SoundPort(22050, 16, 2, 65536);
	bool started = false;

	File* f = new File("C:/Banana/Audio/win98snd.wav", kernelProcess);
	f->open(FileOpenMode::Read);

	while (1) {
		int bytesRead = 0;
		FileStatus st = f->read(4096 * 2, buf, &bytesRead);

		if (bytesRead == 0 || st != FileStatus::Success) {
			kprintf("SONG SHOULD BE DONE.\n");
			break;
		}

		while (started && port->getBufferUsed() + bytesRead * 3 >= port->getBufferSize()) {
			lockScheduler();
			schedule();
			unlockScheduler();
		}

		port->buffer16(buf, bytesRead / 2);

		if (!started) {
			card->configureRates(22050, 16, 2);
			card->addChannel(port);
			port->unpause();
			card->beginPlayback();
			started = true;
		}
	}

	terminateTask(0);
}

char badVer[] = "BAD Soundblaster version, got 0x%X\n";
void SoundBlaster16::resetDSP()
{
	outb(DSP_RESET, 1);
	milliTenthSleep(30);
	outb(DSP_RESET, 0);

	uint8_t x = inb(DSP_READ);
	if (x == 0xAA) {
		outb(DSP_WRITE, WRITE_GET_DSP_VERSION);

		while ((inb(DSP_READSTATUS) & 0x80) == 0);

		dspVersion = inb(DSP_READ);
		inb(DSP_READ);
	} else {
		kprintf(badVer, x);
	}
}

void SoundBlaster16::DSPOut(uint16_t port, uint8_t val)
{
	while ((inb(DSP_WRITE) & 0x80) != 0);
	outb(port, val);
}

void SoundBlaster16::turnSpeakerOn(bool on)
{
	if (!on) {
		DSPOut(DSP_WRITE, currentBits == 16 ? WRITE_STOP_CHANNEL_16 : WRITE_STOP_CHANNEL_8);
		DSPOut(DSP_WRITE, currentBits == 16 ? 0xD9 : 0xDA);
		DSPOut(DSP_WRITE, WRITE_SPEAKER_OFF);
	} else {
		DSPOut(DSP_WRITE, WRITE_SPEAKER_ON);
	}
}

SoundBlaster16::SoundBlaster16(): SoundCard("SoundBlaster 16")
{
	ports[noPorts].rangeStart = 0x220;
	ports[noPorts].rangeLength = 16;
	ports[noPorts++].width = 0;
}

void SoundBlaster16::handleIRQ()
{
	kprintf("SB16 IRQ.\n");
	if (currentBits == 8) {
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

void SoundBlaster16::beginPlayback()
{
	bool stereo = currentChannels == 2;
	bool sign = true;

	//we need to turn the speaker on
	turnSpeakerOn(true);

	if (currentBits == 16) {
		DSPOut(DSP_WRITE, 0x41);
		DSPOut(DSP_WRITE, (currentSampleRate >> 8) & 0xFF);
		DSPOut(DSP_WRITE, (currentSampleRate >> 0) & 0xFF);

		DSPOut(DSP_WRITE, 0xB6);  
		DSPOut(DSP_WRITE, ((int) stereo << 5) | 0x10);
		DSPOut(DSP_WRITE, (DMA_SIZE / 4 - 1) & 0xFF);
		DSPOut(DSP_WRITE, ((DMA_SIZE / 4 - 1) >> 8) & 0xFF);

	} else {
		//write sample rate
		uint8_t timeConstant = 256 - (1000000 / ((currentBits == 16 ? 2 : 1) * (stereo ? 2 : 1) * currentSampleRate));
		DSPOut(DSP_WRITE, WRITE_SET_TIME_CONSTANT);
		DSPOut(DSP_WRITE, timeConstant);

		//get ready to play
		DSPOut(DSP_WRITE, currentBits == 16 ? WRITE_PLAY_SOUND_16 : WRITE_PLAY_SOUND_8);
		DSPOut(DSP_WRITE, ((int) stereo << 5) | ((int) sign << 4));
		DSPOut(DSP_WRITE, (DMA_SIZE / 2 - 1) & 0xFF);
		DSPOut(DSP_WRITE, ((DMA_SIZE / 2 - 1) >> 8) & 0xFF);		//play 1/2 buffer before interrupt

		//start the first segment of playback
		DSPOut(DSP_WRITE, 0x48);
		DSPOut(DSP_WRITE, (DMA_SIZE / 2 - 1) & 0xFF);
		DSPOut(DSP_WRITE, ((DMA_SIZE / 2 - 1) >> 8) & 0xFF);
		DSPOut(DSP_WRITE, 0x1C);
	}
}

void SoundBlaster16::stopPlayback()
{
	turnSpeakerOn(false);
}

char nodma[] = "could not get a SB16 DMA channel\n";
char noirq[] = "SB16 READONLY IRQ PROBLEM";
char baddma[] = "SOUNDBLASTER INVL. DMA CHANNEL";
int SoundBlaster16::open(int, int, void*)
{
	return 0;
}

int SoundBlaster16::_open(int, int, void*)
{
	bool readonly = false;
	//check for readonly bytes 0x80 and 0x81
	{
		//get the current IRQ setting
		DSPOut(DSP_MIXER, MIXER_SET_IRQ);
		uint8_t oldIRQ = inb(DSP_MIXER_DATA);

		//write back a modified value
		DSPOut(DSP_MIXER, MIXER_SET_IRQ);
		DSPOut(DSP_MIXER_DATA, oldIRQ == 2 ? 1 : 2);

		//read it back
		DSPOut(DSP_MIXER, MIXER_SET_IRQ);
		uint8_t newIRQ = inb(DSP_MIXER_DATA);

		//it is readonly if it didn't change
		readonly = newIRQ == oldIRQ;
	}

	if (readonly) {
		//if read only, get the DMA channel
		DSPOut(DSP_MIXER, MIXER_SET_DMA);
		uint8_t needs = inb(DSP_MIXER_DATA) & 0xF;		//only get 8 bit channels

		//convert that to a DMA channel number
		int dmaNum = 0;
		if (needs & DMA_1)			dmaNum = 1;
		else if (needs & DMA_3)		dmaNum = 1;
		else {
			//if we get any 16 bit value or DMA0, set a bogus value
			//so that it will fail
			dmaNum = 99;
		}

		//try to get that channel
		dmaChannel = isaDMAController->tryLockChannel(dmaNum);
		if (dmaChannel == nullptr) {
			//if not, we can't do anything (in 8 bit mode at least)
			kprintf(nodma);
			return -1;
		}

	} else {
		//try get DMA 1
		dmaChannel = isaDMAController->tryLockChannel(1);
		if (dmaChannel == nullptr) {
			//if we can't, try for DMA 3
			dmaChannel = isaDMAController->tryLockChannel(3);
			if (dmaChannel == nullptr) {
				//if we can't, we can't do anything (in 8 bit mode at least)
				kprintf(nodma);
				return -1;
			}
		}
	}

	kprintf("soundblaster 16.\n");
	//program the DMA
	/*dmaChannel->allocateAddressAndSet(DMA_SIZE);
	dmaChannel->setMode(0x59);
	dmaChannel->start();
	dmaAddr = dmaChannel->getAddress();*/

	dmaChannel16 = isaDMAController->tryLockChannel(5);
	if (dmaChannel16 == nullptr) {
		panic("CAN'T GET DMA CHANNEL 5!");
	}
	dmaChannel16->allocateAddressAndSet(DMA_SIZE / 2);
	dmaChannel16->setMode(0x59);
	dmaChannel16->start();
	dma16Addr = dmaChannel16->getAddress();
	kprintf("soundblaster 16 - B.\n");

	kprintf("soundblaster: DMA channel 5 has address of 0x%X\n", dmaChannel16->getAddress());
	kprintf("soundblaster: DMA channel 5 has address of 0x%X\n", dma16Addr);
	kprintf("soundblaster: DMA channel 5 has ch. num. of 0x%X\n", dmaChannel16->getChannelNum());

	//reset the DSP
	resetDSP();
	turnSpeakerOn(true);

	//set IRQ
	if (readonly) {
		//ge the IRQ number
		DSPOut(DSP_MIXER, MIXER_SET_IRQ);
		uint8_t currentIRQ = inb(DSP_MIXER_DATA);

		//and set it
		if (currentIRQ == IRQ_2)	   addIRQHandler(2, sb16Handler, true, (void*) this);
		else if (currentIRQ == IRQ_5)  addIRQHandler(5, sb16Handler, true, (void*) this);
		else if (currentIRQ == IRQ_7)  addIRQHandler(7, sb16Handler, true, (void*) this);
		else if (currentIRQ == IRQ_10) addIRQHandler(10, sb16Handler, true, (void*) this);
		else {
			panic(noirq);
		}

	} else {
		DSPOut(DSP_MIXER, MIXER_SET_IRQ);
		DSPOut(DSP_MIXER_DATA, IRQ_5);
		addIRQHandler(5, sb16Handler, true, (void*) this);
	}


	//read the current soundblaster channel so we can save the 16 bit DMA channel
	DSPOut(DSP_MIXER, MIXER_SET_DMA);
	uint8_t currentDMA = inb(DSP_MIXER_DATA);
	kprintf("SB16: current DMA register = 0x%x\n", currentDMA);

	//set the soundblaster's DMA channel
	DSPOut(DSP_MIXER, MIXER_SET_DMA);
	if (dmaChannel->getChannelNum() == 1) DSPOut(DSP_MIXER_DATA, (currentDMA & ~0xF) | DMA_1);
	else if (dmaChannel->getChannelNum() == 3) DSPOut(DSP_MIXER_DATA, (currentDMA & ~0xF) | DMA_3);
	else {
		panic(baddma);
	}

	//set volume
	DSPOut(DSP_MIXER, MIXER_MASTER_VOLUME);
	DSPOut(DSP_MIXER, 0xFF);

	return 0;
}

void SoundBlaster16::onInterrupt()
{
	static bool bufferB = true;

	if (currentBits == 16) {
		kprintf("on irq, dma16Addr = 0x%X, 5::addr = 0x%X\n", dma16Addr, dmaChannel16->getAddress());
		int16_t* dma = (int16_t*) (dma16Addr + (!bufferB ? (DMA_SIZE / 2) : 0));
		kprintf("write location = 0x%X\n", dma);

		int wordsGot = getSamples16(DMA_SIZE / 4, dma);
		if (wordsGot == 0) {
			kprintf("hello world A!\n");
			turnSpeakerOn(false);
			
		} else if (wordsGot < DMA_SIZE / 4) {
			kprintf("hello world B!\n");

			DSPOut(DSP_WRITE, 0xB0);
			DSPOut(DSP_WRITE, ((int) (currentChannels == 2 ? 1 : 0) << 5) | 0x10);
			DSPOut(DSP_WRITE, (wordsGot - 1) & 0xFF);
			DSPOut(DSP_WRITE, ((wordsGot - 1) >> 8) & 0xFF);
		}

	} else {
		uint8_t* dma = (uint8_t*) (dmaAddr) + (!bufferB ? (DMA_SIZE / 2) : 0);

		/*int samplesGot = ?;
		* 
		if (samplesGot == 0) {
			turnSpeakerOn(false);

		} else if (samplesGot < DMA_SIZE / 2) {
			DSPOut(DSP_WRITE, 0x24);
			DSPOut(DSP_WRITE, (samplesGot - 1) & 0xFF);
			DSPOut(DSP_WRITE, ((samplesGot - 1) >> 8) & 0xFF);
		}*/
	}
	

	bufferB ^= 1;
}

int SoundBlaster16::close(int, int, void*)
{
	//give back the DMA channel
	if (dmaChannel != nullptr) {
		isaDMAController->unlockChannel(dmaChannel);
	}
	return 0;
}
