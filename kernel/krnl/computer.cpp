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

	features.hasACPI = true;

	/*ports[noPorts].rangeStart = PORT_CMOS_BASE;
	ports[noPorts].rangeLength = 2;
	ports[noPorts++].width = 0;*/
}

int Computer::open(int a, int b, void* vas)
{
	VgaText::hiddenOut = false;

	if (!(sysBootSettings & 4)) {
		VgaText::hiddenOut = true;
	}

	KeSetBootMessage("Creating device tree...");
	root = new ACPI();
	addChild(root);

	detectFeatures();
	HalEnableNMI();

	KeSetBootMessage("Configuring processors...");

	cpu[0] = new CPU();
	addChild(cpu[0]);
	cpu[0]->open(0, 0, vas);		//FIRST ARG IS CPU NUMBER
	
	KeSetBootMessage("Detecting numerical coprocessors...");
	HalInitialiseCoprocessor();

	KeSetBootMessage("Setting up multitasking...");
	setupMultitasking(KeFirstTask);
	return -1;
}

extern "C" size_t validateKey();
extern "C" int detectCPUID();
extern "C" size_t x87Detect();
extern "C" size_t sseDetect();
extern "C" size_t avxDetect();
extern "C" size_t x87Detect();

void Computer::detectFeatures()
{
	features.hasAPIC = false;
	features.hasCPUID = false;
	features.hasMSR = false;
	features.hasx87 = false;
	features.hasMMX = false;
	features.has3DNow = false;
	features.hasSSE = false;
	features.hasSSE2 = false;
	features.hasSSE3 = false;
	features.hasSSE41 = false;
	features.hasSSE42 = false;
	features.hasSSSE3 = false;
	features.hasAVX = false;
	features.hasAVX512 = false;
	features.hasNXBit = false;
	features.hasLongMode = false;
	features.hasMCE = false;
	features.hasCPUID = detectCPUID() ? true : false;

	if (features.hasCPUID) {
		features.hasMSR = CPU::cpuidCheckEDX(CPUID_FEAT_EDX_MSR);
		features.hasSSE2 = CPU::cpuidCheckEDX(CPUID_FEAT_EDX_SSE2);
		features.hasMCE = CPU::cpuidCheckEDX(CPUID_FEAT_EDX_MCE);
		features.hasMMX = CPU::cpuidCheckEDX(CPUID_FEAT_EDX_MMX);

		if ((sysBootSettings & 1) || (sysBootSettings & 1024)) {
			features.hasAPIC = false;
		} else {
			features.hasAPIC = CPU::cpuidCheckEDX(CPUID_FEAT_EDX_APIC);
		}

		if (features.hasAPIC && !features.hasMSR) {
			features.hasAPIC = false;
		}

		//features.hasAPIC = false;

		bool ecxCanReturnFeatures = true;
		ecxCanReturnFeatures = false;

		if (ecxCanReturnFeatures) {
			features.hasSSE3 = CPU::cpuidCheckECX(CPUID_FEAT_ECX_SSE3);
			features.hasSSSE3 = CPU::cpuidCheckECX(CPUID_FEAT_ECX_SSSE3);
			features.hasSSE41 = CPU::cpuidCheckECX(CPUID_FEAT_ECX_SSE4_1);
			features.hasSSE42 = CPU::cpuidCheckECX(CPUID_FEAT_ECX_SSE4_2);
		}

		size_t eax, ebx, ecx, edx;
		CPU::cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
		if (eax >= 0x80000001) {
			CPU::cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			features.has3DNow = edx & (1 << 31);
			features.hasLongMode = edx & (1 << 29);
			features.hasNXBit = edx & (1 << 20);
		}
	}

	if (sysBootSettings & 1024) {
		features.hasACPI = false;
	}

	features.hasx87 = x87Detect();
	if (features.hasx87) {
		features.hasSSE = sseDetect();
	}
	if (features.hasSSE) {
		features.hasAVX = avxDetect();
	}
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
	computer->root->sleep();
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
		
	//lwip_init();

	KeSetBootMessage("Getting ready...");
	Thr::executeDLL(Thr::loadDLL("C:/Banana/System/system.dll"), computer);

	while (1) {
		blockTask(TaskState::Paused);
	}
}