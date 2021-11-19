#include "ff.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern uint32_t(*syscalls[32])(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
size_t strlen(const char* str);
void* memmove(void* dstptr, const void* srcptr, size_t size);
int sysPrintf(uint32_t format, uint32_t a1, uint32_t a2, uint32_t a3);
int sysWriteHex(uint32_t val, uint32_t length, uint32_t showZeros, uint32_t arg4);
int sysWriteChar(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
int sysReadSectors(uint32_t lba, uint32_t arg2, uint32_t count, uint32_t drive);
int sysWriteSectors(uint32_t lba, uint32_t arg2, uint32_t count, uint32_t drive);

#define DISK_BOOT_MEDIA				0
#define DISK_HARD_DRIVE				1

#define SPECIAL_KEY_TAB				'\t'
#define SPECIAL_KEY_BACKSPACE		'\b'
#define SPECIAL_KEY_ENTER			'\n'

#define SPECIAL_KEY_HOME			230
#define SPECIAL_KEY_END				231
#define SPECIAL_KEY_INSERT			232
#define SPECIAL_KEY_DELETE			233
#define SPECIAL_KEY_ESCAPE			234
#define SPECIAL_KEY_UP				235
#define SPECIAL_KEY_DOWN			236
#define SPECIAL_KEY_LEFT			237
#define SPECIAL_KEY_RIGHT			238

#define SPECIAL_KEY_F1				241
#define SPECIAL_KEY_F2				242
#define SPECIAL_KEY_F3				243
#define SPECIAL_KEY_F4				244
#define SPECIAL_KEY_F5				245
#define SPECIAL_KEY_F6				246
#define SPECIAL_KEY_F7				247
#define SPECIAL_KEY_F8				248
#define SPECIAL_KEY_F9				249
#define SPECIAL_KEY_F10				250
#define SPECIAL_KEY_F11				251
#define SPECIAL_KEY_F12				252
#define SPECIAL_KEY_PAGEUP			253
#define SPECIAL_KEY_PAGEDOWN		254

