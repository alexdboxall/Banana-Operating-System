#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

	void KeNetCreateSemaphore(size_t* mutex, int count);
	void KeNetFreeSemaphore(size_t* mutex);
	void KeNetSignalSemaphore(size_t* mutex);
	int KeNetWaitSemaphore(size_t* mutex, int millisecs);
	void KeNetCreateThread(void (*thread)(void*), void* arg);
	void KeCPanic(const char* message);
	void KeCPuts(const char* message);

#ifdef __cplusplus
}
#endif