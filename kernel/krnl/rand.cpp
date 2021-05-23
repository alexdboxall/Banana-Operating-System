#include "krnl/rand.hpp"
#include "hw/cpu.hpp"

extern "C" uint32_t getRDRAND();

namespace Krnl
{
	bool initedRand = false;
	uint64_t lcg;

	void initRNG()
	{
		if (initedRand) {
			panic("CAN ONLY INIT RNG ONCE");
			return;
		}

		lcg = 0;

		if (CPU::current()->features.hasRDRAND) {
			lcg = getRDRAND();
			lcg <<= 32;
			lcg |= getRDRAND();
		}

		if (CPU::current()->features.hasTSC) {
			uint64_t tsc;
			asm volatile ("rdtsc" : "=A"(tsc));
			lcg ^= tsc;
		}

		lcg = (lcg << 17) | (lcg >> (64 - 17));
		lcg ^= milliTenthsSinceBoot;
		lcg = (lcg << 37) | (lcg >> (64 - 37));
		lcg ^= 3498667479879802358ULL;

		initedRand = true;
	}

	uint32_t rand()
	{
		if (!initedRand) {
			panic("FORGOT TO SEED KERNEL RNG");
		}
		uint64_t val = (44485709377909ULL * lcg + 11863279ULL) & 0xFFFFFFFFFFFFULL;
		lcg = val;
		return val >> 16;
	}
}
