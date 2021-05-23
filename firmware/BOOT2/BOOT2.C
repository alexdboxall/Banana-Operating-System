#include "../firmware.h"

void main();
void _start()
{
	main();
}

#define KERNEL_SOURCE	0x100000
#define KERNEL_DEST		0x200000

size_t highestFreeAddress = KERNEL_DEST;

void loadKernel();

bool forcePIC = false;
bool safeMode = false;
bool showLogs = false;
bool forceVGA = false;
bool slowDownClock = false;
bool enableHWSecurity = true;
bool disableACPICompletely = false;
bool forceMonochrome = false;
bool vm86Debug = false;
bool floppyDrvEnable = true;
bool noFPUSaveLoad = false;

uint32_t getBootData()
{
	uint32_t data = 0;
	data |= forcePIC ? 1 : 0;
	data |= safeMode ? 2 : 0;
	data |= showLogs ? 4 : 0;
	//must be zero
	data |= slowDownClock ? 16 : 0;
	data |= enableHWSecurity ? 32 : 0;
	//must be zero
	data |= forceVGA ? 128 : 0;
	data |= 256;		//must be 1
	data |= 512;		//must be 1
	data |= disableACPICompletely ? 1024 : 0;
	data |= forceMonochrome ? 2048 : 0;
	data |= vm86Debug ? 4096 : 0;
	data |= floppyDrvEnable ? 8192 : 0;
	data |= noFPUSaveLoad ? 16384 : 0;

	return data;
}

void setBootData(uint32_t in)
{
	if (!(in & 256)) {
		clearScreen();
		writeString("WARNING: CONFIGURATION HAS BEEN CORRUPTED.\nPRESS ENTER");
		blockingKeyboard();
		in |= 256;

	}
	if (!(in & 512)) {
		clearScreen();
		writeString("WARNING: CONFIGURATION HAS BEEN CORRUPTED.\nPRESS ENTER");
		blockingKeyboard();
		in |= 512;
	}
	if (in & 8) {
		clearScreen();
		writeString("WARNING: CONFIGURATION HAS BEEN CORRUPTED.\nPRESS ENTER");
		blockingKeyboard();
		in &= ~8;
	}
	forcePIC = in & 1 ? 1 : 0;
	safeMode = in & 2 ? 1 : 0;
	showLogs = in & 4 ? 1 : 0;
	slowDownClock = in & 16 ? 1 : 0;
	enableHWSecurity = in & 32 ? 1 : 0;
	forceVGA = in & 128 ? 1 : 0;
	disableACPICompletely = in & 1024 ? 1 : 0;
	forceMonochrome = in & 2048 ? 1 : 0;
	floppyDrvEnable = in & 8192 ? 1 : 0;
	noFPUSaveLoad = in & 16384 ? 1 : 0;
}

void xxoutb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t xxinb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

bool specialMode = false;
int specialStep = 0;

