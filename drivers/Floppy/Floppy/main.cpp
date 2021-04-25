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
	uint8_t drvs;
	uint8_t extendedDrives;

	kprintf("Floppy::driveDetection()\n");

	//do some CMOS detection
	if (base == 0x3F0) {
		drvs = Krnl::computer->readCMOS(0x10);

		int drvA = drvs >> 4;
		int drvB = drvs & 0xF;

		kprintf("Drive type 0: 0x%X\n", drvA);
		kprintf("Drive type 1: 0x%X\n", drvB);

		if (drvA) {
			FloppyDrive* dev = new FloppyDrive();
			driveTypes[0] = (DriveType) drvA;
			drives[0] = dev;
			addChild(dev);
			dev->_open(0, drvA, this);
		}
		if (drvA && drvB) {
			FloppyDrive* dev = new FloppyDrive();
			driveTypes[1] = (DriveType) drvB;
			drives[1] = dev;
			addChild(dev);
			dev->_open(1, drvB, this);
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
	kprintf("void Floppy::reset()\n");

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
size_t _TEMP_dma;
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

	_TEMP_dma = dmaBase;
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
		kprintf("select (A). %d\n", drive);

		if (currentSelection != drive) {
			kprintf("select (B).\n");
			//someone else wants it
			lockScheduler();
			kprintf("select (C).\n");

			//select this drive
			uint8_t dor = readPort(FloppyReg::DOR);
			dor &= ~3;
			dor |= drive;
			writePort(FloppyReg::DOR, dor);
			nanoSleep(1000 * 1000 * 80);
			kprintf("select (D).\n");

			//set the datarate
			int8_t rate = floppyTable[(int) driveTypes[drive]].dataRate;
			if (rate == -1) {
				panic("UNSUPPORTED FLOPPY FORMAT (DATARATE NOT KNOWN)");
			}
			writePort(FloppyReg::CCR, rate);
			unlockScheduler();
			kprintf("select (E).\n");

			//specify more drive details
			bool success = specify(drive);
			if (!success) {
				kprintf("specifiy reset.\n");
				reset();
				return false;
			}
			kprintf("select (F).\n");

			//now calibrate the drive
			success = drives[drive]->calibrate();
			kprintf("select (F2).\n");
			if (!success) {
				kprintf("calibrate reset.\n");
				reset();
				return false;
			}
			kprintf("select (G).\n");

		}
		kprintf("select (H).\n");

		selectionLock = state;
		currentSelection = drive;
		kprintf("select (I).\n");

	}

	return selectionLock && (currentSelection == drive);
}

void Floppy::motor(int num, bool state)
{
	kprintf("Floppy::motor\n");
	kprintf("num = %d, state = %d\n", num, state);

	if (state) {
		kprintf("state.\n");
		if (motorStates[num] == MotorState::Off) {
			//start drive

			kprintf("starting the motor.\n");
			lockScheduler();
			uint8_t dor = readPort(FloppyReg::DOR);
			kprintf("dor 1 = 0x%X\n", dor);
			kprintf("dor 2 = 0x%X\n", dor | (DOR_MOTOR_BASE << num));
			writePort(FloppyReg::DOR, dor | (DOR_MOTOR_BASE << num));
			unlockScheduler();

			kprintf("motor again.\n");

			if (driveTypes[num] == DriveType::Drv_1440) {
				nanoSleep(1000 * 1000 * 300);
			} else {
				nanoSleep(1000 * 1000 * 500);
			}
			kprintf("motor again 2.\n");

			motorStates[num] = MotorState::On;
			kprintf("motor again 3.\n");

		} else if (motorStates[num] == MotorState::Waiting) {
			kprintf("motor again 4.\n");
			//put back to on mode
			motorStates[num] = MotorState::On;
		}

	} else {
		kprintf("motor again 5.\n");
		if (motorStates[num] == MotorState::On) {
			kprintf("motor again 6.\n");
			motorStates[num] = MotorState::Waiting;
			motorTicks[num] = 2500;
		}
	}

	kprintf("Floppy::motor done.\n");
}








FloppyDrive::FloppyDrive() : PhysicalDisk("Floppy Disk Drive", 512)
{

}

