#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	void KeNetCreateSemaphore(size_t* mutex, int count);
	void KeNetFreeSemaphore(size_t* mutex);
	void KeNetSignalSemaphore(size_t* mutex);
	int KeNetWaitSemaphore(size_t* mutex, int millisecs);

#ifdef __cplusplus
}
#endif