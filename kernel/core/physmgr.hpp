
#ifndef _PHYSMGR_HPP_
#define _PHYSMGR_HPP_

#include <stdint.h>
#include <stddef.h>
#include "core/main.hpp"

namespace Phys
{
	extern int usablePages;
	extern int usedPages;
	extern size_t highestMem;

	extern bool forbidEvictions;

	void physicalMemorySetup(uint32_t highestUsedAddr);
	void freePage(size_t address);
	size_t allocatePage();
	size_t allocateContiguousPages(int pages);

	size_t allocateDMA(size_t size);
	void freeDMA(size_t addr, size_t size);

	//ONLY TO BE USED BY PHYSMEM AND VIRTMEM
	void setPageState(size_t pageNum, bool state);
}

#endif