#include <stdint.h>

void start(void* parent);
void begin(void* a)
{
	start(a);
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/computer.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp" 
#include "fs/vfs.hpp"
#include "hal/vcache.hpp"
#include "hal/partition.hpp"
#include "hal/logidisk.hpp"

extern "C" {
#include "libk/string.h"
} 


void start(void* _parent)
{
	Device* parent = (Device*) _parent;
	Floppy* dev = new Floppy(); 
	parent->addChild(dev);
	dev->_open(0x3F0, 0, nullptr);
}

void floppyMotorFunction(void* _fdc)
{
	Floppy* fdc = (Floppy*) _fdc;

	unlockScheduler();

	while (1) {
		nanoSleep(1000 * 1000 * 400);

		for (int i = 0; i < 4; ++i) {
			if (fdc->motorStates[i] == MotorState::Waiting) {
				fdc->motorTicks[i] -= 400;

				if (fdc->motorTicks[i] <= 0) {
					fdc->motorStates[i] = MotorState::Off;

					lockScheduler();
					uint8_t dor = fdc->readPort(FloppyReg::DOR);
					fdc->writePort(FloppyReg::DOR, dor & ~(DOR_MOTOR_BASE << i));
					unlockScheduler();
				}
			}
		}
	}
}

void floppyIRQHandler(regs* r, void* context)
{
	Floppy* fdc = (Floppy*) context;
	fdc->receivedIRQ = true;
}

Floppy::Floppy(): HardDiskController("Floppy Disk Controller")
{
	interrupt = addIRQHandler(6, floppyIRQHandler, true, (void*) this);
	motorThread = kernelProcess->createThread(floppyMotorFunction, (void*) this, 210);
}

bool Floppy::wasFailure()
{
	_checkedFailure = true;
	bool _v = _failedCommand;
	_failedCommand = false;
	return _v;
}

void Floppy::writeCommand(uint8_t cmd)
{
	if (_failedCommand) {
		panic("PREVIOUS COMMAND FAILED, CAUGHT BY writeCommand");
	}
	if (!_checkedFailure) {
		panic("DID NOT CHECK FOR FAILURE BEFORE writeCommand");
	}

	_checkedFailure = false;
	_failedCommand = false;

	for (int i = 0; i < 50; i++) {
		nanoSleep(1000 * 1000 * 10);
		uint8_t msr = readPort(FloppyReg::MSR);
		if ((msr & MSR_RQM) && !(msr & MSR_DIO)) {
			Floppy::writePort(FloppyReg::FIFO, cmd);
			return;
		}
	}

	_failedCommand = true;
}

uint8_t Floppy::readData()
{
	if (_failedCommand) {
		panic("PREVIOUS COMMAND FAILED, CAUGHT BY writeCommand");
	}
	if (!_checkedFailure) {
		panic("DID NOT CHECK FOR FAILURE BEFORE writeCommand");
	}

	_checkedFailure = false;
	_failedCommand = false;

	for (int i = 0; i < 50; i++) {
		nanoSleep(1000 * 1000 * 10);
		uint8_t msr = readPort(FloppyReg::MSR);
		if ((msr & MSR_RQM) && (msr & MSR_DIO)) {
			return Floppy::readPort(FloppyReg::FIFO);
		}
	}

	_failedCommand = true;

	return 0;
}

uint8_t Floppy::readPort(FloppyReg reg)
{
	return inb(((int) reg) + base);
}

void Floppy::writePort(FloppyReg reg, uint8_t value)
{
	outb(((int) reg) + base, value);
}

void Floppy::driveDetection()
{
	uint8_t drives;
	uint8_t extendedDrives;

	kprintf("Floppy::driveDetection()\n");

	//do some CMOS detection
	if (base == 0x3F0) {
		drives = Krnl::computer->readCMOS(0x10);

		int drvA = drives >> 4;
		int drvB = drives & 0xF;

		kprintf("Drive type 0: %s\n", drvA);
		kprintf("Drive type 1: %s\n", drvB);

		if (drvA) {
			FloppyDrive* dev = new FloppyDrive();
			addChild(dev);
			dev->_open(0, drvA, this);
		}
		if (drvA && drvB) {
			FloppyDrive* dev = new FloppyDrive();
			addChild(dev);
			dev->_open(0, drvB, this);
		}
	}
}

int Floppy::close(int, int, void*)
{
	return 0;
}

int Floppy::open(int baseAddr, int, void*)
{
	return 0;
}

int Floppy::_open(int baseAddr, int, void*) {
	
	//store the base address
	base = baseAddr;

	//claim the fix six
	ports[noPorts].rangeStart = base;
	ports[noPorts].rangeLength = 6;
	ports[noPorts++].width = 0;

	//skip 0x3F6, then do 0x3F7
	ports[noPorts].rangeStart = base + 7;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	//blank the pointers
	for (int i = 0; i < 4; ++i) {
		drives[i] = nullptr;
		motorStates[i] = MotorState::Off;
	}

	//set the bits to the correct state
	wasFailure();
	drivePollingModeOn = true;
	triedLock = false;

	//reset the FDC
	reset();

	//...
	driveDetection();

	return 0;
}

bool Floppy::senseInterrupt(int* st0, int* cyl)
{
	writeCommand(SENSE_INTERRUPT);
	if (wasFailure()) {
		return false;
	}
	*st0 = readData();
	if (wasFailure()) {
		return false;
	}
	*cyl = readData();
	if (wasFailure()) {
		return false;
	}

	return true;
}

bool Floppy::lock()
{
	writeCommand(LOCK);
	if (wasFailure()) {
		return false;
	}

	readData();
	if (wasFailure()) {
		return false;
	}

	return true;
}

bool Floppy::waitIRQ(int millisecTimeout)
{
	int timeout = 0;
	while (!receivedIRQ) {
		nanoSleep(1000 * 1000 * 50);
		timeout += 50;
		if (timeout >= millisecTimeout) {
			break;
		}
	}
	return receivedIRQ;
}

void Floppy::reset()
{
retry:
	receivedIRQ = false;
	currentSelection = -1;
	selectionLock = false;

	//disable and re-enable the controller
	uint8_t dor = readPort(FloppyReg::DOR);
	writePort(FloppyReg::DOR, 0x00);
	writePort(FloppyReg::DOR, dor | DOR_RESET | DOR_IRQ);

	//check if IRQs on
	if (dor & DOR_IRQ) {
		bool gotIRQ = waitIRQ(400);
		if (!gotIRQ) {
			writePort(FloppyReg::DOR, dor | DOR_RESET | DOR_IRQ);
			goto retry;
		}

	} else {
		//enable IRQ mode
		writePort(FloppyReg::DOR, dor | DOR_RESET | DOR_IRQ);
		goto retry;
	}

	//sense interrupt 4 times
	if (drivePollingModeOn) {
		int st0, cyl;

		bool success = senseInterrupt(&st0, &cyl);
		if (success) success = senseInterrupt(&st0, &cyl);
		if (success) success = senseInterrupt(&st0, &cyl);
		if (success) success = senseInterrupt(&st0, &cyl);

		if (!success) {
			drivePollingModeOn = false;
			goto retry;
		}
	}

	if (lockDoesntWork || !triedLock) {
		//now reconfigure the drives if we haven't locked it
		if (needReconfigAfterReset) {
			for (int i = 0; i < 4; ++i) {
				if (drives[i]) {
					drives[i]->floppyConfigure();
				}
			}
		}

		//first time
		if (!triedLock) {
			lockDoesntWork = !lock();
			triedLock = true;

			if (lockDoesntWork) {
				//the lock didn't work, so reset without locking this time
				goto retry;

			} else {
				//okay, locked.
			}
		}		
	}
}

#define DMA_LENGTH	0x4800
void Floppy::dmaInit(bool write)
{
	/// TODO: use symbols from another driver... (add driver symbols to the kernel table)
	
	static size_t dmaBase = 0;

	if (dmaBase == 0) {
		dmaBase = Phys::allocateDMA(DMA_LENGTH);
	}

	union
	{
		unsigned char b[4]; // 4 bytes
		unsigned long l;    // 1 long = 32-bit
	} a, c; // address and count

	a.l = (unsigned) dmaBase;
	c.l = (unsigned) DMA_LENGTH - 1; // -1 because of DMA counting

	// check that address is at most 24-bits (under 16MB)
	// check that count is at most 16-bits (DMA limit)
	// check that if we add count and address we don't get a carry
	// (DMA can't deal with such a carry, this is the 64k boundary limit)
	if ((a.l >> 24) || (c.l >> 16) || (((a.l & 0xffff) + c.l) >> 16)) {
		panic("floppy_dma_init: static buffer problem\n");
	}

	outb(0x0a, 0x06);   // mask chan 2

	outb(0x0c, 0xff);   // reset flip-flop
	outb(0x04, a.b[0]); //  - address low byte
	outb(0x04, a.b[1]); //  - address high byte

	outb(0x81, a.b[2]); // external page register

	outb(0x0c, 0xff);   // reset flip-flop
	outb(0x05, c.b[0]); //  - count low byte
	outb(0x05, c.b[1]); //  - count high byte

	outb(0x0b, write ? 0x4a : 0x46);   // set mode (see above)

	outb(0x0a, 0x02);   // unmask chan 2
}

bool Floppy::specify(int drive)
{
	int datarateTable[4] = { 500000, 300000, 250000, 1000000 };
	int datarateID = floppyTable[(int) driveTypes[drive]].dataRate;
	if (datarateID == -1) {
		panic("SPECIFY BAD DATARATE");
	}
	int datarate = datarateTable[datarateID];
	int srt = 16 - (7 * datarate / 500000);
	int hlt = 30 * datarate / 1000000;
	int hut = 0;		// 240 * datarate / 8000000;
	int ndma = 0;

	writeCommand(SPECIFY);
	if (wasFailure()) return false;
	writeCommand(srt << 4 | hut);
	if (wasFailure()) return false;
	writeCommand(hlt << 1 | ndma);
	if (wasFailure()) return false;

	return true;
}

bool Floppy::select(int drive, bool state)
{
	if (currentSelection == drive && !state && currentSelection != -1) {
		//lock holder is trying to unlock
		selectionLock = false;

	} else if (!selectionLock || currentSelection == -1) {
		//only redo it all if we didn't just have it

		if (currentSelection != drive) {
			//someone else wants it
			lockScheduler();

			//select this drive
			uint8_t dor = readPort(FloppyReg::DOR);
			dor &= ~3;
			dor |= drive;
			writePort(FloppyReg::DOR, dor);
			nanoSleep(1000 * 1000 * 80);

			//set the datarate
			int8_t rate = floppyTable[(int) driveTypes[drive]].dataRate;
			if (rate == -1) {
				panic("UNSUPPORTED FLOPPY FORMAT (DATARATE NOT KNOWN)");
			}
			writePort(FloppyReg::CCR, rate);
			unlockScheduler();

			//specify more drive details
			bool success = specify(drive);
			if (!success) {
				kprintf("specifiy reset.\n");
				reset();
				return false;
			}

			//now calibrate the drive
			success = drives[drive]->calibrate();
			if (!success) {
				kprintf("calibrate reset.\n");
				reset();
				return false;
			}
		}

		selectionLock = state;
		currentSelection = drive;
	}

	return selectionLock && (currentSelection == drive);
}

void Floppy::motor(int num, bool state)
{
	if (state) {
		if (motorStates[num] == MotorState::Off) {
			//start drive

			lockScheduler();
			uint8_t dor = readPort(FloppyReg::DOR);
			writePort(FloppyReg::DOR, dor | (DOR_MOTOR_BASE << num));
			unlockScheduler();

			if (driveTypes[num] == DriveType::Drv_1440) {
				nanoSleep(1000 * 1000 * 300);
			} else {
				nanoSleep(1000 * 1000 * 500);
			}

			motorStates[num] = MotorState::On;

		} else if (motorStates[num] == MotorState::Waiting) {
			//put back to on mode
			motorStates[num] = MotorState::On;
		}

	} else {
		if (motorStates[num] == MotorState::On) {
			motorStates[num] = MotorState::Waiting;
			motorTicks[num] = 2500;
		}
	}
}








FloppyDrive::FloppyDrive() : PhysicalDisk("Floppy Disk Drive", 512)
{

}

void FloppyDrive::motorOn()
{
	fdc->motor(num, true);
}

void FloppyDrive::motorOff()
{
	fdc->motor(num, false);
}

bool FloppyDrive::floppyConfigure()
{
	bool impliedSeek = false;
	bool fifoDisable = false;
	bool drivePollingModeDisable = true;
	int threshold = 8;
	int precomp = 0;

	fdc->writeCommand(CONFIGURE);
	if (fdc->wasFailure()) return false;
	fdc->writeCommand(0);
	if (fdc->wasFailure()) return false;
	fdc->writeCommand(\
					  ((uint8_t) impliedSeek)				<< 6 | \
					  ((uint8_t) fifoDisable)				<< 5 | \
					  ((uint8_t) drivePollingModeDisable)	<< 4 | \
					  (threshold - 1)
	);
	if (fdc->wasFailure()) return false;
	fdc->writeCommand(precomp);
	if (fdc->wasFailure()) return false;

	fdc->drivePollingModeOn = !drivePollingModeDisable;
	
	return true;
}

int FloppyDrive::_open(int _num, int _type, void* _parent)
{
	fdc = (Floppy*) _parent;
	num = _num;

	sectorSize = 512;
	removable = true;

	sizeInKBs = ((int) floppyTable[_type].cylinders) * ((int) floppyTable[_type].sectors) * ((int) floppyTable[_type].heads) / 2;

	startCache();
	createPartitionsForDisk(this);

	return 0;
}

int FloppyDrive::close(int, int, void*)
{
	return 0;
}

void FloppyDrive::unselect()
{
	fdc->select(num, false);
}

void FloppyDrive::select()
{
	while (1) {
		bool gotLock = fdc->select(num, true);
		if (gotLock) return;
		kprintf("selection locked or failed...\n");
		nanoSleep(1000 * 1000 * 150);
	}
}

bool FloppyDrive::seek(int cyli, int head)
{
	int retries = 0;
retry:
	if (retries >= 5) {
		kprintf("seek: 5 retries, could not calibrate.\n");
		motorOff();
		unselect();
		return false;
	}

	select();
	motorOn();

	fdc->writeCommand(SEEK);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}

	fdc->receivedIRQ = false;

	fdc->writeCommand(num | (head << 2));
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}

	fdc->writeCommand(cyli);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}

	bool gotIRQ = fdc->waitIRQ(1500);
	if (!gotIRQ) {
		fdc->reset();
		++retries;
		goto retry;
	}

	int st0 = 0xC0;
	int cyl = -1;
	bool success = fdc->senseInterrupt(&st0, &cyl);
	if (!success) fdc->reset();
	if (!success || cyl != cyli) {
		++retries;
		goto retry;
	}

	motorOff();
	unselect();

	return true;
}