void main()
{
	setupAbstractionLibrary();

	setFgCol(TCLightGrey);
	writeString("\n  Starting Banana...");
	setFgCol(TCBlack);
	clearScreenToColour(TCBlack);
	millisleep(750);
	
	char key = nonBlockingKeyboard();
	bool fulldebug = false;
	if (key == '6' || key == '7' || key == '8') {
		setFgCol(TCLightGrey);
		clearScreenToColour(TCBlack);
	}

	uint32_t s = readFATFileSectorStart("BANANA     /SYSTEM     /BOOTSET CFG");
	uint32_t secdata[512 / 4];
	readSector(s, (void*) secdata, getFirstHDD());
	setBootData(secdata[0]);

	if (key == '7' || key == '8') {
		if (key == '8') {
			fulldebug = true;
			writeString(" PRESS ENTER (A)");
			while (1) {
				char key = blockingKeyboard();
				if (key == '\n') {
					break;
				}
			}
		}
		bool resetConfig = false;
		do {
			clearScreenToColour(TCBlack);
			writeString("Banana Boot Options:\n\n [1] - Continue booting normally\n [2] - Boot in Safe Mode\n [3] - Reboot\n [4] - Shutdown\n [5] - Boot in 32 bit mode\n\n");

			writeString(" [K] - PS/2 keyboard mode             ");
			writeString(showLogs ? " set 2\n" : " set 1\n");

			writeString(" [P] - Force use of the PIC and PIT   ");
			writeString(forcePIC ? " enabled\n" : " disabled\n");

			writeString(" [V] - Force VGA 640x480 mode         ");
			writeString(forceVGA ? " enabled\n" : " disabled\n");

			writeString(" [A] - ACPI and ACPICA                ");
			writeString(disableACPICompletely ? " disabled\n" : " enabled\n");

			writeString(" [H] - Hardware security systems      ");
			writeString(enableHWSecurity ? " enabled\n" : " disabled\n");

			writeString(" [M] - Force Monochrome               ");
			writeString(forceMonochrome ? " enabled\n" : " disabled\n");

			writeString(" [T] - Older computer optimisations   ");
			writeString(slowDownClock ? " enabled\n" : " disabled\n");

			writeString(" [F] - Floppy disk driver             ");
			writeString(floppyDrvEnable ? " enabled\n" : " disabled\n");

			writeString("\n [Z] - Save these settings as defaults\n");

			writeString("\n\n\n");
			if (specialMode) {
				writeString(" Extra options enabled. Press ENTER to cancel.\n");
			}
			if (vm86Debug) {
				writeString(" VM8086 debug on. To disable, press K twice\n");
			}
			if (noFPUSaveLoad) {
				writeString(" FPU will not be saved. To disable, press K twice\n");
			}

			key = blockingKeyboard();
			while (key == '7') {
				key = blockingKeyboard();
			}

			switch (key) {
			case '\n':
				specialStep = 0;
				specialMode = false;
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
			{
				uint8_t good = 0x02;
				while (good & 0x02) good = xxinb(0x64);
				xxoutb(0x64, 0xFE);
				while (1) {
					asm("cli; hlt");
				}
				break;
			}
			case '4':
				break;
			case '5':
				break;
			case 'P':
			case 'p':
				forcePIC ^= 1;
				break;
			case 'K':
			case 'k':
				showLogs ^= 1;
				if (!showLogs) {
					noFPUSaveLoad = false;
					vm86Debug = false;
				}
				break;
			case 'V':
			case 'v':
				forceVGA ^= 1;
				break;
			case 'X':
				noFPUSaveLoad = true;
				break;
			case 'T':
			case 't':
				slowDownClock ^= 1;
				break;
			case 'H':
			case 'h':
				enableHWSecurity ^= 1;
				break;
			case 'F':
			case 'f':
				floppyDrvEnable ^= 1;
				break;
			case 'A':
			case 'a':
				disableACPICompletely ^= 1;
				break;
			case 'M':
			case 'm':
				forceMonochrome ^= 1;
				break;
			case '@':
				++specialStep;
				if (specialStep == 5) {
					specialMode = true;
					specialStep = 6;
				}
				break;
			case '*':
				vm86Debug ^= 1;
				if (!specialMode) {
					vm86Debug = false;
				}
				break;
			case 'R':
			{
				if (!specialMode) break;

				clearScreen();
				uint16_t count = getRAMMap((void*) 0x600);
				*((uint16_t*) 0x513) = count;

				uint64_t* ramTable = (uint64_t*) 0x600;
				uint16_t* ramTableLengthAddr = (uint16_t*) 0x513;
				uint16_t ramTableLength = *ramTableLengthAddr;

				writeString("RAM MAP\n ");

				for (int i = 0; i < ramTableLength; ++i) {
					uint64_t bottom = *(ramTable + 0);
					uint64_t length = *(ramTable + 1);
					uint64_t top = bottom + length;
					uint64_t type = *(((uint32_t*) ramTable) + 4);

					writeHex(type);
					writeString(": ");
					writeHex(bottom);
					writeString(" - ");
					writeHex(top);
					writeString(" (");
					writeHex(length);
					writeString(")\n ");
					ramTable += 3;	//24 bytes / uint64_t = 3
				}

				writeString("\n\n Press any key.");
				blockingKeyboard();

				break;
			}
			case '}':
			{
				if (!specialMode) break;

				clearScreen();
				uint32_t addr = 0;
				writeString(" Enter address: ");
				for (int i = 0; i < 8; ++i) {
					char c = blockingKeyboard();
					if (c == '\n') break;
					char bbb[] = { ' ', 0 };
					bbb[0] = c;
					bbb[1] = 0;
					writeString(bbb);
					int n = 0;
					if (c >= '0' && c <= '9') {
						n = c - '0';
					} else if (c >= 'A' && c <= 'F') {
						n = c - 'A' + 10;
					} else if (c >= 'a' && c <= 'f') {
						n = c - 'a' + 10;
					}
					addr <<= 4;
					addr |= n;
				}
				clearScreen();
				writeHex(addr);
				writeString("\n ");

				uint32_t* ivt = addr;
				for (int i = 0; i < 256 / 8; ++i) {
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString("\n ");
					if (i == 16) {
						writeString("\n----------\n");
						writeString(" Press a key.\n");
						blockingKeyboard();
						clearScreen();
						writeString("\n ");
					}
				}
				writeString("Press a key.\n");
				blockingKeyboard();
				break;
			}
			case ';':
			{
				if (!specialMode) break;

				clearScreen();
				writeHex(getBootData());
				writeString("Press a key.\n");
				blockingKeyboard();
				break;
			}
			case '|':
			{
				if (!specialMode) break;

				clearScreen();
				writeString(" IVT: \n ");
				uint32_t* ivt = 0;
				for (int i = 0; i < 256 / 8; ++i) {
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString(" ");
					writeHex(*ivt++);
					writeString("\n ");
					if (i == 16) {
						writeString("\n----------\n");
						writeString(" Press a key.\n");
						blockingKeyboard();
						clearScreen();
						writeString("\n ");
					}
				}
				writeString("Press a key.\n");
				blockingKeyboard();
				break;
			}
			case 'W':
			{
				clearScreen();
				writeString("Write diskette [Y/N]: ");
				char c = blockingKeyboard();
				writeString("\n");
				if (c == 'Y' || c == 'y') {
					for (int i = 0; i < 1024 * 1024 / (18 * 512) + 1; ++i) {
						writeString("0x");
						writeHex(i * 9);
						writeString("KB    ");

						writeSector(i * 18, (void*) (size_t) (i * 18 * 512), getFirstFloppy());
					}
				}
				writeString("Press a key. ");
				blockingKeyboard();
				break;
			}
			case 'Y':
			{
				if (!specialMode) break;
				resetConfig = true;
				//FALLTHROUGH
			}
			case 'Z':
			case 'z':
			{
				clearScreen();
				if (resetConfig) {
					writeString("\n Resetting...");
				}
				writeString("\n Saving...\n");
				uint32_t d = getBootData();
				if (resetConfig) {
					d = 0x320;
				}
				uint32_t s = readFATFileSectorStart("BANANA     /SYSTEM     /BOOTSET CFG");

				for (int i = 0; i < 512 / 4; ++i) {
					secdata[i] = 0;
				}
				secdata[0] = d;

				writeSector(s, (void*) secdata, getFirstHDD());
				millisleep(1000);
				clearScreen();
				writeString("\n Configuration saved. Press any key.");
				blockingKeyboard();
				resetConfig = false;
				break;
			}
			default:
				break;
			}

		} while (key != '1' && key != '2');
	}
	clearScreen();
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (B)");
		blockingKeyboard();
	}
	uint32_t data = getBootData();
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (C)");
		blockingKeyboard();
	}
	uint16_t count = getRAMMap((void*) 0x600);
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (D)");
		blockingKeyboard();
	}

	//zero out memory
	uint64_t* ramTable = 0x600;
	for (int i = 0; i < count; ++i) {
		uint64_t bottom = *(ramTable + 0);
		uint64_t length = *(ramTable + 1);
		uint64_t top = bottom + length;
		uint64_t type = *(((uint32_t*) ramTable) + 4);

		if (type == 1 && bottom >= 0x100000 && !(top >> 32)) {
			uint32_t* p = (uint32_t*) bottom;
			for (uint64_t k = 0; k < length; k += 4) {
				*p++ = 0;
			}
		}

		ramTable += 3;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (E)");
		blockingKeyboard();
	}
	readFATFromHDD("BANANA     /SYSTEM     /KERNEL32EXE", (void*) KERNEL_SOURCE);
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (F)");
		blockingKeyboard();
	}
	loadKernel32();
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (G)");
		blockingKeyboard();
	}
	count = getRAMMap((void*) 0x600);
	*((uint16_t*) 0x513) = count;
	*((uint32_t*) 0x524) = highestFreeAddress;
	*((uint32_t*) 0x500) = data;
	*((uint32_t*) 0x504) = data;
	clearScreen();
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (H)");
		blockingKeyboard();
	}

	uint32_t* directoryPointer = (uint32_t*) 0x1000;
	for (int i = 0; i < 1024; ++i) {
		directoryPointer[i] = 6;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (I)");
		blockingKeyboard();
	}
	//ID MAP FIRST 4MB
	uint32_t* pt3 = (uint32_t*) 0x3000;
	for (int i = 0; i < 1024; ++i) {
		pt3[i] = (i * 0x1000) | 7;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (J)");
		blockingKeyboard();
	}
	//MAP KERNEL ENTIRE AREA
	uint32_t* kpt = (uint32_t*) 0x100000;
	uint32_t dest = 0xC0000000;
	for (int i = 0; i < 1024 * 256; ++i) {
		kpt[i] = dest | 7;
		if (dest < 0xC0100000) {
			kpt[i] -= 0xC0000000;
			kpt[i] += KERNEL_DEST;
		}
		dest += 4096;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (K)");
		blockingKeyboard();
	}
	//MAP FIRST FOUR MBs
	uint32_t* pt4 = (uint32_t*) 0x4000;
	for (int i = 0; i < 1024; ++i) {
		pt4[i] = (i * 0x1000) | 7;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (L)");
		blockingKeyboard();
	}
	//POINT TO KERNEL MAPPINGS
	int j = 0;
	for (int i = 768; i < 1024; ++i, ++j) {
		directoryPointer[i] = (0x100000 + j * 4096) | 7;
	}
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (M)");
		blockingKeyboard();
	}
	directoryPointer[0] = 0x3007;			//ID mapped
	directoryPointer[0xC20 / 4] = 0x4007;	//map in low 4 MBs
	directoryPointer[0xFFF / 4] = 0x1007;	//map to itself
	if (fulldebug) {
		writeString("\nPRESS ANY KEY (N)");
		blockingKeyboard();
	}

	regs_t in;
	abstractionCall(ACPagingSetup, in);	
	executeFrom(0xC0000000);
	
	writeString("\nOH DEAR...");
	while (1);

	// 0x4841594E;
}




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


