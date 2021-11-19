#ifndef _VIRTMGR_HPP
#define _VIRTMGR_HPP

#define PAGE_NOT_PRESENT    0
#define PAGE_READONLY       0
#define PAGE_SUPERVISOR     0

#include <arch/hal.hpp>

#define PAGE_PRESENT        (1 << 0)
#define PAGE_WRITABLE       (1 << 1)
#define PAGE_USER           (1 << 2)
#define PAGE_CACHE_DISABLE  (1 << 4)
#define PAGE_ACCESSED		(1 << 5)
#define PAGE_DIRTY			(1 << 6)
#define PAGE_PAT		    HalPageWriteCombiningFlag
#define PAGE_GLOBAL			HalPageGlobalFlag
#define PAGE_COPY_ON_WRITE	(1 << 9)
#define PAGE_ALLOCATED      (1 << 10)
#define PAGE_SWAPPABLE      (1 << 11)

class VAS;
extern VAS* firstVAS;

namespace Virt
{
	extern char swapfileDrive;
	extern size_t swapfileSector;			//base LBA
	extern size_t swapfileLength;			//length is sectors
	extern int swapfileSectorsPerPage;
	extern size_t* swapfileBitmap;

	size_t swapIDToSector(size_t id);
	void freeSwapfilePage(size_t id);
	void allocateSwapfilePage(size_t* sectorOut, size_t* idOut);

	void freeKernelVirtualPages(size_t address);
	size_t allocateKernelVirtualPages(int pages);

	void virtualMemorySetup();

	static inline __attribute__((always_inline)) VAS* getAKernelVAS()
	{
		return firstVAS;
	}

	void setupPageSwapping(int megs);
}

extern "C" void KeEntryPoint();

class VAS {
private:
	friend void KeEntryPoint();
	VAS();
	bool specialFirstVAS;

protected:
	

public:
	bool supervisorVAS;

	size_t sbrk = 0;
	size_t evictionScanner = 0;
	
	size_t* pageDirectoryBase;
	size_t pageDirectoryBasePhysical;

	VAS(VAS* vas);
    VAS(bool kernel);
    ~VAS();
	void setCPUSpecific(size_t phys);

	size_t scanForEviction();
	bool tryLoadBackOffDisk(size_t faultAddr);

	void evict(size_t virt);

	size_t* getForeignPageTableEntry(bool secondSlot, size_t virt);
	size_t* getPageTableEntry(size_t virt);
	size_t virtualToPhysical(size_t virt);
	size_t allocatePages(int count, int flags);
	void freeAllocatedPages(size_t virt);
    void mapPage(size_t physicalAddr, size_t virtualAddr, int flags);
	size_t mapRange(size_t physicalAddr, size_t virtualAddr, int pages, int flags);

	void reflagRange(size_t virtualAddr, int pages, size_t andFlags, size_t orFlags);
	void setToWriteCombining(size_t virtualAddr, int pages);

	void mapOtherVASIn(bool secondSlot, VAS* other);
	void mapForeignPage(bool secondSlot, VAS* other, size_t physicalAddr, size_t virtualAddr, int flags);

	size_t allocateSharedMemoryWithKernel(size_t pageCount, size_t* krnlVirt);
	void freeSharedMemoryWithKernel(size_t vaddr, size_t krnlVirt);
};

extern "C" void mapVASFirstTime();


#endif
