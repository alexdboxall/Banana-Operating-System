#pragma once

#include <thr/elf2.hpp>
#include <thr/elf.hpp>
#include <thr/prcssthr.hpp>
#include <krnl/physmgr.hpp>
#include <krnl/virtmgr.hpp>
#include <krnl/kheap.hpp>
#include <libk/string.h>
#include <krnl/physmgr.hpp>
#include <hw/cpu.hpp>
#include <krnl/unaligned.hpp>
#include <krnl/resolve.hpp>
#include <fs/vfs.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Thr
{
	size_t getAddressOfKernelSymbol(const char* name);
}

size_t KeLoadDriver(const char* filepath)
{
	kprintf("\n\nloading driver: %s\n", filepath);

	uint64_t siz;
	bool dir;

	File* f = new File(filepath, kernelProcess);
	if (!f) {
		return 0;
	}

	FileStatus status = f->stat(&siz, &dir);

	if (dir || !siz) {
		return 0;
	}

	size_t addr = (size_t) Virt::getAKernelVAS()->allocatePages((siz + 4095) / 4096, PAGE_PRESENT | PAGE_SUPERVISOR | PAGE_WRITABLE);
	kprintf("@<<: %s %X\n", filepath, addr);

	status = f->open(FileOpenMode::Read);
	if (status != FileStatus::Success) {
		delete f;
		return 0;
	}

	uint8_t* loc = (uint8_t*) malloc(siz);
	int br;
	f->read(siz, loc, &br);
	f->close();

	size_t entryPoint = KeLoadELF(loc, true, (size_t) addr);

	int used = 0;
	int nnot = 0;
	for (size_t i = 0; i < (siz + 4095) / 4096; ++i) {
		size_t* ptentry = Virt::getAKernelVAS()->getPageTableEntry(addr + i * 4096);
		if (!(*ptentry & (PAGE_ACCESSED | PAGE_DIRTY))) {
			Phys::freePage(*ptentry & ~0xFFF);
		}
	}

	return entryPoint;
}

bool KeIsELFValid(Elf32_Ehdr* elfHeader)
{
	// check for ELF signature
	if (elfHeader->e_ident[EI_MAG0] != ELFMAG0) return false;
	if (elfHeader->e_ident[EI_MAG1] != ELFMAG1) return false;
	if (elfHeader->e_ident[EI_MAG2] != ELFMAG2) return false;
	if (elfHeader->e_ident[EI_MAG3] != ELFMAG3) return false;

	// check for other things
	//if (elfHeader->e_ident[EI_CLASS] != ELFCLASS32) return false;
	//if (elfHeader->e_ident[EI_DATA] != ELFDATA2LSB) return false;
	//if (elfHeader->e_machine != EM_386) return false;

	return true;
}

Elf32_Shdr* KeGetELFSectionHeader(uint8_t* data, int index)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;
	Elf32_Shdr* sectionHeaders = (Elf32_Shdr*) (data + elfHeader->e_shoff);
	return sectionHeaders + index;
}

Elf32_Phdr* KeGetELFProgramHeader(uint8_t* data, int index)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;
	Elf32_Phdr* programHeaders = (Elf32_Phdr*) (data + elfHeader->e_phoff);
	return programHeaders + index;
}

char* KeLookupELFString(uint8_t* data, int offset)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;

	if (elfHeader->e_shstrndx == SHN_UNDEF) {
		return nullptr;
	}

	char* stringTable = (char*) (data + KeGetELFSectionHeader(data, elfHeader->e_shstrndx)->sh_offset);
	if (stringTable == nullptr) {
		return nullptr;
	}

	return stringTable + offset;
}


size_t KeLoadELFProgramHeaders(uint8_t* data, bool relocate, size_t relocationPoint) {
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;
	
	size_t entryPoint = elfHeader->e_entry;
	size_t highestUsedAddress = entryPoint;		// used for SBRK

	for (int i = 0; i < elfHeader->e_phnum; ++i) {
		Elf32_Phdr* progHeader = KeGetELFProgramHeader(data, i);

		size_t address = progHeader->p_vaddr;
		size_t offset = progHeader->p_offset;
		size_t size = progHeader->p_filesz;
		size_t zerosize = progHeader->p_memsz;
		size_t type = progHeader->p_type;

		if (type == PHT_LOAD) {
			if (!relocate) {
				KePanic("elf2 doesn't support normal programs yet");

				// allocateMemoryForTask(p, f, size, addr, (progHeaders + i)->p_memsz - (progHeaders + i)->p_filsz);
				
				if (address + size + zerosize > highestUsedAddress) {
					highestUsedAddress = address + size + zerosize;
				}

			} else {
				memcpy((void*) (address + relocationPoint - entryPoint), (const void*) (data + offset), size);
				memset((void*) (address + relocationPoint - entryPoint + size), 0, zerosize - size);
			}
		}
	}

	return highestUsedAddress;
}

#define ELF32_R_SYM(INFO)		((INFO) >> 8)
#define ELF32_R_TYPE(INFO)		((uint8_t)(INFO))

#define DO_386_32(S, A)			((S) + (A))
#define DO_386_RELATIVE(B, A)	((B) + (A))
#define DO_386_PC32(S, A, P)	((S) + (A) - (P))

