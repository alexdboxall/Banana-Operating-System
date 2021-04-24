#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <stdint.h>

#include "core/terminal.hpp"
#include "hal/device.hpp"
#include "hal/diskctrl.hpp"
#include "hal/diskphys.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void begin(void* a);
void start(Device* parent);

enum class FloppyReg : int
{
	STATUS_A		= 0x0, 
	STATUS_B		= 0x1,
	DOR				= 0x2,
	TAPE			= 0x3,
	MSR				= 0x4,		//read only
	DATA_RATE		= 0x4,		//write only
	FIFO			= 0x5,
	DIR				= 0x7,		//read only
	CCR				= 0x7,		//write only
};

enum class MotorState: int
{
	Off,
	On,
	Waiting
};

enum class DriveType: int
{
	None,
	Drv_360,
	Drv_1200,
	Drv_720,
	Drv_1440,
	Drv_2800,
	Drv_Unknown1,
	Drv_Unknown2,
};

struct FloppyStats
{
	char str[16];
	int8_t dataRate;
	uint8_t cylinders;
	uint8_t heads;
	uint8_t sectors;
	bool perpendicular;
};

FloppyStats floppyTable[] = {
	//name				rate	cyl		heads	sect	perpendicular
	{"none",			-1,		0,		0,		0,		false},
	{"360 KiB 5.25",	-1,		0,		0,		0,		false},
	{"1.2 MiB 5.25",	0,		80,		2,		15,		false},
	{"720 KiB 3.5",		-1,		0,		0,		0,		false},
	{"1.44 KiB 3.5",	0,		80,		2,		18,		false},
	{"2.88 KiB 3.5",	3,		80,		2,		26,		true},
	{"unknown 1",		-1,		0,		0,		0,		false},
	{"unknown 2",		-1,		0,		0,		0,		false},
};

#define DOR_MOTOR_BASE	0x10
#define DOR_IRQ			0x08
#define DOR_RESET		0x04

#define MSR_RQM			0x80
#define MSR_DIO			0x40
#define MSR_NDMA		0x20
#define MSR_CB			0x10
#define MSR_ACTD		0x08
#define MSR_ACTC		0x04
#define MSR_ACTB		0x02
#define MSR_ACTA		0x01

enum FloppyCommands
{
	READ_TRACK = 2,	// generates IRQ6
	SPECIFY = 3,      // * set drive parameters
	SENSE_DRIVE_STATUS = 4,
	WRITE_DATA = 5,      // * write to the disk
	READ_DATA = 6,      // * read from the disk
	RECALIBRATE = 7,      // * seek to cylinder 0
	SENSE_INTERRUPT = 8,      // * ack IRQ6, get status of last command
	WRITE_DELETED_DATA = 9,
	READ_ID = 10,	// generates IRQ6
	READ_DELETED_DATA = 12,
	FORMAT_TRACK = 13,     // *
	DUMPREG = 14,
	SEEK = 15,     // * seek both heads to cylinder X
	VERSION = 16,	// * used during initialization, once
	SCAN_EQUAL = 17,
	PERPENDICULAR_MODE = 18,	// * used during initialization, once, maybe
	CONFIGURE = 19,     // * set controller parameters
	LOCK = 20,     // * protect controller params from a reset
	VERIFY = 22,
	SCAN_LOW_OR_EQUAL = 25,
	SCAN_HIGH_OR_EQUAL = 29
};

class Floppy;

class FloppyDrive : public PhysicalDisk
{
private:

protected:
	Floppy* fdc;
	int num;

public:
	void motorOn();
	void motorOff();

	FloppyDrive();
	
	virtual void configure();
	virtual int open(int _num, int, void* _parent);
	virtual int close(int, int, void*);

	bool floppyConfigure();
};

class Floppy: public HardDiskController
{
private:

protected:
	uint16_t base = 0x3F0;
	ThreadControlBlock* motorThread;

public:
	Floppy();

	MotorState motorStates[4];
	int motorTicks[4];

	void motor(int num, bool state);

	bool lockDoesntWork = true;
	bool triedLock = false;
	bool _failedCommand = false;
	bool _checkedFailure = false;
	bool needReconfigAfterReset = true;
	bool drivePollingModeOn = true;

	virtual bool wasFailure();

	bool lock();

	bool senseInterrupt(int* st0, int* cyl);

	void reset();
	void driveDetection();

	void writeCommand(uint8_t cmd);
	uint8_t readData();

	DriveType driveTypes[4];
	FloppyDrive* drives[4];

	uint8_t readPort(FloppyReg reg);
	void writePort(FloppyReg reg, uint8_t value);

	virtual void configure();					//Configure device settings. Called the first time the device is found.
	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands
};

#endif