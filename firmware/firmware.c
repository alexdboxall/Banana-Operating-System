#include "firmware.h"

int cursorX = 0;
int cursorY = 0;

int bgC = TCBlack;
int fgC = TCLightGrey;

uint8_t cdDrive = 0;
uint8_t hdd = 0;

void setFgCol(uint8_t col)
{
	fgC = col;
}

void executeFrom(uint32_t addr)
{
	asm volatile ("jmp *%%esi" : : "S" (addr) : "memory");
}

regs_t abstractionCall (int num, regs_t in)
{
	volatile uint32_t resA;
	volatile uint32_t resB;
	volatile uint32_t resC;
	volatile uint32_t resD;

	uint32_t spot = 0xC200 + num * 0x10;

	asm volatile (
		"call *%%esi"  :                //assembly
		"=a" (resA),                //output
		"=b" (resB),                //output
		"=c" (resC),                //output
		"=d" (resD) :                //output
		"a" (in.eax),                 //input
		"S" (spot),                 //input
		"b" (in.ebx),                     //input
		"c" (in.ecx),                     //input
		"d" (in.edx) :                    //input
		"memory", "cc");            //clobbers

	in.eax = resA;
	in.ebx = resB;
	in.ecx = resC;
	in.edx = resD;
	return in;
}

//0=none, 1=HDD, 2=FDD, 3=CD
uint8_t disks[16];
void setupAbstractionLibrary()
{
	cursorX = 0;
	cursorY = 0;
	bgC = TCBlack;
	fgC = TCLightGrey;

	//TODO: find where the BSS and stack sections are and clear them...

	regs_t in;
	for (int i = 0; i < 16; ++i) {
		in.edx = i;
		in = abstractionCall(ACDriveType, in);

		disks[i] = in.eax;
	}

	cdDrive = getCD();
	hdd = getFirstHDD();
}

void clearScreenToColour(uint8_t col)
{
	bgC = col;

	cursorX = 0;
	cursorY = 0;
	
	regs_t in;
	in.eax = col;

	abstractionCall(ACClearScreen, in);
}

void sleep(int secs)
{
	regs_t in;
	for (int quarter = 0; quarter < secs * 4; ++quarter) {
		abstractionCall(ACQuarterSecondDelay, in);
	}
}

void millisleep(int milli)
{
	regs_t in;

	for (int quarter = 0; quarter < (milli + 249) / 250; ++quarter) {
		abstractionCall(ACQuarterSecondDelay, in);
	}
}

char blockingKeyboard()
{
	regs_t in;
	in = abstractionCall(ACKeyboardBlocking, in);
	char c = in.eax & 0xFF;
	uint8_t high = (in.eax >> 8) & 0xFF;
	if (c == '\r') c = '\n';
	if (high == 0x48) return 1;
	if (high == 0x50) return 2;
	if (high == 0x01 && (in.eax & 0xFF) == 0x1B) return '\e';

	return c;
}

char nonBlockingKeyboard()
{
	regs_t in;
	in = abstractionCall(ACKeyboardNonblocking, in);
	char c = in.eax & 0xFF;
	uint8_t high = (in.eax >> 8) & 0xFF;
	if (c == '\r') c = '\n';
	if (high == 0x48) return 1;
	if (high == 0x50) return 2;
	if (high == 0x01 && (in.eax & 0xFF) == 0x1B) return '\e';

	return c;
}

void clearScreen()
{
	clearScreenToColour(0);
}

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0"
				  : "=a"(ret)
				  : "Nd"(port));
	return ret;
}

