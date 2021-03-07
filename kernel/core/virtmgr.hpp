#ifndef _VIRTMGR_HPP
#define _VIRTMGR_HPP

#define PAGE_NOT_PRESENT    0
#define PAGE_READONLY       0
#define PAGE_SUPERVISOR     0

#define PAGE_PRESENT        (1 << 0)
#define PAGE_WRITABLE       (1 << 1)
#define PAGE_USER           (1 << 2)
#define PAGE_CACHE_DISABLE  (1 << 4)
#define PAGE_ACCESSED		(1 << 5)
#define PAGE_DIRTY			(1 << 6)
#define PAGE_GLOBAL		    (1 << 8)
#define PAGE_GUARD_PAGE     (1 << 9 | PAGE_NOT_PRESENT)
#define PAGE_SWAPPABLE      (1 << 9 | PAGE_PRESENT)
#define PAGE_ALLOCATED      (1 << 10)

class VAS;

namespace Virt
{
	void freeKernelVirtualPages(size_t address);
	size_t allocateKernelVirtualPages(int pages);
	void virtualMemorySetup();

	VAS* getAKernelVAS();

	void setupPageSwapping(int megs);
}

extern "C" void kernel_main();

class VAS {
private:
	friend void kernel_main();
	VAS();
	bool specialFirstVAS;

protected:

public:
	bool supervisorVAS;

	size_t sbrk = 0;
	
	size_t* pageDirectoryBase;
	size_t pageDirectoryBasePhysical;

	VAS(VAS* vas);
    VAS(bool kernel);
    ~VAS();
	void setCPUSpecific(size_t phys);

	size_t* getForeignPageTableEntry(bool secondSlot, size_t virt);
	size_t* getPageTableEntry(size_t virt);
	size_t virtualToPhysical(size_t virt);
	size_t allocatePages(int count, int flags);
	void freeAllocatedPages(size_t virt);
    void mapPage(size_t physicalAddr, size_t virtualAddr, int flags);
	size_t mapRange(size_t physicalAddr, size_t virtualAddr, int pages, int flags);

	void mapOtherVASIn(bool secondSlot, VAS* other);
	void mapForeignPage(bool secondSlot, VAS* other, size_t physicalAddr, size_t virtualAddr, int flags);
};

extern "C" void mapVASFirstTime();


#endif