void FloppyDrive::motorOn()
{
	kprintf("FloppyDrive::motorOn num = %d\n", num);
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

int FloppyDrive::open(int _num, int _type, void* _parent)
{
	return 0;
}

int FloppyDrive::_open(int _num, int _type, void* _parent)
{
	fdc = (Floppy*) _parent;
	num = _num;
	kprintf("num = %d\n", num);

	sectorSize = 512;
	removable = true;

	sizeInKBs = ((int) floppyTable[_type].cylinders) * ((int) floppyTable[_type].sectors) * ((int) floppyTable[_type].heads) / 2;

	kprintf("size in KBs = %d\n", sizeInKBs);

	kprintf("FloppyDrive::_open 1\n");
	startCache();	
	kprintf("FloppyDrive::_open 2\n");
	createPartitionsForDisk(this);
	kprintf("FloppyDrive::_open 3\n");

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
		kprintf("FloppyDrive::select\n");
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
	kprintf("seek (sel) %d.\n", num);
	select();
	kprintf("seek (on) %d.\n", num);
	motorOn();
	kprintf("seek (1).\n");

	fdc->writeCommand(SEEK);
	if (fdc->wasFailure()) {
		kprintf("seek (aa).\n");
		fdc->reset();
		kprintf("seek (bb).\n");
		++retries;
		goto retry;
	}
	kprintf("seek (2).\n");

	fdc->receivedIRQ = false;

	fdc->writeCommand(num | (head << 2));
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("seek (3).\n");

	fdc->writeCommand(cyli);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("seek (4).\n");

	bool gotIRQ = fdc->waitIRQ(1500);
	if (!gotIRQ) {
		kprintf("seek (nirq).\n");
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("seek (5).\n");

	int st0 = 0xC0;
	int cyl = -1;
	bool success = fdc->senseInterrupt(&st0, &cyl);
	if (!success) fdc->reset();
	if (!success || cyl != cyli) {
		++retries;
		goto retry;
	}
	kprintf("seek (sid).\n");
	motorOff();
	kprintf("seek (off).\n");
	unselect();
	kprintf("seek (un).\n");

	return true;
}

bool FloppyDrive::calibrate()
{
	int retries = 0;
retry:
	if (retries >= 5) {
		kprintf("calibrate: 5 retries, could not calibrate.\n");
		motorOff();
		//unselect();
		return false;
	}

	//select();
	kprintf("cal (on), %d\n", num);
	motorOn();
	kprintf("cal (0)\n");

	fdc->writeCommand(RECALIBRATE);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("cal (1)\n");

	fdc->receivedIRQ = false;

	fdc->writeCommand(num);
	if (fdc->wasFailure()) {
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("cal (2)\n");

	bool gotIRQ = fdc->waitIRQ(1500);
	if (!gotIRQ) {
		fdc->reset();
		++retries;
		goto retry;
	}
	kprintf("cal (3)\n");

	int st0 = 0xC0;
	int cyl = -1;
	bool success = fdc->senseInterrupt(&st0, &cyl);
	kprintf("cal (4)\n");
	if (!success) fdc->reset();
	if (!success || cyl || !(st0 & 0x20)) {
		++retries;
		goto retry;
	}
	kprintf("cal (5)\n");

	motorOff();
	//unselect();
	return true;
}

int FloppyDrive::doTrack(int cyl, bool write, uint8_t* buffer)
{
	if (write) {
		panic("WRITE: NEED TO COPY DATA TO DMA BUFFER");
	}

	int cmd = (write ? WRITE_DATA : READ_DATA) | 0xC0;
	int retries = 0;

retry:
	kprintf(" retry: \n");

	if (retries == 20) {
		motorOff();
		unselect();
		return -2;
	}

	kprintf("About to seek.\n");
	//seek both heads
	if (!seek(cyl, 0)) return -1;
	if (!seek(cyl, 1)) return -1;
	kprintf("Seek done.\n");

	motorOn();	
	kprintf("Motor on.\n");
	select();
	kprintf("Selected.\n");

	fdc->dmaInit(write);
	kprintf("DMA init'd.\n");

	nanoSleep(1000 * 1000 * 100);
	kprintf("sleep done\n");

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

	fdc->receivedIRQ = false;
	fdc->writeCommand(0xFF);
	if (fdc->wasFailure()) {
		fdc->reset();
		retries++;
		goto retry;
	}

	kprintf("about to waitIRQ.\n");
	bool gotIRQ = fdc->waitIRQ(1000);
	if (!gotIRQ) {
		kprintf("no IRQ.\n");
		fdc->reset();
		retries++;
		goto retry;
	}
	kprintf("got IRQ.\n");

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

	kprintf("read result bytes.\n");

	motorOff();
	kprintf("motor off\n");
	unselect();
	kprintf("unselect.\n");

	if (!write) {
		kprintf("about to memcpy.\n");
		memcpy(buffer, (const void*) _TEMP_dma, 0x4800);
		kprintf("done memcpy.\n");
	}

	return 0;
}

void FloppyDrive::lbaToCHS(uint32_t lba, int* cyl, int* head, int* sector)
{
	int sectorsPerTrack = floppyTable[(int) fdc->driveTypes[num]].sectors;

	*cyl = lba / (2 * sectorsPerTrack);
	*head = ((lba % (2 * sectorsPerTrack)) / sectorsPerTrack);
	*sector = ((lba % (2 * sectorsPerTrack)) % sectorsPerTrack + 1);
}

uint8_t _TEMP_trackBuffer[0x4800];

int FloppyDrive::read(uint64_t lba, int count, void* ptr)
{
	if (count != 1) {
		panic("floppy count not 1");
	}

	kprintf("FloppyDrive::read called.\n");
	int cyl, head, sector;
	lbaToCHS(lba, &cyl, &head, &sector);
	kprintf("C 0x%X, H 0x%X, S 0x%X\n", cyl, head, sector);
	doTrack(cyl, false, _TEMP_trackBuffer);
	kprintf("read buffer here: 0x%X\n", _TEMP_trackBuffer);
	kprintf("did track.\n");
	memcpy(ptr, _TEMP_trackBuffer + (sector - 1) * 512, 512);
	kprintf("did memcpy.\n");
	kprintf("ptr = 0x%X.\n", ptr);

	return 0;
}

int FloppyDrive::write(uint64_t lba, int count, void* ptr)
{
	panic("floppy write called");
	return -3;
}

FloppyDrive::~FloppyDrive()
{

}