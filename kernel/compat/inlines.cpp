#include "hw/cpu.hpp"

extern "C" CPU* _ZN3CPU7currentEv()		//	CPU::current()
{
	return CPU::current();
}

extern "C" void* _Znwm(size_t size)		//	operator new(size_t)
{
	return malloc(size);
}

/*
extern "C" void operator delete(void* p)
{
	rfree(p);
}*/