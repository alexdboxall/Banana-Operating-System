#include <core/common.hpp>
#include <core/main.hpp>
#include <core/computer.hpp>
#include <krnl/hal.hpp>
#include <krnl/random.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint64_t kiRandSeed;

uint32_t KeRand()
{
	kiRandSeed = (44485709377909ULL * kiRandSeed) + 11863279ULL;
	kiRandSeed &= 0xFFFFFFFFFFFF;
	return (uint32_t) (kiRandSeed >> 14);
}

void KeInitRand()
{
	uint32_t seed = HalQueryPerformanceCounter() ^ 0x38958A03;
	HalFlushTLB();
	HalFlushTLB();
	HalFlushTLB();
	HalFlushTLB();
	KeSeedRand(seed);
}

void KeSeedRand(uint32_t seed)
{
	seed ^= HalGetRand();
	kiRandSeed = seed;
	KeRand();
	KeRand();
}