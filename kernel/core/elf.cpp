#include "core/elf.hpp"
#include "core/prcssthr.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "core/kheap.hpp"
#include "libk/string.h"
#include "core/physmgr.hpp"
#include "hw/cpu.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

bool allocateMemoryForTask(Process* prcss, File* file, size_t size, size_t virtualAddr, size_t additionalNullBytes)
{
	/*
	Basically, we get a physical page and map into the CURRENT VIRTUAL ADDRESS SPACE.
	We use that mapping to write the correct data to the page. Then, we map the same
	physical page to the new VAS using mapForeignPage.

	We do not save the mappings in the current VAS, and there is only a single 4KB spot where
	we map them in and do the copying (virtMappingSpot)
	
	We do not need to INVLPG or reload CR3 here, because this is only called on program load
	and CR3 will be set when this task is switched in for the first time.
	*/

	if ((virtualAddr & 0xFFF) && additionalNullBytes && !size) {
		virtualAddr += 0x1000;
		size -= 0x1000 - (virtualAddr & 0xFFF);
		virtualAddr &= ~0xFFF;
	}

	size_t pagesReq = (size + 4095) / 4096;
	size_t nullPagesReq = (additionalNullBytes + 4095) / 4096;
	size_t virtMappingSpot = Virt::allocateKernelVirtualPages(1);

	int actual;

	if (pagesReq) {

		for (size_t i = 0; i < pagesReq; ++i) {
			uint8_t buffer[4096];

			FileStatus res = file->read(size > 4096 ? 4096 : size, (void*) buffer, &actual);
			if (res != FileStatus::Success) {
				kprintf("allocate memory for task failed (A)! 0x%X\n", (int) res);
				Virt::freeKernelVirtualPages(virtMappingSpot);
				return false;
			}

			lockScheduler();
			size_t addr = Phys::allocatePage();
			currentTaskTCB->processRelatedTo->vas->mapPage(addr, virtMappingSpot, PAGE_PRESENT | PAGE_USER | PAGE_WRITABLE);

			//TODO: you can move mapOtherVASIn outside of the loop, but if someone else maps a VAS into the same slot the system will crash
			//		(add locking to mapOtherVASIn?, e.g. releaseOtherVAS(bool slot) )
			currentTaskTCB->processRelatedTo->vas->mapOtherVASIn(false, prcss->vas);
			currentTaskTCB->processRelatedTo->vas->mapForeignPage(false, prcss->vas, addr, virtualAddr, PAGE_PRESENT | PAGE_ALLOCATED | PAGE_USER | PAGE_WRITABLE);

			memcpy((void*) virtMappingSpot, (const void*) buffer, 4096);

			unlockScheduler();

			size -= 4096;
			virtualAddr += 4096;
		}
	}

	if (nullPagesReq) {
		lockScheduler();
		currentTaskTCB->processRelatedTo->vas->mapOtherVASIn(false, prcss->vas);

		for (size_t i = 0; i < nullPagesReq; ++i) {
			size_t addr = Phys::allocatePage();
			currentTaskTCB->processRelatedTo->vas->mapPage(addr, virtMappingSpot, PAGE_PRESENT | PAGE_USER | PAGE_WRITABLE);
			currentTaskTCB->processRelatedTo->vas->mapForeignPage(false, prcss->vas, addr, virtualAddr, PAGE_PRESENT | PAGE_ALLOCATED | PAGE_USER | PAGE_WRITABLE);
			memset((void*) virtMappingSpot, 0, 4096);
			virtualAddr += 4096;
		}

		unlockScheduler();
	}

	Virt::freeKernelVirtualPages(virtMappingSpot);

	return true;
}


bool loadProgramIntoMemory(Process* p, const char* filename)
{
	File* f = new File(filename, p);
	FileStatus status = f->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		return false;
	}

	int actual = 0;
	ELFHeader* elf = (ELFHeader*) malloc(sizeof(ELFHeader));

	status = f->read(sizeof(ELFHeader), (void*) elf, &actual);
	if (status != FileStatus::Success) {
		return false;
	}

	if (elf->identify[0] == 0x7F && elf->identify[1] == 'E' && elf->identify[2] == 'L' && elf->identify[3] == 'F') {
	} else {
		return false;
	}

	//LOAD SECTION HEADERS
	if (elf->shOffset == 0) {
		return false;
	}

	status = f->seek(elf->shOffset);
	if (status != FileStatus::Success) {
		return false;
	}


	size_t entryPoint = elf->entry;
	size_t relocationPoint = 0x10000000;

