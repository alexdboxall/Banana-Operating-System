#include "libk/string.h"


//ALL OF THESE DEFINED BY ACPICA

/*
libk/string.32: In function `memmove':
string.c:(.text+0x0): multiple definition of `memmove'
acpica/utclib.32:utclib.c:(.text+0x50): first defined here
libk/string.32: In function `strlen':
string.c:(.text+0x50): multiple definition of `strlen'
acpica/utclib.32:utclib.c:(.text+0x100): first defined here
libk/string.32: In function `memcmp':
string.c:(.text+0x70): multiple definition of `memcmp'
acpica/utclib.32:utclib.c:(.text+0x0): first defined here
libk/string.32: In function `memset':
string.c:(.text+0xe0): multiple definition of `memset'
acpica/utclib.32:utclib.c:(.text+0xd0): first defined here
libk/string.32: In function `memcpy':
string.c:(.text+0x110): multiple definition of `memcpy'
acpica/utclib.32:utclib.c:(.text+0xa0): first defined here
libk/string.32: In function `strcpy':
string.c:(.text+0x140): multiple definition of `strcpy'
acpica/utclib.32:utclib.c:(.text+0x1e0): first defined here
libk/string.32: In function `strcmp':
string.c:(.text+0x160): multiple definition of `strcmp'
*/

/*
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

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int memcmp(const void* aptr, const void* bptr, size_t size)
{
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
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

char* strcpy(char* strDest, const char* strSrc)
{
	//assert(strDest != NULL && strSrc != NULL);
	char* temp = strDest;
	 while((*strDest++=*strSrc++) != '\0');
	return temp;
}

int strcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}*/
