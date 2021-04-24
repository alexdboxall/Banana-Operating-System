#include <stdint.h>

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

extern "C" {
#include "libk/string.h"
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void start(Device* parent)
{
	Floppy* dev = new Floppy();
	parent->addChild(dev);
	//dev->configure();
	//dev->open(0x3F0, 0, nullptr);
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

Floppy::Floppy(): HardDiskController("Floppy Disk Controller")
{
	kprintf("Floppy::Floppy()\n");

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

void Floppy::configure()
{

}

void Floppy::driveDetection()
{
	uint8_t drives;
	uint8_t extendedDrives;

	kprintf("Floppy::driveDetection()\n");

	//do some CMOS detection
	if (base == 0x3F0) {
		drives = Krnl::computer->readCMOS(0x10);

		kprintf("Drive type 0: %s\n", floppyTable[drives >> 4]);
		kprintf("Drive type 1: %s\n", floppyTable[drives & 0xF]);

		
	}
}

int Floppy::open(int baseAddr, int, void*)
{
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

	//reset the FDC
	reset();

	//...
	driveDetection();

	return 0;
}

int Floppy::close(int, int, void*)
{
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

void Floppy::reset()
{
retry:
	//disable and re-enable the controller
	uint8_t dor = readPort(FloppyReg::DOR);
	writePort(FloppyReg::DOR, 0x00);
	writePort(FloppyReg::DOR, dor | DOR_RESET);

	//check if IRQs on
	if (dor & DOR_IRQ) {
		
		//wait for interrupt
		panic("UNIMPL.");

	} else {
		//enable IRQ mode
		writePort(FloppyReg::DOR, dor | DOR_RESET | DOR_IRQ);
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

void FloppyDrive::configure()
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

int FloppyDrive::open(int _num, int _type, void* _parent)
{
	fdc = (Floppy*) _parent;
	num = _num;

	return 0;
}

int FloppyDrive::close(int, int, void*)
{
	return 0;
}
