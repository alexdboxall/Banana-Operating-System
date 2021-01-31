#ifndef _FIRMWARE_HPP_
#define _FIRMWARE_HPP_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct regs_t
{
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
} regs_t;

extern int cursorX;
extern int cursorY;
regs_t abstractionCall(int num, regs_t in);
void setupAbstractionLibrary();

int __strlen(char* string);
void* __memcpy(void* destination, const void* source, size_t num);
void* __memset(void* b, int c, int len);
void writeHex(uint32_t data);
bool getFileData(char* filename, uint32_t* lbaOut, uint32_t* lenOut);

enum AbstractionCalls
{
	ACClearScreen,
	ACDriveType,
	ACReadSector,
	ACWriteSector,
	ACReadRAM,
	ACWriteCharacter,
	ACFindVideoMode,
	ACSetVideoMode,
	ACKeyboardBlocking,
	ACKeyboardNonblocking,
	ACBootFATInformation,
	ACQuarterSecondDelay,
	ACPagingSetup,
};

enum TerminalColours
{
	TCBlack = 0,
	TCBlue = 1,
	TCGreen = 2,
	TCTeal = 3,
	TCMaroon = 4,
	TCMagenta = 5,
	TCBrown = 6,
	TCLightGrey = 7,
	TCDarkGrey = 8,
	TCSky = 9,
	TCLime = 10,
	TCCyan = 11,
	TCRed = 12,
	TCPink = 13,
	TCYellow = 14,
	TCWhite = 15,
};


void sleep(int secs);
void millisleep(int milli);

void setFgCol(uint8_t col);

char blockingKeyboard();
char nonBlockingKeyboard();

void beep(int hz);

void clearScreen();
void clearScreenToColour(uint8_t col);

void readSectorFromCDROM(uint32_t sector, uint8_t* data);
bool readSector(uint32_t lba, void* location, uint8_t disk);
bool writeSector(uint32_t lba, void* location, uint8_t disk);

void writeCharacter(int x, int y, char c, uint8_t bg, uint8_t fg);
void writeString(char* s);
void writeHex(uint32_t data);

void executeFrom(uint32_t addr);
int getRAMMap(void* addr);

uint8_t getFirstHDD();
uint8_t getCD();
uint8_t getFirstFloppy();

void readFATFromHDD(char* filename, void* location);
void readISO9660FromCD(char* filename, void* location);
uint32_t readFATFileSectorStart(char* filename);

#endif