#ifndef _LIBK_STRING_H
#define _LIBK_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

	int memcmp(const void*, const void*, size_t);

	static inline __attribute__((always_inline)) void* memcpy(void* destination, const void* source, size_t n)
	{
		void* originalDest = Dest;
		asm volatile("cld; rep movsb" :: "S"(Src), "D"(Dest), "c"(Count) : "cc", "memory");
		return originalDest;
	}

	void* memmove(void*, const void*, size_t);
	void* memset(void*, int, size_t);
	size_t strlen(const char*);
	char* strcpy(char* strDest, const char* strSrc);
	int strcmp(const char* s1, const char* s2);
	char* strcat(char* dest, const char* src);

#ifdef __cplusplus
}
#endif

#endif