void loadKernel32()
{
	int actual = 0;
	ELFHeader* elf = (ELFHeader*) KERNEL_SOURCE;
	ELFSectionHeader32* sectHeaders = (ELFSectionHeader32*) (KERNEL_SOURCE + elf->shOffset);
	ELFProgramHeader32* progHeaders = (ELFProgramHeader32*) (KERNEL_SOURCE + elf->phOffset);

	for (uint16_t i = 0; i < elf->phNum; ++i) {
		size_t addr = (progHeaders + i)->p_vaddr;
		size_t fileOffset = (progHeaders + i)->p_offset;
		size_t size = (progHeaders + i)->p_filsz;

		if ((progHeaders + i)->type == PT_LOAD) {
			uint32_t* filePos = (KERNEL_SOURCE + fileOffset);

			uint32_t additionalNullBytes = (progHeaders + i)->p_memsz - (progHeaders + i)->p_filsz;

			__memcpy(addr - 0xC0000000 + KERNEL_DEST, filePos, size);
			__memset(addr + size - 0xC0000000 + KERNEL_DEST, 0, additionalNullBytes);

			if ((size_t) filePos + size > KERNEL_DEST) {
				setFgCol(TCLightGrey);
				clearScreenToColour(TCBlack);
				writeString("\n  KERNEL TOO BIG\n");
				while (1);
			}

			if (addr - 0xC0000000 + KERNEL_DEST + size + additionalNullBytes > highestFreeAddress) {
				highestFreeAddress = addr - 0xC0000000 + KERNEL_DEST + size + additionalNullBytes;
			}
		}
	}
}