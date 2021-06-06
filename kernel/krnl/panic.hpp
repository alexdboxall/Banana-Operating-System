#ifndef _PANIC_KCON_HPP_
#define _PANIC_KCON_HPP_

#include "core/main.hpp"

extern bool KeIsKernelInPanic;
extern void KePanic(const char* message);

#endif