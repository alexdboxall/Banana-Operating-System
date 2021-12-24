
#pragma once
extern void KeAssertionFailed(char* condition, const char* file, const char* func, int line);

#define assert(EX) (void)((EX) || (KeAssertionFailed (#EX, __FILE__, __func__, __LINE__),0))