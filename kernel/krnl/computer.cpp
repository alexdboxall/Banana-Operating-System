#include "krnl/computer.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "krnl/physmgr.hpp"
#include "thr/elf.hpp"
#include "krnl/idle.hpp"
#include "hw/acpi.hpp"
#include "hal/clock.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#include "hal/vcache.hpp"
#include "fs/vfs.hpp"
#include "vm86/vm8086.hpp"
#include "krnl/powctrl.hpp"
#include "krnl/hal.hpp"
#include "krnl/random.hpp"
#include "krnl/atexit.hpp"
#include "fs/symlink.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


bool KeIsSchedulingOn = false;
bool KeIsPreemptionOn = false;

namespace Krnl
{
	Computer* computer;
}

Computer::Computer() : Device("Computer")
{
	deviceType = DeviceType::Bus;
	parent = nullptr;
}

int Computer::open(int a, int b, void* vas)
{
	VgaText::hiddenOut = false;

	if (!(keBootSettings & 4)) {
		VgaText::hiddenOut = true;
	}

	if (computer != this) {
		KePanic("ASSERTION FAILED: MULTIPLE Computer OBJECTS");
	}

	KeSetBootMessage("Creating device tree...");
	root = new ACPI();
	addChild(root);

	KeSetBootMessage("Configuring processors...");
	HalEnableNMI();
	HalDetectFeatures();
	cpu[0] = new CPU();
	addChild(cpu[0]);
	cpu[0]->open(0, 0, vas);		//FIRST ARG IS CPU NUMBER
	
	KeSetBootMessage("Detecting numerical coprocessors...");
	HalInitialiseCoprocessor();

	KeSetBootMessage("Setting up multitasking...");
	setupMultitasking(KeFirstTask);
	return -1;
}

int Computer::close(int a, int b, void* c)
{
	return -1;
}

void KePrepareShutdown()
{
	KeExecuteAtexit();
	computer->root->closeAll();
}

void (*systemShutdownFunction)();
void (*systemResetFunction)();
void (*systemSleepFunction)();

void KeShutdown()
{
	KePrepareShutdown();
	
	if (systemShutdownFunction) {
		systemShutdownFunction();
	}

	KePanic("You may now turn off your computer.");
}

void KeSleep()
{
	if (systemSleepFunction) {
		systemSleepFunction();
	}
}

void KeRestart()
{
	KePrepareShutdown();
	
	if (systemResetFunction) {
		systemResetFunction();
	}

	uint8_t good = 0x02;
	while (good & 0x02) good = inb(0x64);
	outb(0x64, 0xFE);
}

extern "C" void lwip_init(void);

void KeFirstTask()
{
	HalEnableInterrupts();

	KeSetBootMessage("Starting core threads...");

	//setup up the core processes and threads we need
	Process* idleProcess = new Process(true, "Idle Process", kernelProcess);
	idleProcess->createThread(idleFunction, nullptr, 255);

	cleanerThread = kernelProcess->createThread(cleanerTaskFunction, nullptr, 122);

	KeSetBootMessage("Initialising system components...");
	KeIsSchedulingOn = true;
	KeInitRand();
	Vm::initialise8086();
	Fs::initVFS();

	KeSetBootMessage("Loading device drivers...");
	computer->root->open(0, 0, nullptr);

	KeSetBootMessage("Initialising system components...");
	KeInitialiseSymlinks();
	KeLoadSystemEnv();
	KeSetupPowerManager();
		
	KeSetBootMessage("Loading more device drivers...");
	computer->root->loadDriversForAll();
		
	KeSetBootMessage("Getting ready...");
	Thr::executeDLL(Thr::loadDLL("C:/Banana/System/system.dll"), computer);

	while (1) {
		blockTask(TaskState::Paused);
	}
}