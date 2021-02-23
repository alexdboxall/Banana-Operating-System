#ifndef _ELF_HPP_
#define _ELF_HPP_

#include <stdint.h>
#include <stddef.h>
#include "fs/vfs.hpp"

#define ELF_ARCH_32 0x03
#define ELF_ARCH_64 0x3E

enum ELFProgramTypes
{
	PT_NULL = 0,
	PT_LOAD = 1,
	PT_DYNAMIC = 2,
	PT_INTERP = 3,
	PT_NOTE = 4,
	PT_SHLIB = 5,
	PT_PHDIR = 6,
	PT_LOOS = 0x60000000,
	PT_HIOS = 0x6FFFFFFF,
	PT_LOPROC = 0x70000000,
	PT_HIPROC = 0x7FFFFFFF
};

enum ELFSectionTypes
{
	SHT_NULL = 0,			//null
	SHT_PROGBITS = 1,		//program
	SHT_SYMTAB = 2,			//symbol table
	SHT_STRTAB = 3,			//string table
	SHT_RELA = 4,			//relocation
	SHT_NOBITS = 8,			//not present in file (e.g. BSS)
	SHT_REL = 9,			//relocation
};

enum ELFSectionAttribs
{
	SHF_WRITE = 0x1,		//writable
	SHF_ALLOC = 0x2			//exists in memory
};

typedef struct ELFSectionHeader32
{
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint32_t sh_addr;
	uint32_t sh_offset;
	uint32_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint32_t sh_addalign;
	uint32_t sh_entsize;

} ELFSectionHeader32;

typedef struct ELFSectionHeader64
{
	uint32_t sh_name;
	uint32_t sh_type;
	uint64_t sh_flags;
	uint64_t sh_addr;
	uint64_t sh_offset;
	uint64_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint64_t sh_addalign;
	uint64_t sh_entsize;

} ELFSectionHeader64;

typedef struct ELFProgramHeader32
{
	uint32_t type;
	uint32_t p_offset;
	uint32_t p_vaddr;
	uint32_t reserved;
	uint32_t p_filsz;
	uint32_t p_memsz;
	uint32_t flags;
	uint32_t padding;

} ELFProgramHeader32;

typedef struct ELFProgramHeader64
{
	uint32_t type;
	uint32_t flags;
	uint64_t p_offset;
	uint64_t p_vaddr;
	uint64_t reserved;
	uint64_t p_filsz;
	uint64_t p_memsz;
	uint64_t padding;
	//uint64_t padding2;

} ELFProgramHeader64;

typedef struct ELFHeader
{
	uint8_t identify[16];
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	size_t entry;				//program entry point
	size_t phOffset;			//program header offset
	size_t shOffset;			//section header offset
	uint32_t flags;
	uint16_t headerSize;
	uint16_t phSize;
	uint16_t phNum;
	uint16_t shSize;			//section header size
	uint16_t shNum;				//number of sections
	uint16_t strtabIndex;

} ELFHeader;

typedef struct ELFSymbolTable32
{
	uint32_t st_name;
	size_t st_value;
	uint32_t st_size;
	uint8_t st_info;
	uint8_t st_other;
	uint16_t st_shndx;

} ELFSymbolTable32;

#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ 2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6

typedef struct ELFDynanicSection32
{
	uint32_t d_tag;
	union
	{
		uint32_t d_val;
		uint32_t d_ptr;
	} d_un;

} ELFDynanicSection32;

typedef struct ELFDynanicSection64
{
	uint64_t d_tag;
	union
	{
		uint64_t d_val;
		uint64_t d_ptr;
	} d_un;

} ELFDynanicSection64;

bool allocateMemoryForTask(Process* prcss, File* file, size_t size, size_t virtualAddr, size_t additionalNullBytes);
bool loadProgramIntoMemory(Process* p, const char* filename);
bool loadDriverIntoMemory(const char* filename, size_t address, bool critical = true);
bool loadKernelSymbolTable(const char* filename);
size_t getAddressOfKernelSymbol(const char* name);

size_t loadDLL(const char* name, bool critical = true);
void executeDLL(size_t startAddr, void* parentDevice);

char* getDriverNameFromAddress(size_t addr);
size_t getDriverOffsetFromAddress(size_t addr);
size_t getDriverBaseFromAddress(size_t addr);

#endif