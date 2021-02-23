#ifndef _KCON_HPP_
#define _KCON_HPP_

#include "core/main.hpp"
#include "krnl/panic.hpp"

using namespace Dbg;

namespace Dbg
{
	extern void kprintf(const char* format, ...);
}

namespace Krnl
{
	extern void panic(const char* message);
}

#endif