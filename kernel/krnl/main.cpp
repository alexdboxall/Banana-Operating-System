
//
// Kernel entry point and the initial kernel task
//

#include <krnl/main.hpp>
#include <krnl/physmgr.hpp>
#include <krnl/virtmgr.hpp>
#include <krnl/kheap.hpp>
#include <krnl/computer.hpp>
#include <krnl/hal.hpp>
#include <krnl/bootmsg.hpp>
#include <krnl/atexit.hpp>
#include <krnl/bootflags.hpp>
#include <krnl/random.hpp>
#include <krnl/powctrl.hpp>
#include <krnl/idle.hpp>
#include <fs/symlink.hpp>
#include <fs/vfs.hpp>
#include <dbg/kconsole.hpp>
#include <thr/prcssthr.hpp>
#include <thr/elf.hpp>
#include <vm86/vm8086.hpp>

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// The main kernel thread's entry point. Initialises the main kernel subsystems.
/// 
/// Only designed to be started once as the initial task, and cannot be started as a
/// regular task or called as a function.
/// </summary>
void KeFirstTask()
{
	HalEnableInterrupts();
	HalEnableNMI();

	KeSetBootMessage("Starting core threads...");

	// Start the idle task
	Process* idleProcess = new Process(true, "Idle Process", kernelProcess);
	idleProcess->createThread(idleFunction, nullptr, 255);

	// Start the task termination cleanup thread
	cleanerThread = kernelProcess->createThread(cleanerTaskFunction, nullptr, 122);

	// These do not require the filesystem to be working
	KeSetBootMessage("Initialising system components...");
	keIsSchedulingOn = true;
	KeInitRand();
	Vm::initialise8086();
	Fs::initVFS();

	// Scan the device tree, which also sets up the filesystem
	KeSetBootMessage("Loading device drivers...");
	computer->root->open(0, 0, nullptr);

	// Now we have a filesystem, we can set up more complicated subsystems
	KeSetBootMessage("Initialising system components...");
	KeInitialiseSymlinks();
	KeLoadSystemEnv();
	KeSetupPowerManager();

	// Hand over control to the login task
	KeSetBootMessage("Getting ready...");
	KeLoadAndExecuteDriver("C:/Banana/System/system.dll", computer);

	// This thread now does not do anything actively
	while (1) {
		blockTask(TaskState::Paused);
	}
}

extern "C" void _init();			// global constructors (implemented in assembly)
//extern VAS* keFirstVAS;

/// <summary>
/// The entry point for the entire C/C++ kernel. It is reponsible for initialising the entire kernel.
/// </summary>
extern "C" void KeEntryPoint()
{
	KeInitialiseBootConfigurationFlags();

	// Sets up the first serial port for kernel debugging at 37400 baud
#ifdef KERNEL_DEBUG
	outb(0x3F8 + 1, 0x00);
	outb(0x3F8 + 3, 0x80);
	outb(0x3F8 + 0, 0x03); 
	outb(0x3F8 + 1, 0x00);
	outb(0x3F8 + 3, 0x03);
	outb(0x3F8 + 2, 0xC7);
	outb(0x3F8 + 4, 0x0B);
#endif

	kprintf("\n\nKERNEL HAS STARTED.\n");
	KeDisplaySplashScreen();

	// The bootloader passes us the highest address used by the kernel image and other boot time things
	// in address 0x524. This is then rounded up to the nearest page, and used as the lowest address we
	// can start allocating from.
	Phys::physicalMemorySetup(((*((uint32_t*) 0x524)) + 4095) & ~0xFFF);
	Virt::virtualMemorySetup();

	KeInitialiseAtexit();

	{
		// Due to the nested scope, the VAS initialisation will only occur when
		// we get to here. Reaching this declaration actually sets up the VAS.
		// This is required as the physical and virtual memory setup needs to be
		// done first.
		VAS vas;
		keFirstVAS = &vas;

		// Call global constructors
		_init();

		KeSetBootMessage("Configuring processors...");
		computer = new Computer();
		computer->open(0, 0, keFirstVAS);

		KeSetBootMessage("Detecting numerical coprocessors...");
		HalInitialiseCoprocessor();

		// Start the main kernel task, as well as the scheduler and multitasking subsystem
		// This function never returns.
		KeSetBootMessage("Setting up multitasking...");
		setupMultitasking(KeFirstTask);
	}

	// We should never get here.
}
