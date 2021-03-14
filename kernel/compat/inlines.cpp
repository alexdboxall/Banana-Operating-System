#include "hw/cpu.hpp"

extern "C" CPU* _ZN3CPU7currentEv()
{
	return CPU::current();
}