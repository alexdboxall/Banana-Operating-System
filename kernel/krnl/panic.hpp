#ifndef _PANIC_KCON_HPP_
#define _PANIC_KCON_HPP_

#include "core/main.hpp"

namespace Krnl
{
	extern bool kernelInPanic;
	extern void panic(const char* message);
}

using Krnl::panic;

#endif