void outb(uint16_t port, uint8_t  val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void beep(int hz)
{
	if (hz) {
		uint32_t Div = 1193180 / hz;
		outb(0x43, 0xb6);
		outb(0x42, (uint8_t) (Div));
		outb(0x42, (uint8_t) (Div >> 8));
		uint8_t tmp = inb(0x61);
		if (tmp != (tmp | 3)) {
			outb(0x61, tmp | 3);
		}
	} else {
		uint8_t tmp = inb(0x61) & 0xFC;
		outb(0x61, tmp);
	}
}

void writeCharacter(int x, int y, char c, uint8_t fg, uint8_t bg)
{
	regs_t in;
	in.eax = x;
	in.ebx = y;
	in.ecx = c;
	in.edx = fg | bg << 4;

	while ((inb(0x3F8 + 5) & 0x20) == 0);
	outb(0x3F8, c);

	abstractionCall(ACWriteCharacter, in);
}

void writeHex(uint32_t data)
{
	char lookup[] = "0123456789ABCDEF    ";

	for (int i = 0; i < 8; ++i) {
		char cc = lookup[(data & 0xF0000000) >> 28];
		data <<= 4;
		writeCharacter(cursorX, cursorY, cc, fgC, bgC);
		cursorX++;
		if (cursorX == 80) {
			cursorX = 0;
			cursorY++;

			if (cursorY >= 25) {
				cursorY = 0;
			}
		}
	}
}

void writeString(char* s)
{
	for (int i = 0; s[i]; ++i) {
		if (s[i] == '\n') {
			cursorX = 0;
			cursorY++;
		} else {
			writeCharacter(cursorX, cursorY, s[i], fgC, bgC);
			cursorX++;
			if (cursorX == 80) {
				cursorX = 0;
				cursorY++;

				if (cursorY >= 25) {
					cursorY = 0;
				}
			}
		}
	}
}

bool readSector(uint32_t lba, void* location, uint8_t disk)
{
	regs_t in;
	in.eax = lba;
	in.ebx = (size_t) location;
	in.edx = disk;
	in = abstractionCall(ACReadSector, in);

	return in.eax == 0 ? true : false;
}

bool writeSector(uint32_t lba, void* location, uint8_t disk)
{
	regs_t in;
	in.eax = lba;
	in.ebx = (size_t) location;
	in.edx = disk;
	in = abstractionCall(ACWriteSector, in);

	return in.eax == 0 ? true : false;
}

uint8_t getFirstHDD()
{
	for (int i = 0; i < 16; ++i) {
		if (disks[i] == 1) {
			return i;
		}
	}

	return 0xFF;
}

void* __memcpy(void* destination, const void* source, size_t num);

int getRAMMap(void* addr)
{
	regs_t in;
	in.eax = (uint32_t) addr;
	in = abstractionCall(ACReadRAM, in);
	return in.eax;
}

uint8_t getCD()
{
	for (int i = 0; i < 16; ++i) {
		if (disks[i] == 3) {
			return i;
		}
	}

	return 0xFF;
}

uint8_t getFirstFloppy()
{
	for (int i = 0; i < 16; ++i) {
		if (disks[i] == 2) {
			return i;
		}
	}

	return 0xFF;
}



uint16_t fatReservedSectors;
uint8_t totalFats;
uint32_t fatHiddenSectors;
uint32_t logicalSectorsPerFAT;

/*
;RESERVED SECTORS 0x187E
;2 FATS
;0x80 HIDDEN SECTORS
;0x1FCF sectors per FAT*/

uint32_t getFAT()
{
	return (uint32_t) fatReservedSectors + fatHiddenSectors;
}

uint32_t getRoot();

uint32_t getNext(uint32_t previous) {
	uint32_t root = getRoot();
	previous -= root;
	previous += 2;

	uint32_t fat = getFAT();

	//prev = 0x16351
	//FAT = 0x187E

	//0x2C6 + FAT
	//0x144
	uint32_t sector = (previous >> 7) + fat;
	uint32_t offset = (previous << 2) & 0b111111111;

	readSector(sector, (void*) 0x500, hdd);

	offset += 0x500;
	
	uint32_t val = *((uint32_t*) offset);
	val &= 0b1111111111111111111111111111;
	if (val >= 0xF0000000) {
		return 0xF0000000;
	}

	return val + getRoot() - 2;
}

uint32_t getRoot()
{
	return getFAT() + logicalSectorsPerFAT * (uint16_t) totalFats;
}

uint32_t findStartOfPathSection(uint32_t prevRoot, char* part, bool last, uint32_t* sizeout)
{
	if (prevRoot > 0xF0000000) {
		return 0;		//probably doesn't exist
	}
	
	readSector(prevRoot, (void*) 0x500, hdd);
	if (prevRoot == 0x2000) {
		__memcpy((void*) 0x1111900, (void*) 0x500, 0x200);
	}
	uint8_t* data = (uint8_t*) 0x500;
	
	for (int i = 0; i < 512 / 32; ++i) {
		bool pathMatch = true;

		for (int j = 0; j < 11; ++j) {
			if (part[j] != data[j]) {
				pathMatch = false;
				break;
			}
		}

		if (pathMatch) {
			uint32_t out = 0;
			out |= data[0x15];
			out <<= 8;
			out |= data[0x14];
			out <<= 8;
			out |= data[0x1B];
			out <<= 8;
			out |= data[0x1A];

			if (last) {
				uint32_t size = 0;
				size |= data[0x1F];
				size <<= 8;
				size |= data[0x1E];
				size <<= 8;
				size |= data[0x1D];
				size <<= 8;
				size |= data[0x1C];

				*sizeout = size;
			}

			return out + getRoot() - 2;
		}

		data += 32;
	}

	return findStartOfPathSection(getNext(prevRoot), part, last, sizeout);
}


uint32_t readFATFileSectorStart(char* filename)
{
	regs_t in;
	in = abstractionCall(ACBootFATInformation, in);

	fatReservedSectors = in.ecx;
	totalFats = in.edx;
	fatHiddenSectors = in.ebx;
	logicalSectorsPerFAT = in.eax;

	bool foundSplit = true;

	uint32_t root = getRoot();
	uint32_t sz = 0;

	while (foundSplit) {
		foundSplit = false;

		char part[13];
		for (int i = 0; i < 11; ++i) {
			part[i] = ' ';
		}
		part[11] = 0;

		for (int i = 0; i < 12; ++i) {
			if (filename[i] == '/' || filename[i] == '\\') {
				filename += i + 1;
				foundSplit = true;
				break;
			} else if (i == 11) break;
			part[i] = filename[i];
		}

		root = findStartOfPathSection(root, part, !foundSplit, &sz);
	}

	uint32_t sectors = sz >> 9;
	uint32_t finalSectorBytes = sz & 0b111111111;

	return root;
}

void readFATFromHDD(char* filename, void* lc)
{
	uint8_t* location = (uint8_t*) lc;

	regs_t in;
	in = abstractionCall(ACBootFATInformation, in);

	fatReservedSectors = in.ecx;
	totalFats = in.edx;
	fatHiddenSectors = in.ebx;
	logicalSectorsPerFAT = in.eax;

	bool foundSplit = true;

	uint32_t root = getRoot();
	uint32_t sz = 0;

	while (foundSplit) {
		foundSplit = false;

		char part[13];
		for (int i = 0; i < 11; ++i) {
			part[i] = ' ';
		}
		part[11] = 0;

		for (int i = 0; i < 12; ++i) {
			if (filename[i] == '/' || filename[i] == '\\') {
				filename += i + 1;
				foundSplit = true;
				break;
			} else if (i == 11) break;
			part[i] = filename[i];
		}

		root = findStartOfPathSection(root, part, !foundSplit, &sz);
	}

	uint32_t sectors = sz >> 9;
	uint32_t finalSectorBytes = sz & 0b111111111;

	//the file starts at 'root' (if everything goes well)

	while (sectors--) {
		readSector(root, (void*) 0x700, hdd);
		__memcpy(location, (void*) 0x700, 0x200);
		root = getNext(root);
		location += 512;
	}

	if (finalSectorBytes) {
		readSector(root, (void*) 0x700, hdd);
		__memcpy(location, (void*) 0x700, finalSectorBytes);
	}
}







void* __malloc(int size)
{
	static int lastMalloc = 0x400000;
	size /= 8;
	size *= 8;
	size += 64;

	int a = lastMalloc;
	lastMalloc += size;
	return (void*) a;
}

void* __memset(void* b, int c, int len)
{
	unsigned char* p = (unsigned char*) b;
	while (len > 0) {
		*p = c;
		p++;
		len--;
	}
	return b;
}

void* __memcpy(void* destination, const void* source, size_t num)
{
	uint8_t* dst8 = (uint8_t*) destination;
	uint8_t* src8 = (uint8_t*) source;

	while (num--) {
		*dst8++ = *src8++;
	}

	return destination;
}

int __strlen(char* string)
{
	int a = 0;
	for (; string[a]; ++a);
	return a;
}

uint8_t* __memmem(uint8_t* big, int bigLen, uint8_t* small, int smallLen)
{
	//may have an 'off by one' error, but this won't matter, as all
	//names end in ';1'
	for (int i = 0; i < bigLen - smallLen; ++i) {
		bool yes = true;
		for (int j = 0; j < smallLen; ++j) {
			if (small[j] != big[i + j]) {
				yes = false;
				break;
			}
		}
		if (yes) {
			return big + i;
		}
	}
	return 0;
}

void readSectorFromCDROM(uint32_t sector, uint8_t* data)
{
	regs_t in;
	in.eax = sector;
	in.ebx = (size_t) data;
	in.edx = cdDrive;

	abstractionCall(ACReadSector, in);
}

bool readRoot(uint32_t* lbaOut, uint32_t* lenOut)
{
	uint8_t sector[2048];
	readSectorFromCDROM(16, sector);
	uint8_t root[34];
	__memcpy(root, sector + 156, 34);

	*lbaOut = root[2] | (root[3] << 8) | (root[4] << 16) | (root[5] << 24);
	*lenOut = root[10] | (root[11] << 8) | (root[12] << 16) | (root[13] << 24);

	return true;
}

bool readRecursively(char* filename, uint32_t startSec, uint32_t startLen, \
					 uint32_t* lbaOut, uint32_t* lenOut)
{

	char firstPart[256];
	__memset(firstPart, 0, 256);
	bool dir = false;
	for (int i = 0; filename[i]; ++i) {
		if (filename[i] == '/') {
			filename += i + 1;
			dir = true;
			break;
		}
		firstPart[i] = filename[i];
	}

	uint32_t newLba, newLen;
	uint8_t* data = (uint8_t*) __malloc(startLen);

	for (int i = 0; i < (startLen + 2047) / 2048; ++i) {
		readSectorFromCDROM(startSec + i, data + i * 2048);
	}

	uint8_t* o = __memmem(data, startLen, (uint8_t*) firstPart, __strlen(firstPart));
	if (o == 0) {
		return false;
	}
	o -= 33;                    //33 = filename start, 2 = lba start, 31 = difference

	newLba = o[2] | (o[3] << 8) | (o[4] << 16) | (o[5] << 24);
	newLen = o[10] | (o[11] << 8) | (o[12] << 16) | (o[13] << 24);

	if (dir) {
		return readRecursively(filename, newLba, newLen, lbaOut, lenOut);
	} else {
		*lbaOut = newLba;      //data
		*lenOut = newLen;      //data
		return true;
	}

	return false;
}

bool getFileData(char* filename, uint32_t* lbaOut, uint32_t* lenOut)
{
	uint32_t lba = 0, len = 0;
	*lbaOut = -1;
	*lenOut = -1;
	readRoot(&lba, &len);
	return readRecursively(filename, lba, len, lbaOut, lenOut);
}


void readISO9660FromCD(char* filename, void* location)
{
	uint32_t lba;
	uint32_t length;

	getFileData(filename, &lba, &length);
}