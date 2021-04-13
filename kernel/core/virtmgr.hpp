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
#define PAGE_PAT		    (1 << 7)
#define PAGE_GLOBAL		    (1 << 8)

#define PAGE_ALLOCATED      (1 << 10)
#define PAGE_SWAPPABLE      (1 << 11)
// (1 << 9) is free to use for anything you want 

class VAS;

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
	void swappingSetup();

	VAS* getAKernelVAS();
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

	size_t evictionScanner = 0;
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

	void reflagRange(size_t virtualAddr, int pages, int andFlags, int orFlags);
	void setToWriteCombining(size_t virtualAddr, int pages);

	void mapOtherVASIn(bool secondSlot, VAS* other);
	void mapForeignPage(bool secondSlot, VAS* other, size_t physicalAddr, size_t virtualAddr, int flags);
};

extern "C" void mapVASFirstTime();


#endif
