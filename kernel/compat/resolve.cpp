#include "core/computer.hpp"

extern "C" {
#include "libk/string.h"
}

namespace Krnl
{
	size_t resolveCompatibilitySymbol(char* name)
	{
		if (!strcmp(name, "computer")) {
			return (size_t) Krnl::computer;

		} else if (!strcmp(name, "__udivdi3")) {
			addr = (size_t) __udivdi3;

		} else if (!strcmp(name, "__divdi3")) {
			addr = (size_t) __divdi3;

		} else if (!strcmp(name, "__umoddi3")) {
			addr = (size_t) __umoddi3;

		} else if (!strcmp(name, "__moddi3")) {
			addr = (size_t) __moddi3;
		}

		return 0;
	}
}