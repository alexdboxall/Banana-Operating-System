#ifndef _KRAND_HPP_
#define _KRAND_HPP_

#include <stdint.h>

namespace Krnl
{
	void initRNG();
	uint32_t rand();
}

#endif