#include "core/computer.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "core/physmgr.hpp"
#include "thr/elf.hpp"
#include "core/idle.hpp"
#include "reg/registry.hpp"
#include "hw/acpi.hpp"
#include "hal/clock.hpp"
#include "hw/cpu.hpp"
#include "hw/smp.hpp"
#include "krnl/hal.hpp"
#include "hal/vcache.hpp"
#include "fs/vfs.hpp"
#include "vm86/vm8086.hpp"
#include "krnl/powctrl.hpp"
#include "krnl/hal.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define PORT_SYSTEM_CONTROL_A	0x92
#define PORT_SYSTEM_CONTROL_B	0x61

#define PORT_CMOS_BASE			0x70	

namespace Krnl
{
	bool schedulingOn = false;
	bool preemptionOn = false;

	Computer* computer;
}

Computer::Computer() : Device("Computer")
{
	deviceType = DeviceType::Bus;
	parent = nullptr;

	features.hasACPI = true;

	//CMOS
	ports[noPorts].rangeStart = PORT_CMOS_BASE;
	ports[noPorts].rangeLength = 2;
	ports[noPorts++].width = 0;

	//SYSTEM CONTROL PORT A
	ports[noPorts].rangeStart = PORT_SYSTEM_CONTROL_A;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	//SYSTEM CONTROL PORT B
	ports[noPorts].rangeStart = PORT_SYSTEM_CONTROL_B;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;
}

void Computer::setBootMessage(const char* message)
{
	
}

int Computer::open(int a, int b, void* vas)
{
	Krnl::setBootMessage("Detecting processor information...");

	VgaText::hiddenOut = false;

	if (!(sysBootSettings & 4)) {
		VgaText::hiddenOut = true;
	}

	Krnl::setBootMessage("Creating device tree...");
	root = new ACPI();
	addChild(root);

	detectFeatures();
	displayFeatures();
	enableNMI();

	Krnl::setBootMessage("Configuring processors...");

	cpu[0] = new CPU();
	addChild(cpu[0]);
	cpu[0]->open(0, 0, vas);		//FIRST ARG IS CPU NUMBER

	Hal::initialise();
	
	Krnl::setBootMessage("Detecting numerical coprocessors...");
	Hal::initialiseCoprocessor();

	Krnl::setBootMessage("Setting up multitasking...");
	setupMultitasking(Krnl::firstTask);
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

#ifdef JUMPER32
	features.hasCPUID = false;
#else
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

#endif
}


void Computer::displayFeatures()
{
	kprintf("Computer Features\n");
	kprintf("    APIC   - %s\n", features.hasAPIC ? "Yes" : "No");
	kprintf("    ACPI   - %s\n", features.hasACPI ? "Yes" : "No");
	kprintf("    CPUID  - %s\n", features.hasCPUID ? "Yes" : "No");
	kprintf("    MSR    - %s\n", features.hasMSR ? "Yes" : "No");
	kprintf("    x87    - %s\n", features.hasx87 ? "Yes" : "No");
	kprintf("    MMX    - %s\n", features.hasMMX ? "Yes" : "No");
	kprintf("    3DNow! - %s\n", features.has3DNow ? "Yes" : "No");
	kprintf("    SSE    - %s\n", features.hasSSE ? "Yes" : "No");
	kprintf("    SSE2   - %s\n", features.hasSSE2 ? "Yes" : "No");
	kprintf("    SSE3   - %s\n", features.hasSSE3 ? "Yes" : "No");
	kprintf("    SSSE3  - %s\n", features.hasSSSE3 ? "Yes" : "No");
	kprintf("    SSE4.1 - %s\n", features.hasSSE41 ? "Yes" : "No");
	kprintf("    SSE4.2 - %s\n", features.hasSSE42 ? "Yes" : "No");
	kprintf("    AVX    - %s\n", features.hasAVX ? "Yes" : "No");
	kprintf("    AVX512 - %s\n", features.hasAVX512 ? "Yes" : "No");
	kprintf("    MCE    - %s\n", features.hasMCE ? "Yes" : "No");
	kprintf("    x86-64 - %s\n", features.hasLongMode ? "Yes" : "No");
	kprintf("    NX bit - %s\n", features.hasNXBit ? "Yes" : "No");
	kprintf("\n");
}

