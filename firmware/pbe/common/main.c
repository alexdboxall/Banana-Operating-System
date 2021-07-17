#include "main.h"

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void* memmove(void* dstptr, const void* srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--)
			dst[i - 1] = src[i - 1];
	}
	return dstptr;
}

void* memset(void* bufptr, int value, size_t size)
{
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}
uint32_t (*syscalls[32])(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
extern void archSetup();
extern void fwUpdateCursor(int x, int y);
extern void fwClearScreen();
extern void fwScrollScreen();
extern void fwBeep(int hertz);
extern void fwWait(int millisec);
extern char fwHeldKey();
extern void fwWriteChar(uint32_t c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg);
extern int fwReadSector(int lba, void* location, int disk);
extern int fwWriteSctor(int lba, void* location, int disk);

int cursorX = 0;
int cursorY = 0;

int sysClearScreen(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	cursorX = 0;
	cursorY = 0;
	fwClearScreen();
	return 0;
}

int sysWriteCharToPosition(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)		//0: char, 1: x, 2: y, 3: low nibble=fg, high nibble=bg)
{
	fwWriteChar(arg1, arg2, arg3, arg4 & 0xF, (arg4 >> 4) & 0xF);
	return 0;
}

bool noUpdateCur = false;

int sysWriteChar(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)				//0: char
{
	if (arg1 == '\b') {
		if (cursorX) {
			cursorX--;
			if (!noUpdateCur) fwUpdateCursor(cursorX, cursorY);
			fwWriteChar(' ', cursorX, cursorY, 0x7, 0x0);
		}
		return 0;
	} else if (arg1 == '\n') {
		cursorX = 0;
		cursorY++;
		if (cursorY == 25) {
			cursorY = 24;
			fwScrollScreen();
		}
		if (!noUpdateCur) fwUpdateCursor(cursorX, cursorY);
		return 0;
	} else if (arg1 == '\r') {
		cursorX = 0;
		if (!noUpdateCur) fwUpdateCursor(cursorX, cursorY);
		return 0;
	}

	fwWriteChar(arg1, cursorX, cursorY, 0x7, 0x0);
	++cursorX;
	if (cursorX >= 80) {
		cursorX = 0;
		cursorY++;
		if (cursorY == 25) {
			cursorY = 24;
			fwScrollScreen();
		}
	}
	if (!noUpdateCur) fwUpdateCursor(cursorX, cursorY);
	return 0;
}

int sysWriteString(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)			//0: string
{
	noUpdateCur = true;
	char* str = (char*) arg1;
	for (int i = 0; str[i]; ++i) {
		sysWriteChar(str[i], 0, 0, 0);
	}
	noUpdateCur = false;
	fwUpdateCursor(cursorX, cursorY);
	return 0;
}

int sysBeep(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)					//0: hertz, 1: milliseconds
{
	fwBeep(arg1);
	fwWait(arg2);
	fwBeep(0);
}

int sysNonBlockingKeyboard(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	return fwHeldKey();
}

int sysBlockingKeyboard(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	while (1) {
		char c = fwHeldKey();
		if (c) return c;
	}
	return 0;
}

int sysWait(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	fwWait(arg1);
	return 0;
}

int sysReadSectors(uint32_t lba, uint32_t arg2, uint32_t count, uint32_t drive)		//0: lba, 1: buffer, 2: count, 3: drive
{
	uint8_t* buffer = arg2;
	while (count--) {
		int success = fwReadSector(lba, buffer, drive);
		if (!success) return 1;
		lba++;
		buffer += 512;
	}
	return 0;
}

int sysWriteSectors(uint32_t lba, uint32_t arg2, uint32_t count, uint32_t drive)		//0: lba, 1: buffer, 2: count, 3: drive
{
	uint8_t* buffer = arg2;
	while (count--) {
		int success = fwWriteSector(lba, buffer, drive);
		if (!success) return 1;
		lba++;
		buffer += 512;
	}
	return 0;
}

int handleSystemCall(uint32_t num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	return syscalls[num](arg1, arg2, arg3, arg4);
}

FATFS bootFS;
FATFS hardFS;

int sysReadFile(uint32_t name, uint32_t location, uint32_t length, uint32_t arg4)
{
	FIL fp;
	int br;
	int res = f_open(&fp, (const TCHAR*) name, FA_READ);
	if (res) return -1;
	res = f_read(&fp, (void*) location, length, &br);
	if (res) return -2;
	f_close(&fp);
	return br;
}

int sysFileSize(uint32_t name, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	FIL fp;
	int res = f_open(&fp, (const TCHAR*) name, FA_READ);
	if (res) return -1;
	int size = f_size(&fp);
	f_close(&fp);
	return size;
}

int sysWriteHex(uint32_t val, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	int written = 0;
	char lookup[] = "0123456789ABCDEF";
	for (int i = 0; i < (arg2 == 0 ? 8 : arg2); ++i) {
		if (arg3 || (val >> 28) || val < 0x10) {
			sysWriteChar(lookup[val >> 28], 0, 0, 0);
			written++;
		}
		if (arg3 && val < 0x10 && !i) break;
		val <<= 4;
	}
	
	return written;
}

int sysPrintf(uint32_t str, uint32_t a1, uint32_t a2, uint32_t a3)
{
	char* format = (char*) str;
	uint32_t args[3];
	args[0] = a1;
	args[1] = a2;
	args[2] = a3;
	int argno = 0;
	for (int i = 0; format[i]; ++i) {
		if (format[i] == '%') {
			++i;
			if (format[i] == 'X' || format[i] == 'x') {
				sysWriteHex(args[argno++], 0, 0, 0);
			} else if (format[i] == 's') {
				sysWriteString(args[argno++], 0, 0, 0);
			} else if (format[i] == 'c') {
				sysWriteChar(args[argno++], 0, 0, 0);
			} else {
				sysWriteChar(format[i], 0, 0, 0);
			}
		}
	}
}

void main()
{
	size_t* p = (size_t*) 0xBCDE;
	*p = handleSystemCall;

	archSetup();

	syscalls[0] = sysClearScreen;
	syscalls[1] = sysWriteCharToPosition;
	syscalls[2] = sysWriteChar;
	syscalls[3] = sysWriteString;
	syscalls[4] = sysBeep;
	syscalls[5] = sysNonBlockingKeyboard;
	syscalls[6] = sysBlockingKeyboard;
	syscalls[7] = sysWait;
	syscalls[8] = sysReadSectors;
	syscalls[9] = sysWriteSectors;
	syscalls[10] = sysWriteHex;
	syscalls[11] = sysPrintf;

	f_mount(&bootFS, "0:", 0);
	f_mount(&hardFS, "1:", 0);

	int res = sysReadFile("0:/Banana/System/COREBKUP.SYS", 0x7C00, 242, 0);
	if (res == -1) {
		sysWriteString("-1 ", 0, 0, 0);
	}
	if (res == -2) {
		sysWriteString("-2 ", 0, 0, 0);
	}
	if (res == 0) {
		sysWriteString("0 ", 0, 0, 0);
	}

	uint8_t* ptr = 0x7C00;
	for (int i = 0; i < 242; ++i) {
		sysWriteChar(*ptr++, 0, 0, 0);
	}

	sysWriteString("Starting Banana...", 0, 0, 0);

	while (1) {
		char c = sysNonBlockingKeyboard(0, 0, 0, 0);
		if (c) sysWriteChar(c, 0, 0, 0);
	}
}