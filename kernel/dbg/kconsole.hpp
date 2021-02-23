#ifndef _KCON_HPP_
#define _KCON_HPP_

#include "core/main.hpp"
#include "krnl/panic.hpp"

namespace Dbg
{
	extern void kprintf(const char* format, ...);
}

using Dbg::kprintf;

#endif