bool FloppyDrive::calibrate()
{
	int retries = 0;
retry:
	if (retries >= 5) {
		kprintf("calibrate: 5 retries, could not calibrate.\n");
		motorOff();
		unselect();
		return false;
	}

	select();
	motorOn();

	fdc->writeCommand(RECALIBRATE);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}

	fdc->receivedIRQ = false;

	fdc->writeCommand(num);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}

	bool gotIRQ = fdc->waitIRQ(1500);
	if (!gotIRQ) {
		fdc->reset();
		++retries;
		goto retry;
	}

	int st0 = 0xC0;
	int cyl = -1;
	bool success = fdc->senseInterrupt(&st0, &cyl);
	if (!success) fdc->reset();
	if (!success || cyl || !(st0 & 0x20)) {
		++retries;
		goto retry;
	}

	motorOff();
	unselect();
	return true;
}

int FloppyDrive::doTrack(int cyl, bool write)
{
	int cmd = (write ? WRITE_DATA : READ_DATA) | 0xC0;
	int retries = 0;

retry:
	if (retries == 20) {
		motorOff();
		unselect();
		return -2;
	}

	//seek both heads
	if (!seek(cyl, 0)) return -1;
	if (!seek(cyl, 1)) return -1;

	motorOn();
	select();

	fdc->dmaInit(write);

	nanoSleep(1000 * 1000 * 100);

	fdc->writeCommand(cmd);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(num);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(cyl);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(0);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(1);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(2);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(18);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(0x1B);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}
	fdc->writeCommand(0xFF);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}

	bool gotIRQ = fdc->waitIRQ(1000);
	if (!gotIRQ) {
		fdc->reset();
		retries++;
		goto retry;
	}

	uint8_t st0, st1, st2, rcy, rhe, rse, bps;
	st0 = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	st1 = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	st2 = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	rcy = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	rhe = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	rse = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	bps = fdc->readData();
	if (fdc->wasFailure()) {
		kprintf("failure reading status.\n");
		fdc->reset();
		retries++;
		goto retry;
	}

	motorOff();
	unselect();
	return 0;
}

int FloppyDrive::read(uint64_t lba, int count, void* ptr)
{
	return -3;
}

int FloppyDrive::write(uint64_t lba, int count, void* ptr)
{
	return -3;
}