uint64_t Computer::rdmsr(uint32_t msr_id)
{
	if (!features.hasMSR) {
		panic("RDMSR");
	}
#if PLATFORM_ID == 86
	uint64_t msr_value;
	asm volatile ("rdmsr" : "=A" (msr_value) : "c" (msr_id));
	return msr_value;
#elif PLATFORM_ID == 64
	uint32_t low, high;
	asm volatile (
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr_id)
		);
	return ((uint64_t) high << 32) | low;
#else
#error "Platform not supported for WRMSR"
#endif
}

void Computer::wrmsr(uint32_t msr_id, uint64_t msr_value)
{
	if (!features.hasMSR) {
		panic("WRMSR");
	}
#if PLATFORM_ID == 86
	asm volatile ("wrmsr" : : "c" (msr_id), "A" (msr_value));
#elif PLATFORM_ID == 64
	uint32_t low = msr_value & 0xFFFFFFFF;
	uint32_t high = msr_value >> 32;
	asm volatile (
		"wrmsr"
		:
	: "c"(msr_id), "a"(low), "d"(high)
		);
#else
#error "Platform not supported for WRMSR"
#endif
}

int Computer::close(int a, int b, void* c)
{
	root->closeAll();
	return root->close(a, 9999, c);
}

void Computer::shutdown()
{
	close(0, 0, 0);
}

void Computer::restart()
{
	close(1, 0, 0);
}

void Computer::sleep()
{
	root->sleep();
}

bool Computer::nmiEnabled()
{
	return nmi;
}

void Computer::enableNMI(bool enable)
{
	nmi = enable;
	readCMOS(0x10);		//dummy read to change the NMI settings
}

void Computer::disableNMI()
{
	enableNMI(false);
}

namespace Krnl
{
	void firstTask()
	{
		Krnl::setBootMessage("Enabling interrupts...");
		asm("sti");

		Krnl::setBootMessage("Starting core threads...");

		//setup up the core processes and threads we need
		Process* idleProcess = new Process(true, "Idle Process", kernelProcess);
		idleProcess->createThread(idleFunction, nullptr, 255);

		cleanerThread = kernelProcess->createThread(cleanerTaskFunction, nullptr, 122);

		schedulingOn = true;

		Krnl::setBootMessage("Initialising system components...");
		Vm::initialise8086();
		Fs::initVFS();

		Krnl::setBootMessage("Loading device drivers...");
		computer->root->open(0, 0, nullptr);

		Krnl::setBootMessage("Initialising system components...");
		Sys::loadSyscalls();
		Krnl::loadSystemEnv();
		Krnl::setupPowerManager();
		User::loadClockSettings(Reg::readIntWithDefault((char*) "country", (char*) "timezone", 58));
		
		Krnl::setBootMessage("Loading more device drivers...");
		computer->root->loadDriversForAll();

		Krnl::setBootMessage("Configuring processors...");
		Krnl::startCPUs();

		Krnl::setBootMessage("Getting ready...");
		Thr::executeDLL(Thr::loadDLL("C:/Banana/System/system.dll"), computer);

		while (1) {
			blockTask(TaskState::Paused);
		}
	}
}

uint8_t Computer::readCMOS(uint8_t reg)
{
	outb(PORT_CMOS_BASE + 0, reg | (nmi ? 0 : 0x80));
	return inb(PORT_CMOS_BASE + 1);
}

void Computer::writeCMOS(uint8_t reg, uint8_t val)
{
	outb(PORT_CMOS_BASE + 0, reg | (nmi ? 0 : 0x80));
	outb(PORT_CMOS_BASE + 1, val);
}

void Computer::handleNMI()
{
	uint8_t sysA = inb(PORT_SYSTEM_CONTROL_A);
	uint8_t sysB = inb(PORT_SYSTEM_CONTROL_B);

	kprintf("RECEIVED AN NMI\n");

	if (sysA & (1 << 4)) {
		panic("WATCHDOG NMI");
	}

	if (sysB & (1 << 6)) {
		panic("BUS ERROR");
	}

	if (sysB & (1 << 7)) {
		panic("MEMORY ERROR");
	}
}

void Computer::setDiskActivityLight(int disk, bool state)
{
	if (disk == 0 || disk == 1) {
		uint8_t sysA = inb(PORT_SYSTEM_CONTROL_A);
		sysA &= ~(0x40 << disk);
		sysA |= 0x40 << ((int) state);
		outb(PORT_SYSTEM_CONTROL_A, sysA);
	}
}
