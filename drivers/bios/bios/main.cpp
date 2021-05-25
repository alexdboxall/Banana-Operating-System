#include <stdint.h>

void start();
void begin()
{
	start();
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/computer.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

namespace Krnl
{
	extern void (*biosPanicHandler)();
}

bool vgamono = false;
size_t VGA_TEXT_MODE_ADDRESS = 0xC20B8000;



BIOS::BIOS(): Device ("Legacy BIOS")
{
	//claim ports
	/*ports[noPorts].rangeStart = ?;
	ports[noPorts].rangeLength = ?;
	ports[noPorts++].width = 0;*/

	//claim memory
	memory[noMems].rangeStart = 0x400;
	memory[noMems++].rangeLength = 0x100;

	memory[noMems].rangeStart = 0xC0000;
	memory[noMems++].rangeLength = 0x40000;

	//actually, not all of this is claimed by the BIOS, and Banana actually allocates part of this
	memory[noMems].rangeStart = 0x80000;
	memory[noMems++].rangeLength = 0x20000;
}

void start()
{
	BIOS* dev = new BIOS();
	Krnl::computer->addChild(dev);
	setupTextMode();
}


int BIOS::open(int, int, void*)
{
	return 0;
}

int BIOS::close(int, int, void*)
{
	return 0;
}