#if PLATFORM_ID == 86
	ELFSectionHeader32* sectHeaders = (ELFSectionHeader32*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#else
	ELFSectionHeader64* sectHeaders = (ELFSectionHeader64*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#endif


	//LOAD PROGRAM HEADERS
	if (!elf->phOffset) {
		return false;
	}

	status = f->seek(elf->phOffset);
	if (status != FileStatus::Success) {
		return false;
	}

	size_t highest = 0;

#if PLATFORM_ID == 86
	ELFProgramHeader32* progHeaders = (ELFProgramHeader32*) malloc(elf->phNum * elf->phSize);
	f->read(elf->phNum * elf->phSize, (void*) progHeaders, &actual);

#else
	ELFProgramHeader64* progHeaders = (ELFProgramHeader64*) malloc(elf->phNum * elf->phSize);
	f->read(elf->phNum * elf->phSize, (void*) progHeaders, &actual);

#endif

	//LOOK AT PROG SEGMENTS

	//this whole thing isn't loading the file from the disk right. the code is sound, it's just the vfs
	//however! the vfs_file_t might be in bad form before it gets here...

	for (uint16_t i = 0; i < elf->phNum; ++i) {
		size_t addr = (progHeaders + i)->p_vaddr;
		size_t fileOffset = (progHeaders + i)->p_offset;
		size_t size = (progHeaders + i)->p_filsz;

		if ((progHeaders + i)->type == PT_LOAD) {
			//seek to correct part then load into paging structures
			status = f->seek(fileOffset);
			if (status != FileStatus::Success) {
				kprintf("OOPS 7\n");
				return false;
			}

			//kprintf("allocateMemoryForTask 0x%X 0x%X 0x%X\n", size, addr, (progHeaders + i)->p_memsz - (progHeaders + i)->p_filsz);
			if (size >= 65536) {
				//size = 64000;
			}

			allocateMemoryForTask(p, f, size, addr, (progHeaders + i)->p_memsz - (progHeaders + i)->p_filsz);

			if (addr + size > highest) {
				highest = addr + size;
			}
		}
	}

	highest /= 4096;
	highest += 1;
	highest *= 4096;

	p->usermodeEntryPoint = entryPoint;

	p->vas->sbrk = highest;	//for future heap allocations

	free(sectHeaders);
	free(elf);
	free(progHeaders);

	f->close();

	return true;
}

void runtimeReferenceHelper()
{
	kprintf("Runtime reference helper called!\n");
	asm("cli");
	while (1);
}

int nextDLLSymbolIndex = 0;

//this means 32 drivers can have their symbols loaded into the kernel table
void* kernelSymbolTable[32];
void* kernelStringTable[32];
int kernelSymbols[32];

//this is REALLY slow!
size_t getAddressOfKernelSymbol(const char* name)
{
	for (int j = 0; j < nextDLLSymbolIndex; ++j) {
		ELFSymbolTable32* sym = (ELFSymbolTable32*) kernelSymbolTable[j];

		for (int i = 0; i < kernelSymbols[j]; ++i) {
			if (!strcmp(((char*) kernelStringTable[j]) + sym->st_name, name)) {
				return sym->st_value;
			}
			++sym;
		}

	}

	return 0;
}

bool loadKernelSymbolTable(const char* filename)
{
	Process* p = kernelProcess;

	File* f = new File(filename, p);
	FileStatus status = f->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		return false;
	}

	int actual = 0;
	ELFHeader* elf = (ELFHeader*) malloc(sizeof(ELFHeader));

	status = f->read(sizeof(ELFHeader), (void*) elf, &actual);
	if (status != FileStatus::Success) {
		panic("KERNEL FILE CAN'T LOAD");
		return false;
	}

	if (elf->identify[0] == 0x7F && elf->identify[1] == 'E' && elf->identify[2] == 'L' && elf->identify[3] == 'F') {
	} else {
		panic("KERNEL FILE CAN'T LOAD");
		return false;
	}

	//LOAD SECTION HEADERS
	if (elf->shOffset == 0) {
		panic("KERNEL FILE CAN'T LOAD");
		return false;
	}

	status = f->seek(elf->shOffset);
	if (status != FileStatus::Success) {
		panic("KERNEL FILE CAN'T LOAD");
		return false;
	}

#if PLATFORM_ID == 86
	ELFSectionHeader32* sectHeaders = (ELFSectionHeader32*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#else
	ELFSectionHeader64* sectHeaders = (ELFSectionHeader64*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#endif

	size_t symTabOffset = 0;			//offset into file of .symtab
	size_t symTabLength = 0;			//length of .symtab

	size_t stringTabOffset = 0;
	size_t stringTabLength = 0;

	//LOOK AT SECTIONS
	for (uint16_t i = 0; i < elf->shNum; ++i) {
		size_t fileOffset = (sectHeaders + i)->sh_offset;
		size_t addr = (sectHeaders + elf->strtabIndex)->sh_offset + (sectHeaders + i)->sh_name;

		//vfs_seek(file, addr);
		f->seek(addr);

		char namebuffer[32];
		memset(namebuffer, 0, 32);

		int actual;
		f->read(31, namebuffer, &actual);

		if (!strcmp(namebuffer, ".symtab")) {
			symTabOffset = fileOffset;
			symTabLength = (sectHeaders + i)->sh_size;
		}
		if (!strcmp(namebuffer, ".strtab")) {
			stringTabOffset = fileOffset;
			stringTabLength = (sectHeaders + i)->sh_size;
		}
	}

	if (!symTabOffset) {
		panic("KERNEL TABLE HAS NO TABLE");
	}
	if (!stringTabOffset) {
		panic("KERNEL TABLE HAS NO TABLE");
	}

	f->seek(symTabOffset);

#if PLATFORM_ID == 86
	ELFSymbolTable32* symbolTab = (ELFSymbolTable32*) malloc(symTabLength);
	f->read(symTabLength, (void*) symbolTab, &actual);
#else

#endif

	void* stringTab = (void*) malloc(stringTabLength);

	f->read(symTabLength, (void*) stringTab, &actual);
	kernelSymbols[nextDLLSymbolIndex] = symTabLength / sizeof(ELFSymbolTable32);

	f->seek(stringTabOffset);
	f->read(stringTabLength, (void*) stringTab, &actual);


	f->close();
	free(sectHeaders);
	free(elf);

	kernelSymbolTable[nextDLLSymbolIndex] = (void*) symbolTab;
	kernelStringTable[nextDLLSymbolIndex++] = (void*) stringTab;

	return true;
}

extern "C" unsigned long __udivdi3(unsigned long, unsigned long);
extern "C" long __divdi3(long, long);
extern "C" unsigned long __umoddi3(unsigned long, unsigned long);
extern "C" long __moddi3(long, long);

bool loadDriverIntoMemory(const char* filename, size_t address)
{
	Process* p = kernelProcess;

	File* f = new File(filename, p);
	FileStatus status = f->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		return false;
	}

	int actual = 0;
	ELFHeader* elf = (ELFHeader*) malloc(sizeof(ELFHeader));

	status = f->read(sizeof(ELFHeader), (void*) elf, &actual);
	if (status != FileStatus::Success) {
		return false;
	}

	if (elf->identify[0] == 0x7F && elf->identify[1] == 'E' && elf->identify[2] == 'L' && elf->identify[3] == 'F') {
	} else {
		return false;
	}

	//LOAD SECTION HEADERS
	if (elf->shOffset == 0) {
		return false;
	}

	status = f->seek(elf->shOffset);
	if (status != FileStatus::Success) {
		return false;
	}

	size_t entryPoint = elf->entry;
	size_t relocationPoint = address;
	
#if PLATFORM_ID == 86
	ELFSectionHeader32* sectHeaders = (ELFSectionHeader32*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#else
	ELFSectionHeader64* sectHeaders = (ELFSectionHeader64*) malloc(elf->shNum * elf->shSize);
	f->read(elf->shNum * elf->shSize, (void*) sectHeaders, &actual);
#endif

	//LOAD PROGRAM HEADERS
	if (!elf->phOffset) {
		return false;
	}

	status = f->seek(elf->phOffset);
	if (status != FileStatus::Success) {
		return false;
	}

#if PLATFORM_ID == 86
	ELFProgramHeader32* progHeaders = (ELFProgramHeader32*) malloc(elf->phNum * elf->phSize);
	f->read(elf->phNum * elf->phSize, (void*) progHeaders, &actual);

#else
	ELFProgramHeader64* progHeaders = (ELFProgramHeader64*) malloc(elf->phNum * elf->phSize);
	f->read(elf->phNum * elf->phSize, (void*) progHeaders, &actual);

#endif

	//LOOK AT PROG SEGMENTS

	for (uint16_t i = 0; i < elf->phNum; ++i) {
		size_t addr = (progHeaders + i)->p_vaddr;
		size_t fileOffset = (progHeaders + i)->p_offset;
		size_t size = (progHeaders + i)->p_filsz;

		if ((progHeaders + i)->type == PT_LOAD) {
			status = f->seek(fileOffset);
			if (status != FileStatus::Success) {
				return false;
			}

			int actu;
			f->read(size, (void*) (addr - entryPoint + relocationPoint), &actu);
			memset((void*) (addr - entryPoint + relocationPoint + size), 0, (progHeaders + i)->p_memsz - (progHeaders + i)->p_filsz);
		}
	}

	size_t relTextOffset = 0;			//offset into file of .rel.text
	size_t relTextLength = 0;			//length of .rel.text
	size_t symTabOffset = 0;			//offset into file of .symtab
	size_t symTabLength = 0;			//length of .symtab
	size_t strTabLength = 0;			//length of .symtab
	size_t strTabOffset = 0;			//length of .symtab

	//LOOK AT SECTIONS
	for (uint16_t i = 0; i < elf->shNum; ++i) {
		size_t fileOffset = (sectHeaders + i)->sh_offset;
		size_t addr = (sectHeaders + elf->strtabIndex)->sh_offset + (sectHeaders + i)->sh_name;

		//vfs_seek(file, addr);
		f->seek(addr);

		char namebuffer[32];
		memset(namebuffer, 0, 32);

		int actual;
		f->read(31, namebuffer, &actual);
		
		if (!strcmp(namebuffer, ".rel.text")) {
			relTextOffset = fileOffset;
			relTextLength = (sectHeaders + i)->sh_size;
		}
		if (!strcmp(namebuffer, ".symtab")) {
			symTabOffset = fileOffset;
			symTabLength = (sectHeaders + i)->sh_size;
		}
		if (!strcmp(namebuffer, ".strtab")) {
			strTabOffset = fileOffset;
			strTabLength = (sectHeaders + i)->sh_size;
		}
	}

	f->seek(symTabOffset);

#if PLATFORM_ID == 86
	ELFSymbolTable32* symbolTab = (ELFSymbolTable32*) malloc(symTabLength);
	f->read(symTabLength, (void*) symbolTab, &actual);

#else

#endif

	char* stringTab = (char*) malloc(strTabLength);

	f->seek(strTabOffset);
	f->read(strTabLength, (void*) stringTab, &actual);

	if (relTextOffset) {
		int entries = relTextLength / (sizeof(size_t) * 2);
		kprintf("%d relocation entries.\n", entries);

		f->seek(relTextOffset);

		size_t* ptr = (size_t*) malloc(relTextLength);
		size_t* optr = ptr;

		int act;
		f->read(relTextLength, ptr, &act);
		kprintf("relTextLength = %d, actually read in %d bytes\n", relTextLength, act);

		for (int i = 0; i < entries; ++i) {
			uint32_t pos = *ptr++;
			uint32_t info = *ptr++;

			uint8_t type = info & 0xFF;
			uint32_t symbolNum = info >> 8;

			size_t addr = symbolTab[symbolNum].st_value;

			bool dynamic = false;
			if (addr == 0) {
				addr = getAddressOfKernelSymbol(((char*) stringTab) + symbolTab[symbolNum].st_name);
				dynamic = true;
				if (addr == 0) {
					if (!strcmp(((char*) stringTab) + symbolTab[symbolNum].st_name, "__udivdi3")) {
						addr = (size_t) __udivdi3;
					} else if (!strcmp(((char*) stringTab) + symbolTab[symbolNum].st_name, "__divdi3")) {
						addr = (size_t) __divdi3;
					} else if (!strcmp(((char*) stringTab) + symbolTab[symbolNum].st_name, "__umoddi3")) {
						addr = (size_t) __umoddi3;
					} else if (!strcmp(((char*) stringTab) + symbolTab[symbolNum].st_name, "__moddi3")) {
						addr = (size_t) __moddi3;
					}

					if (addr == 0) {
						kprintf("SYMBOL: %s\n", ((char*) stringTab) + symbolTab[symbolNum].st_name);
						char msg[256];
						strcpy(msg, "UNDEFINED DLL SYMBOL '");
						strcat(msg, ((char*) stringTab) + symbolTab[symbolNum].st_name);
						strcat(msg, "'");
						panic(msg);
					}
				}
			}

			kprintf("SYMBOL: %s\n", ((char*) stringTab) + symbolTab[symbolNum].st_name);

			if (type == 1 && sizeof(size_t) == 4) {			//R_386_32
				uint32_t* entry = (uint32_t*) (pos - entryPoint + relocationPoint);
				uint32_t x;
				if (dynamic) {
					x = addr + *entry;
				} else {
					x = addr - entryPoint + relocationPoint + *entry;
				}
				kprintf("R_386_32	Modifying symbol 0x%X at 0x%X to become 0x%X\n", *entry, entry, x);
				kprintf("addr 0x%X entryPoint 0x%X reloc 0x%X *entry 0x%X\n", addr, entryPoint, relocationPoint, *entry);
				kprintf("dynamic: %d\n", dynamic);
				*entry = x;

			} else if (type == 2 && sizeof(size_t) == 4) {			//R_386_PC32
				uint32_t* entry = (uint32_t*) (pos - entryPoint + relocationPoint);
				uint32_t x;

				if (dynamic) {
					x = addr - pos + *entry + entryPoint - relocationPoint;
				} else {
					x = addr - pos + *entry;
				}
				kprintf("R_386_PC32	Modifying symbol 0x%X at 0x%X to become 0x%X\n", *entry, entry, x);
				kprintf("addr 0x%X entryPoint 0x%X reloc 0x%X *entry 0x%X\n", addr, entryPoint, relocationPoint, *entry);
				*entry = x;

			} else {
				kprintf("TYPE 0x%X\n", type);
				panic("UNKNOWN RELOCATION TYPE");

			}
		}

		free(optr);
	}

	f->close();

	free(sectHeaders);
	free(elf);
	free(progHeaders);

	return true;
}

size_t loadDLL(const char* name)
{
	kprintf("loading dll: %s\n", name);
	uint64_t siz;
	bool dir;

	File* f = new File(name, kernelProcess);
	if (!f) {
		char msg[256];
		strcpy(msg, "COULD NOT LOAD DLL '");
		strcat(msg, name);
		strcat(msg, "'");
		panic(msg);
	}
	FileStatus status = f->stat(&siz, &dir);
	if (dir || !siz) {
		char msg[256];
		strcpy(msg, "COULD NOT LOAD DLL '");
		strcat(msg, name);
		strcat(msg, "'");
		panic(msg);
	}
	delete f;

	size_t addr = (size_t) malloc(siz);

	kprintf("Loaded driver to address 0x%X\n", addr);

	loadDriverIntoMemory(name, addr);
	return addr;
}

void executeDLL(size_t startAddr, void* parentDevice)
{
	reinterpret_cast<int(*)(void*)>(startAddr)(parentDevice);
}