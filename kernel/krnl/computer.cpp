
//
// The root device in the device tree
//

#include <krnl/computer.hpp>
#include <krnl/physmgr.hpp>
#include <krnl/idle.hpp>
#include <krnl/powctrl.hpp>
#include <krnl/hal.hpp>
#include <hw/acpi.hpp>
#include <hw/cpu.hpp>
#include <hal/vcache.hpp>
#include <hal/clock.hpp>
#include <fs/symlink.hpp>
#include <thr/elf.hpp>
#include <thr/prcssthr.hpp>
#include <sys/syscalls.hpp>

#include <drv/device.hpp>

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


bool keIsSchedulingOn = false;
bool keIsPreemptionOn = false;

Computer* computer;

Computer::Computer() : Device("Computer")
{
	deviceType = DeviceType::Bus;
	parent = nullptr;
}

extern "C" {
#include <libk/math.h>
}

int Computer::open(int a, int b, void* vas)
{
	if (computer != this) {
		KePanic("ASSERTION FAILED: MULTIPLE Computer OBJECTS");
	}

	cpu[0] = new CPU();
	cpu[0]->open(0, 0, vas);		//FIRST ARG IS CPU NUMBER

	KeSetBootMessage("Creating device tree...");
	KeSetupDeviceTree();
	KePrintDeviceTree();

	root = new ACPI();
	addChild(root);
	addChild(cpu[0]);
	
	return -1;
}

int Computer::close(int a, int b, void* c)
{
	return -1;
}