size_t KeGetELFSymbolValue(uint8_t* data, int table, int index, bool* error, size_t relocationPoint, size_t entryPoint)
{
	*error = false;

	if (table == SHN_UNDEF || index == SHN_UNDEF) {
		*error = true;
		return 0;
	}

	Elf32_Shdr* symbolTable = KeGetELFSectionHeader(data, table);

	size_t symbolTableEntries = symbolTable->sh_size / symbolTable->sh_entsize;
	if (index >= symbolTableEntries) {
		*error = true;
		return 0;
	}

	Elf32_Sym* symbol = ((Elf32_Sym*) (data + symbolTable->sh_offset)) + index;

	if (symbol->st_shndx == SHN_UNDEF) {
		// external symbol (i.e. from the kernel)

		Elf32_Shdr* stringTable = KeGetELFSectionHeader(data, symbolTable->sh_link);
		const char* name = (const char*) (data + stringTable->sh_offset + symbol->st_name);

		size_t target = Thr::getAddressOfKernelSymbol(name);

		// TODO: combine compatibility lookups into getAddressOfKernelSymbol

		if (target == 0) {
			if (!(ELF32_ST_BIND(symbol->st_info) & STB_WEAK)) {
				*error = true;
			}

			kprintf("... not defined int the kernel.\n");

			return 0;

		} else {
			return target;
		}

	} else if (symbol->st_shndx == SHN_ABS) {
		return symbol->st_value;

	} else {
		Elf32_Shdr* target = KeGetELFSectionHeader(data, symbol->st_shndx);
		return symbol->st_value + (relocationPoint - entryPoint);
	}
}

bool KePerformRelocation(uint8_t* data, size_t relocationPoint, Elf32_Shdr* section, Elf32_Rel* relocationTable)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;
	Elf32_Shdr* target = KeGetELFSectionHeader(data, section->sh_info);

	size_t entryPoint = elfHeader->e_entry;

	size_t addrK = (size_t) relocationPoint - entryPoint + relocationTable->r_offset;
	size_t* ref = (size_t*) addrK;

	int symbolValue = 0;
	if (ELF32_R_SYM(relocationTable->r_info) != SHN_UNDEF) {
		bool error = false;
		symbolValue = KeGetELFSymbolValue(data, section->sh_link, ELF32_R_SYM(relocationTable->r_info), &error, relocationPoint, entryPoint);
		if (error) {
			return false;
		}
	}
	
	int type = ELF32_R_TYPE(relocationTable->r_info);
	if (type == R_386_32) {
		*ref = DO_386_32(symbolValue, *ref);

	} else if (type == R_386_PC32) {
		*ref = DO_386_PC32(symbolValue, *ref, (size_t) ref);

	} else if (type == R_386_RELATIVE) {
		*ref = DO_386_RELATIVE((relocationPoint - entryPoint), *ref);

	} else {
		return false;
	}

	return true;
}

bool KePerformRelocations(uint8_t* data, size_t relocationPoint)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;

	for (int i = 0; i < elfHeader->e_shnum; ++i) {
		Elf32_Shdr* section = KeGetELFSectionHeader(data, i);

		if (section->sh_type == SHT_REL) {
		
			Elf32_Rel* relocationTables = (Elf32_Rel*)(data + section->sh_offset);
			int count = section->sh_size / section->sh_entsize;

			if (strcmp(KeLookupELFString(data, section->sh_name), ".rel.dyn")) {
				continue;
			}

			for (int index = 0; index < count; ++index) {
				bool success = KePerformRelocation(data, relocationPoint, section, relocationTables + index);
				if (!success) {
					return false;
				}
			}


		} else if (section->sh_type == SHT_RELA) {
			KePanic("KePerformRelocations: SHIT! RELA");
		}
	}

	return true;
}

size_t KeLoadELF(uint8_t* data, bool relocate, size_t relocationPoint)
{
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) data;

	if (!KeIsELFValid(elfHeader)) {
		return 0;
	}

	if (relocate && elfHeader->e_shnum == 0) {
		// we can't relocate without section headers
		// (we can load normal programs fine though)
		return 0;
	}

	if (elfHeader->e_phnum == 0) {
		// no program headers means no program to load
		return 0;
	}

	size_t sbrkAddr = KeLoadELFProgramHeaders(data, relocate, relocationPoint);
	kprintf("loaded program, with sbrk at 0x%X.\n", sbrkAddr);

	if (relocate) {
		bool success = KePerformRelocations(data, relocationPoint);
		if (!success) {
			return 0;
		}
	}

	return relocate ? relocationPoint : sbrkAddr;
}

void KeExecuteDriver(size_t startAddr, void* parentDevice)
{
	if (!startAddr) {
		KePanic("ATTEMPTING TO START DRIVER LOCATED AT 0x0");
	}
	reinterpret_cast<int(*)(void*)>(startAddr)(parentDevice);
}

bool KeLoadAndExecuteDriver(const char* filepath, void* parentDevice, bool critical)
{
	size_t loadAddr = KeLoadDriver(filepath);

	if (loadAddr) {
		KeExecuteDriver(loadAddr, parentDevice);
		return true;
	}

	if (critical) {
		char msg[256];
		strcpy(msg, "FAILED TO LOAD DLL ");
		strcat(msg, filepath);
		KePanic(msg);
	}

	return false;
}