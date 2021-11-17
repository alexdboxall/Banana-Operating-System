#include "thr/prcssthr.hpp"
#include "krnl/computer.hpp"
#include "sys/syscalls.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Loads a kernel-mode dynamic link library or driver.
/// </summary>
/// <remark>
/// Loading dynamic link libraries or drivers which have already been loaded could cause system instability.
/// </remark>
/// <param name="ebx">The filename to load.</param>
/// <returns>Returns zero on success, or non-zero on failure.</returns>
/// 
uint64_t SysLoadDLL(regs* r)
{
	//check for invalid pointer
	if (!r->ebx) {
		return 1;
	}

	//create the file object
	File* f = new File((char*) r->ebx, currentTaskTCB->processRelatedTo);
	if (!f) {
		return 2;
	}

	//ensure the file exists
	if (!f->exists()) {
		delete f;
		return 3;
	}

	//we can close the file now
	delete f;

	//try loading the DLL as a non-critical driver
	//stange notation here because we are calling the 'other' loadDLL()
	size_t addr = Thr::loadDLL((char*) r->ebx, false);

	//check for failure
	if (!addr) {
		return 4;
	}

	//execute the DLL
	Thr::executeDLL(addr, computer);

	return 0;
}