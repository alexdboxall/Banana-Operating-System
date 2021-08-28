#pragma once

extern "C" void KeNetCreateSemaphore(size_t* mutex, int count);
extern "C" void KeNetFreeSemaphore(size_t* mutex);
extern "C" void KeNetSignalSemaphore(size_t* mutex);
extern "C" int KeNetWaitSemaphore(size_t* mutex, int millisecs);